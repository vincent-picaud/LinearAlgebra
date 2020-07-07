// [[file:call_assign_demo.org]]
// [BEGIN_call_assign_demo.cpp]
#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/dense/vmt_assignment_operator_define.hpp"
#include "LinearAlgebra/metaexpr/call_assign_from_metaexpr.hpp"
#include "LinearAlgebra/metaexpr/metaexpr_crtp.hpp"
#include "LinearAlgebra/vector.hpp"

#include <iostream>
#include <sstream>
#include <string>
namespace LinearAlgebra
{
  // [BEGIN_vector_type]
  //
  // This is the strict minimum to define a new vector type that inherits from =Vector_Crtp=.
  //
  class Minimal_Vector;

  template <>
  struct Crtp_Type_Traits<Minimal_Vector>
  {
    using element_type = int;
    using size_type    = std::size_t;
  };

  class Minimal_Vector : public Vector_Crtp<Minimal_Vector>
  {
   public:
    using base_type    = Vector_Crtp<Minimal_Vector>;
    using element_type = typename base_type::element_type;
    using size_type    = typename base_type::size_type;

   protected:
    // My data
    std::size_t _number;

   public:
    explicit Minimal_Vector(const size_t number) : _number(number) {}

    std::size_t
    number() const
    {
      return _number;
    }

    // Provides operator=() -> must be followed by impl_assign
    // implementation (see protected: section)
    VMT_ASSIGNMENT_OPERATOR(Minimal_Vector);

   protected:
    friend base_type;

    size_type
    impl_size() const
    {
      return 0;
    }

    const Minimal_Vector&
    impl_as_const() const
    {
      return *this;
    }

    // VMT_ASSIGNMENT_OPERATOR most basic implementation
    //
    template <typename EXPR_IMPL>
    Minimal_Vector&
    impl_assign(const Detail::MetaExpr_Crtp<EXPR_IMPL>& metaExpr)  // Expression Template
    {
      // code here ...
      return *this;
    }

    Minimal_Vector&
    impl_assign(const Minimal_Vector&)  // Compatible Vector
    {
      // code here ...
      return *this;
    }

    Minimal_Vector&
    impl_assign(const element_type&)  // Compatible Scalar
    {
      // code here ...
      return *this;
    }
  };
  // [END_vector_type]

  // ////////////////////////////////////////////////////////////////

  // [BEGIN_to_string_operator]

  template <typename IMPL>
  std::string
  template_declaration(const Expr_Tags_Crtp<IMPL>&)
  {
    return "";
  }

  std::string
  type_name(const _plus_t_&)
  {
    return "_plus_t_";
  }

  std::string
  variable_name(const _plus_t_&)
  {
    return "";
  }

  std::string
  to_string(const _plus_t_)
  {
    return " + ";
  }

  // [END_to_string_operator]

  // ================================================================

  // [BEGIN_to_string_minimal_vector]

  std::string
  variable_name(const Minimal_Vector& v)
  {
    return "vector_" + std::to_string(v.number());
  }
  std::string
  template_parameter(const Minimal_Vector& v)
  {
    return "VECTOR_" + std::to_string(v.number()) + "_IMPL";
  }
  std::string
  template_declaration(const Minimal_Vector& v)
  {
    return "typename " + template_parameter(v);
  }
  std::string
  type_name(const Minimal_Vector& v)
  {
    return "Vector_CRTP<" + template_parameter(v) + ">";
  }

  std::string
  to_string(const Minimal_Vector& v)
  {
    return variable_name(v);
  }

  // [END_to_string_minimal_vector]

  // ////////////////////////////////////////////////////////////////

  // remove last n char
  std::string
  remove_last_n(std::string s, std::size_t n)
  {
    if (s.size() > n)
    {
      return std::string(s.begin(), s.end() - n);
    }
    return {};
  }

  template <typename DEST_IMPL, typename... ARGS>
  std::string
  to_string(const VMT_Crtp<DEST_IMPL>& dest, const std::tuple<ARGS...>& tuple)
  {
    std::stringstream buffer;

    auto add_space = [](const auto& arg) {
      using std::to_string;
      return to_string(arg) + " ";
    };

    auto reverse_Polish_string =
        std::apply([&](const auto&... args) { return (add_space(args.impl()) + ...); }, tuple);

    // ----------------

    auto add_comma = [](const auto& arg) {
      std::string r = template_declaration(arg);
      if (not r.empty())
      {
        return r + ", ";
      }
      return r;
    };

    auto template_declaration_string =
        std::apply([&](const auto&... args) { return (add_comma(args.impl()) + ...); }, tuple);

    // remove last ", "
    template_declaration_string = remove_last_n(template_declaration_string, 2);

    // ----------------

    auto argument_comma = [](const auto& arg) {
      return "const " + type_name(arg) + "& " + variable_name(arg) + ", ";
    };
    auto argument_declaration_string =
        std::apply([&](const auto&... args) { return (argument_comma(args.impl()) + ...); }, tuple);
    // remove last ", "
    argument_declaration_string = remove_last_n(argument_declaration_string, 2);

    // ----------------

    buffer << "// " << variable_name(dest.impl()) << " = " << reverse_Polish_string << std::endl
           << "// " << std::endl;

    if (not template_declaration_string.empty())
    {
      buffer << "template<" << template_declaration_string << ">" << std::endl;
    }
    buffer << "void assign(" << type_name(dest.impl()) + "& " + variable_name(dest.impl()) << ", "
           << argument_declaration_string << ")" << std::endl;

    buffer << "{" << std::endl;
    buffer << std::endl;
    buffer << "}" << std::endl;

    return buffer.str();
  }

  template <typename DEST_IMPL, typename SRC_IMPL>
  std::string
  to_string(const VMT_Crtp<DEST_IMPL>& dest,
            const LinearAlgebra::Detail::MetaExpr_Crtp<SRC_IMPL>& metaExpr)
  {
    return to_string(dest, from_metaexpr_to_reverse_Polish_tuple(metaExpr.impl()));
  }
}  // namespace LinearAlgebra

using namespace LinearAlgebra;

#define PRINT_EXPR(DEST, EXPR) \
  std::cout << "//\n// " #DEST << " = " << #EXPR << "\n" << to_string(DEST, EXPR);

int
main()
{
  Minimal_Vector V0(0), V1(1), V2(2);
  PRINT_EXPR(V0, V1 + V2 + V2);
  //  std::cout << to_string(V0, V1 + V2 + V2);
}
// [END_call_assign_demo.cpp]
