#include "LinearAlgebra/dense/matrix_storage_mask_enum.hpp"
#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/dense/vmt_assignment_operator_define.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/expr/scalar_crtp.hpp"
#include "LinearAlgebra/metaexpr/call_assign_from_metaexpr.hpp"
#include "LinearAlgebra/metaexpr/metaexpr_crtp.hpp"
#include "LinearAlgebra/vector.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace LinearAlgebra
{
  // from: https://en.cppreference.com/w/cpp/string/byte/toupper
  std::string
  str_toupper(std::string s)
  {
    std::transform(
        s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::toupper(c); }  // correct
    );
    return s;
  }

  // ////////////////////////////////////////////////////////////////

  class _LHS_;

  template <>
  struct Crtp_Type_Traits<_LHS_>
  {
    using element_type = int;
  };

  class _LHS_ : public VMT_Crtp<_LHS_>
  {
   public:
    using base_type    = VMT_Crtp<_LHS_>;
    using element_type = typename base_type::element_type;
  };

  // ////////////////////////////////////////////////////////////////

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
  };

  // ////////////////////////////////////////////////////////////////

  class Minimal_Matrix;

  template <>
  struct Crtp_Type_Traits<Minimal_Matrix>
  {
    using element_type = int;
    using I_size_type  = std::size_t;
    using J_size_type  = std::size_t;
  };

  class Minimal_Matrix : public Matrix_Crtp<Minimal_Matrix>
  {
   public:
    using base_type    = Matrix_Crtp<Minimal_Matrix>;
    using element_type = typename base_type::element_type;

   protected:
    // My data
    std::size_t _number;

   public:
    explicit Minimal_Matrix(const size_t number) : _number(number) {}

    std::size_t
    number() const
    {
      return _number;
    }
  };

  // ////////////////////////////////////////////////////////////////
  //
  // We cannot use native transpose, identity etc... has we cannot
  // affect them a number...
  //
  // That's the reason why we create ad hoc functions
  //
  // ////////////////////////////////////////////////////////////////

  // Mimic transpose, etc... + let add a number
  //
  template <Matrix_Unary_Op_Enum OP, std::size_t N>
  struct Transpose_Like : Expr_Tags_Crtp<Transpose_Like<OP, N>>
  {
  };

  // ----

  template <typename T>
  struct Is_Transpose_Like : std::false_type
  {
  };
  template <Matrix_Unary_Op_Enum OP, std::size_t N>
  struct Is_Transpose_Like<Transpose_Like<OP, N>> : std::true_type
  {
  };

  // ----

  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>,
                                            Transpose_Like<Matrix_Unary_Op_Enum::Transpose, 1>,
                                            IMPL>>
  transpose1(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }
  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>,
                                            Transpose_Like<Matrix_Unary_Op_Enum::Transpose, 2>,
                                            IMPL>>
  transpose2(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }

  // ----

  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>,
                                            Transpose_Like<Matrix_Unary_Op_Enum::Identity, 1>,
                                            IMPL>>
  identity1(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }
  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>,
                                            Transpose_Like<Matrix_Unary_Op_Enum::Identity, 2>,
                                            IMPL>>
  identity2(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }
  // ----

  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>,
                                            Transpose_Like<Matrix_Unary_Op_Enum::Conjugate, 1>,
                                            IMPL>>
  conjugate1(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }
  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>,
                                            Transpose_Like<Matrix_Unary_Op_Enum::Conjugate, 2>,
                                            IMPL>>
  conjugate2(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }

  // ----

  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>,
                                            Transpose_Like<Matrix_Unary_Op_Enum::TransConj, 1>,
                                            IMPL>>
  transConj1(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }
  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>,
                                            Transpose_Like<Matrix_Unary_Op_Enum::TransConj, 2>,
                                            IMPL>>
  transConj2(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }

  // ////////////////////////////////////////////////////////////////
  //
  // We cannot use native transpose, identity etc... has we cannot
  // affect them a number...
  //
  // That's the reason why we create ad hoc functions
  //
  // ////////////////////////////////////////////////////////////////

  // Mimic transpose, etc... + let add a number
  //
  template <std::size_t N>
  struct OP_Like : Expr_Tags_Crtp<OP_Like<N>>
  {
  };

  // ----

  template <typename T>
  struct Is_OP_Like : std::false_type
  {
  };
  template <std::size_t N>
  struct Is_OP_Like<OP_Like<N>> : std::true_type
  {
  };

  // ----

  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>, OP_Like<1>, IMPL>>
  op1(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }
  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>, OP_Like<2>, IMPL>>
  op2(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }

  // ////////////////////////////////////////////////////////////////

  template <typename IMPL>
  std::string
  template_declaration(const Expr_Tags_Crtp<IMPL>&)
  {
    return "";
  }

  // ////////////////////////////////////////////////////////////////
  // For Expr_Tags types, define:
  // - type_name
  // - variable_name
  // - to_string
  // ////////////////////////////////////////////////////////////////

  // ================================================================

  template <Matrix_Unary_Op_Enum OP, std::size_t N>
  std::string
  variable_name(const Transpose_Like<OP, N>&)
  {
    return "op" + std::to_string(N);
  }

  template <Matrix_Unary_Op_Enum OP, std::size_t N>
  std::string
  template_parameter(const Transpose_Like<OP, N>&)
  {
    return "";
  }

  template <Matrix_Unary_Op_Enum OP, std::size_t N>
  std::string
  template_declaration(const Transpose_Like<OP, N>&)
  {
    return "";
  }

  template <Matrix_Unary_Op_Enum OP, std::size_t N>
  std::string
  type_name(const Transpose_Like<OP, N>&)
  {
    switch (OP)
    {
      case Matrix_Unary_Op_Enum::Transpose:
        return "_transpose_t_";
      case Matrix_Unary_Op_Enum::Identity:
        return "_identity_t_";
      case Matrix_Unary_Op_Enum::TransConj:
        return "_transConj_t_";
      case Matrix_Unary_Op_Enum::Conjugate:
        return "_conjugate_t_";

      default:
        assert(0);
        return "Internal error";
    }
  }

  template <Matrix_Unary_Op_Enum OP, std::size_t N>
  std::string
  to_string(const Transpose_Like<OP, N>&)
  {
    switch (OP)
    {
      case Matrix_Unary_Op_Enum::Transpose:
        return "transpose";
      case Matrix_Unary_Op_Enum::Identity:
        return "identity";
      case Matrix_Unary_Op_Enum::TransConj:
        return "transConj";
      case Matrix_Unary_Op_Enum::Conjugate:
        return "conjugate";

      default:
        assert(0);
        return "Internal error";
    }
  }

  // ================================================================

  template <std::size_t N>
  std::string
  variable_name(const OP_Like<N>&)
  {
    return "op" + std::to_string(N);
  }

  template <std::size_t N>
  std::string
  template_parameter(const OP_Like<N>&)
  {
    return "OP" + std::to_string(N);
  }

  template <std::size_t N>
  std::string
  template_declaration(const OP_Like<N>& op)
  {
    return " Matrix_Unary_Op_Enum " + template_parameter(op);
  }

  template <std::size_t N>
  std::string
  type_name(const OP_Like<N>& op)
  {
    return "_matrix_unary_op_t_<" + template_parameter(op) + ">";
  }

  template <std::size_t N>
  std::string
  to_string(const OP_Like<N>& op)
  {
    return variable_name(op);
  }

  // ================================================================

  std::string
  variable_name(const _inverse_t_&)
  {
    return "";
  }

  std::string
  type_name(const _inverse_t_&)
  {
    return "_inverse_t_";
  }

  std::string
  to_string(const _inverse_t_&)
  {
    return "inverse";
  }

  // ================================================================

  std::string
  variable_name(const _unary_minus_t_&)
  {
    return "";
  }

  std::string
  type_name(const _unary_minus_t_&)
  {
    return "_unary_minus_t_";
  }

  std::string
  to_string(const _unary_minus_t_&)
  {
    return "- ";
  }

  // ================================================================

  // std::string
  // variable_name(const _unary_plus_t_&)
  // {
  //   return "";
  // }

  // std::string
  // type_name(const _unary_plus_t_&)
  // {
  //   return "_unary_plus_t_";
  // }

  // std::string
  // to_string(const _unary_plus_t_&)
  // {
  //   return "+ ";
  // }

  // ================================================================

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
    return "+";
  }

  // ================================================================

  std::string
  type_name(const _minus_t_&)
  {
    return "_minus_t_";
  }

  std::string
  variable_name(const _minus_t_&)
  {
    return "";
  }

  std::string
  to_string(const _minus_t_)
  {
    return "-";
  }

  // ================================================================

  std::string
  type_name(const _product_t_&)
  {
    return "_product_t_";
  }

  std::string
  variable_name(const _product_t_&)
  {
    return "";
  }

  std::string
  to_string(const _product_t_)
  {
    return "*";
  }

  // ================================================================

  std::string
  variable_name(const _LHS_&)
  {
    return "";
  }
  std::string
  template_parameter(const _LHS_&)
  {
    return "";
  }
  std::string
  template_declaration(const _LHS_&)
  {
    return "";
  }

  std::string
  type_name(const _LHS_&)
  {
    return "_lhs_t_";
  }

  std::string
  to_string(const _LHS_&)
  {
    return "lhs ";
  }
  // ================================================================

  // ////////////////////////////////////////////////////////////////
  // For Minimal Vector, define:
  // - type_name
  // - variable_name
  // - etc...
  // - to_string
  // ////////////////////////////////////////////////////////////////

  std::string
  variable_name(const Minimal_Vector& v)
  {
    return "v" + std::to_string(v.number());
  }
  std::string
  template_parameter(const Minimal_Vector& v)
  {
    return "V" + std::to_string(v.number()) + "_IMPL";
  }
  std::string
  template_declaration(const Minimal_Vector& v)
  {
    return "typename " + template_parameter(v);
  }
  std::string
  type_name(const Minimal_Vector& v)
  {
    return "Vector_Crtp<" + template_parameter(v) + ">&";
  }

  std::string
  to_string(const Minimal_Vector& v)
  {
    return variable_name(v);
  }

  // ////////////////////////////////////////////////////////////////
  // For Minimal Matrix, define:
  // - type_name
  // - variable_name
  // - etc...
  // - to_string
  // ////////////////////////////////////////////////////////////////

  std::string
  variable_name(const Minimal_Matrix& v)
  {
    return "M" + std::to_string(v.number());
  }
  std::string
  template_parameter(const Minimal_Matrix& v)
  {
    return "M" + std::to_string(v.number()) + "_IMPL";
  }
  std::string
  template_declaration(const Minimal_Matrix& v)
  {
    return "typename " + template_parameter(v);
  }
  std::string
  type_name(const Minimal_Matrix& v)
  {
    return "Matrix_Crtp<" + template_parameter(v) + ">&";
  }

  std::string
  to_string(const Minimal_Matrix& v)
  {
    return variable_name(v);
  }

  // ================================================================

  // ////////////////////////////////////////////////////////////////
  // For Scalar, define:
  // - type_name
  // - variable_name
  // - etc...
  // - to_string
  //
  // As overloaded operators use Scalar we cannot redefine our
  // own scalar type. By consequence we use this
  // trick:
  // - use int scalar
  // - 1 => alpha, 2 => beta...
  ////////////////////////////////////////////////////////////////

  std::string
  variable_name(const Scalar<int>& scalar)
  {
    assert(scalar.value() >= 0 and scalar.value() < 3);

    switch (scalar.value())
    {
      case 0:
        return "alpha";
      case 1:
        return "beta";
      case 2:
        return "gamma";

      default:
        assert(0);
        return "Internal error";
    }
  }
  std::string
  template_parameter(const Scalar<int>& scalar)
  {
    return str_toupper(variable_name(scalar)) + "_IMPL";
  }
  std::string
  template_declaration(const Scalar<int>& scalar)
  {
    return "typename " + template_parameter(scalar);
  }
  std::string
  type_name(const Scalar<int>& scalar)
  {
    return "Scalar_Crtp<" + template_parameter(scalar) + ">&";
  }

  std::string
  to_string(const Scalar<int>& scalar)
  {
    return variable_name(scalar);
  }

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

    if (not template_declaration_string.empty())
    {
      template_declaration_string =
          template_declaration(dest.impl()) + ", " + template_declaration_string;
    }
    else
    {
      template_declaration_string = template_declaration(dest.impl());
    }
    template_declaration_string = "template<" + template_declaration_string + ">";

    // ----------------

    auto argument_comma = [](const auto& arg) {
      return "const " + type_name(arg) + " " + variable_name(arg) + ", ";
    };
    auto argument_declaration_string =
        std::apply([&](const auto&... args) { return (argument_comma(args.impl()) + ...); }, tuple);
    // remove last ", "
    argument_declaration_string = remove_last_n(argument_declaration_string, 2);

    // ----------------

    // buffer << "// " << variable_name(dest.impl()) << " = " << reverse_Polish_string << std::endl;
    buffer << "// " << std::endl;

    buffer << template_declaration_string << std::endl;

    buffer << "void assign(" << type_name(dest.impl()) + " " + variable_name(dest.impl()) << ", "
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

// string: search/replace
void
replaceAll(std::string& data, const std::string& toSearch, const std::string& replaceStr)
{
  // Get the first occurrence
  size_t pos = data.find(toSearch);
  // Repeat till end is reached
  while (pos != std::string::npos)
  {
    // Replace this occurrence of Sub String
    data.replace(pos, toSearch.size(), replaceStr);
    // Get the next occurrence from the current position
    pos = data.find(toSearch, pos + replaceStr.size());
  }
}

// super naive
std::string
to_latex(std::string str)
{
  replaceAll(str, "alpha", "\\alpha");
  replaceAll(str, "beta", "\\beta");
  replaceAll(str, "gamma", "\\gamma");

  replaceAll(str, "* ", "");

  replaceAll(str, "inverse", "\\text{inv}");

  replaceAll(str, "op0", "\\text{op}_0");
  replaceAll(str, "op1", "\\text{op}_1");
  replaceAll(str, "op2", "\\text{op}_2");

  replaceAll(str, "M0", "M_0");
  replaceAll(str, "M1", "M_1");
  replaceAll(str, "M2", "M_2");
  replaceAll(str, "M3", "M_3");
  replaceAll(str, "M4", "M_4");

  replaceAll(str, "v0", "v_0");
  replaceAll(str, "v1", "v_1");
  replaceAll(str, "v2", "v_2");
  replaceAll(str, "v3", "v_3");
  replaceAll(str, "v4", "v_4");

  return str;
}

std::string
to_latex_with_comment(const std::string& str)
{
  std::string to_return;
  to_return += "// [DOC]\n";
  to_return += "// \n";
  to_return += "// \\begin{equation*}\n";
  to_return += "// " + to_latex(str) + "\n";
  to_return += "// \\end{equation*}\n";

  return to_return;
}

using namespace LinearAlgebra;

#define PRINT_EXPR(DEST, EXPR) \
  std::cout << to_latex_with_comment(#DEST + std::string(" = ") + #EXPR) << to_string(DEST, EXPR);

// ////////////////////////////////////////////////////////////////

namespace LinearAlgebra::Detail
{
  // A offset for item value (to avoid "special" numerical value as 0, 1)
  //
  //  constexpr int offset_component = 10;

  // Print test
  //
  std::string
  print_test(const Minimal_Matrix& M)
  {
    return std::to_string((1. + M.number()) / 1000.);
  }

  std::string
  print_test(const Minimal_Vector& v)
  {
    return std::to_string((1. + v.number()) / 100.);
  }

  std::string
  print_test(const Scalar<int>& scalar)
  {
    return std::to_string((1. + scalar.value()) / 10.);
  }
  template <typename IMPL>
  std::string
  print_test(const MetaExpr_UnaryOp_Crtp<IMPL>& unary_op)
  {
    using op_type = typename IMPL::operator_type;

    // As for test we work 1x1 matrixn no need to take into account
    // transpose like operator
    if constexpr (Is_Transpose_Like<op_type>::value or Is_OP_Like<op_type>::value)
    {
      return print_test(unary_op.arg());
    }
    else if constexpr (std::is_same_v<_unary_minus_t_, op_type>)
    {
      return "- ( " + print_test(unary_op.arg()) + " )";
    }
    else if constexpr (std::is_same_v<_inverse_t_, op_type>)
    {
      return "1. / ( " + print_test(unary_op.arg()) + " )";
    }
    else
    {
      std::cerr << __PRETTY_FUNCTION__;
      assert(0);
      return "";
    }
  }

  template <typename IMPL>
  std::string
  print_test(const MetaExpr_BinaryOp_Crtp<IMPL>& binary_op)
  {
    using op_type = typename IMPL::operator_type;

    if constexpr (std::is_same_v<_product_t_, op_type>)
    {
      return "( " + print_test(binary_op.arg_0()) + " ) * ( " + print_test(binary_op.arg_1()) +
             " )";
    }
    else if constexpr (std::is_same_v<_plus_t_, op_type>)
    {
      return "( " + print_test(binary_op.arg_0()) + " ) + ( " + print_test(binary_op.arg_1()) +
             " )";
    }
    else if constexpr (std::is_same_v<_minus_t_, op_type>)
    {
      return "( " + print_test(binary_op.arg_0()) + " ) - ( " + print_test(binary_op.arg_1()) +
             " )";
    }
    else
    {
      assert(0);
    }
  }
}  // namespace LinearAlgebra::Detail

#define PRINT_TEST(DEST, EXPR)                             \
  std::cout << "\n" << #DEST << " = " << #EXPR << ";\n";   \
  std::cout << "EXPECT_DOUBLE_EQ(*" << #DEST << ".data()," \
            << LinearAlgebra::Detail::print_test(EXPR) << ");\n";

int
main()
{
  Scalar<int> alpha(0), beta(1), gamma(2);

  Minimal_Vector v0(0), v1(1), v2(2), v3(3);
  Minimal_Matrix M0(0), M1(1), M2(2), M3(3);

  PRINT_EXPR(v0, alpha * v1 + v2);
  // Alias 
  PRINT_EXPR(v0, v2 + alpha * v1);
  PRINT_EXPR(v0, v2 - alpha * v1);

  PRINT_EXPR(v0, v1 + v2);
  PRINT_EXPR(v0, v1 - v2);


  // ////////////////////////////////////////////////////////////////

  PRINT_TEST(v0, alpha * v1 + v2);

  PRINT_TEST(v0, v2 + alpha * v1);
  PRINT_TEST(v0, v2 - alpha * v1);
  
  PRINT_TEST(v0, v1 + v2);
  PRINT_TEST(v0, v1 - v2);

}

// // ////////////////////////////////////////////////////////////////

// void
// big_list()
// {
//   Scalar<int> alpha(1), beta(2), gamma(3);

//   Minimal_Vector v0(0), v1(1), v2(2), v3(3);
//   Minimal_Matrix M0(0), M1(1), M2(2), M3(3);

//   std::cout << "*** X = αX" << std::endl;

//   PRINT_EXPR(v0, alpha * v1);
//   PRINT_EXPR(v0, alpha * v0);

//   std::cout << "*** X = αX + X" << std::endl;

//   PRINT_EXPR(v0, alpha * v1 + v0);

//   // attention: v2 is always with coef = 1
//   //            v1 coef is alpha
//   PRINT_EXPR(v0, alpha * v1 + v2);
//   PRINT_EXPR(v0, v1 + v2);
//   PRINT_EXPR(v0, -v1 + v2);

//   PRINT_EXPR(v0, v2 + alpha * v1);
//   PRINT_EXPR(v0, v2 - alpha * v1);
//   PRINT_EXPR(v0, v2 - v1);

//   //================================================================

//   std::cout << "*** v0 = α op(M) v1 + β v0" << std::endl;

//   PRINT_EXPR(v0, alpha * op1(M1) * v1 + beta * v0);

//   std::cout << "*** v0 = α op(M) v1 + β v2" << std::endl;

//   PRINT_EXPR(v0, alpha * op1(M1) * v1 + beta * v2);
//   std::cout << "--- alias " << std::endl;
//   PRINT_EXPR(v0, M1 * v1 + v2);
//   PRINT_EXPR(v0, M1 * v1 + beta * v2);
//   PRINT_EXPR(v0, M1 * v1 - v2);
//   PRINT_EXPR(v0, v2 + M1 * v1);
//   PRINT_EXPR(v0, v2 + op1(M1) * v1);
//   PRINT_EXPR(v0, v2 + alpha * M1 * v1);
//   PRINT_EXPR(v0, v2 + alpha * op1(M1) * v1);
//   PRINT_EXPR(v0, v2 - M1 * v1);
//   PRINT_EXPR(v0, v2 - op1(M1) * v1);
//   PRINT_EXPR(v0, v2 - alpha * M1 * v1);
//   PRINT_EXPR(v0, op1(M1) * v1 + v2);
//   PRINT_EXPR(v0, op1(M1) * v1 + beta * v2);
//   PRINT_EXPR(v0, op1(M1) * v1 - v2);
//   PRINT_EXPR(v0, alpha * M1 * v1 + beta * v2);
//   PRINT_EXPR(v0, alpha * M1 * v1 - beta * v2);
//   PRINT_EXPR(v0, alpha * M1 * v1 + v2);
//   PRINT_EXPR(v0, alpha * M1 * v1 - v2);
//   PRINT_EXPR(v0, alpha * op1(M1) * v1 + v2);
//   PRINT_EXPR(v0, alpha * op1(M1) * v1 - v2);
//   PRINT_EXPR(v0, alpha * op1(M1) * v1 + beta * v2);
//   PRINT_EXPR(v0, beta * v2 + alpha * M1 * v1);
//   PRINT_EXPR(v0, beta * v2 - alpha * M1 * v1);
//   PRINT_EXPR(v0, beta * v2 + M1 * v1);
//   PRINT_EXPR(v0, beta * v2 + op1(M1) * v1);
//   PRINT_EXPR(v0, beta * v2 + alpha * op1(M1) * v1);
//   PRINT_EXPR(v0, beta * v2 - M1 * v1);
//   PRINT_EXPR(v0, beta * v2 - op1(M1) * v1);
//   PRINT_EXPR(v0, beta * v2 - alpha * op1(M1) * v1);
//   PRINT_EXPR(v0, -M1 * v1 + v2);
//   PRINT_EXPR(v0, -M1 * v1 + beta * v2);
//   PRINT_EXPR(v0, -M1 * v1 - v2);
//   PRINT_EXPR(v0, -v2 + M1 * v1);
//   PRINT_EXPR(v0, -v2 + op1(M1) * v1);
//   PRINT_EXPR(v0, -v2 + alpha * M1 * v1);
//   PRINT_EXPR(v0, -v2 + alpha * op1(M1) * v1);
//   PRINT_EXPR(v0, -v2 - M1 * v1);
//   PRINT_EXPR(v0, -v2 - op1(M1) * v1);
//   PRINT_EXPR(v0, -op1(M1) * v1 + v2);
//   PRINT_EXPR(v0, -op1(M1) * v1 + beta * v2);
//   PRINT_EXPR(v0, -op1(M1) * v1 - v2);

//   //================================================================

//   std::cout << "*** v0 = α op(M) v0" << std::endl;

//   PRINT_EXPR(v0, alpha * op1(M1) * v0);
//   PRINT_EXPR(v0, alpha * op1(inverse(M1)) * v0);

//   std::cout << "*** v0 = α op(M) v1" << std::endl;

//   PRINT_EXPR(v0, alpha * op1(M1) * v1);
//   PRINT_EXPR(v0, alpha * op1(inverse(M1)) * v1);

//   std::cout << "--- alias" << std::endl;
//   PRINT_EXPR(v0, M1 * v1);
//   PRINT_EXPR(v0, inverse(M1) * v1);
//   PRINT_EXPR(v0, alpha * M1 * v1);
//   PRINT_EXPR(v0, alpha * inverse(M1) * v1);
//   PRINT_EXPR(v0, op1(M1) * v1);
//   PRINT_EXPR(v0, inverse(op1(M1)) * v1);
//   PRINT_EXPR(v0, op1(inverse(M1) * v1));
//   PRINT_EXPR(v0, alpha * inverse(op1(M1)) * v1);

//   std::cout << "--- alias forgotten" << std::endl;
//   PRINT_EXPR(v0, -M1 * v1);
//   PRINT_EXPR(v0, -inverse(M1) * v1);
//   PRINT_EXPR(v0, -inverse(op1(M1)) * v1);
//   PRINT_EXPR(v0, -op1(inverse(M1) * v1));

//   std::cout << "*** M0 = α op1(M1) op2(M2) + β M0" << std::endl;

//   PRINT_EXPR(M0, alpha * op1(M1) * op2(M2) + beta * M0);

//   //
//   // TODO:  M0 = α op1(M1) op2(M2) + β M1 + Alias
//   //

//   std::cout << "*** M0 = α op1(M1) op2(M1) + β M0" << std::endl;

//   PRINT_EXPR(M0, alpha * op1(M1) * op2(M1) + beta * M0);
// }

// int
// main()
// {
//   big_list();
//   return 0;

//   // ////////////////////////////////////////////////////////////////

//   Scalar<int> alpha(1), beta(2), gamma(3);

//   Minimal_Vector v0(0), v1(1), v2(2), v3(3);
//   Minimal_Matrix M0(0), M1(1), M2(2), M3(3);

//   _LHS_ lhs;

//   PRINT_EXPR(M0, alpha * op1(M1) * op2(M2) + beta * lhs);

//   PRINT_EXPR(M2, v1 + alpha * op1(M1) * v2 + beta * v3);

//   PRINT_EXPR(M0, -(alpha * inverse(op1(M1))));

//   PRINT_EXPR(M0, M1 * op2(lhs));
// }
// // [END_print_expr_cpp]
