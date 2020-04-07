//
// Important: it helps us to generate function prototypes

#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/matrix.hpp"

#include <set>
#include <string>
#include <tuple>
#include <type_traits>

namespace LinearAlgebra
{
  enum class PrintMode_Enum
  {
    Expression,
    Prototype
  };
  using _Expression_t_ = std::integral_constant<PrintMode_Enum, PrintMode_Enum::Expression>;
  using _Prototype_t_  = std::integral_constant<PrintMode_Enum, PrintMode_Enum::Prototype>;

  struct PrintContext
  {
    size_t count_op{};
    std::set<std::string> matrix_op;
    std::set<std::string> matrix;
    std::set<std::string> vector;
    PrintContext() = default;
  };

  template <PrintMode_Enum MODE>
  std::string
  print_item(PrintContext& printContext, const double&)
  {
    if constexpr (MODE == PrintMode_Enum::Expression)
    {
      return "s";
    }
    else
    {
      static_assert(MODE == PrintMode_Enum::Prototype);

      return "SCALAR& scalar \n";
    }
  }

  template <PrintMode_Enum MODE>
  std::string
  print_item(PrintContext& printContext, const _transpose_t_)
  {
    printContext.count_op++;
    std::string var_name = "op" + std::to_string(printContext.count_op);
    std::string var_type = "_matrix_unary_op_t_<OP" + std::to_string(printContext.count_op) + ">";

    if constexpr (MODE == PrintMode_Enum::Expression)
    {
      return var_name;
    }
    else
    {
      static_assert(MODE == PrintMode_Enum::Prototype);

      return var_type + " " + var_name + " \n";
    }
  }

  // template <PrintMode_Enum MODE>
  // std::string
  // print_item(PrintContext& printContext, const _identity_t_)
  // {

  //   if constexpr (MODE == PrintMode_Enum::Expression)
  //   {
  //     return "";
  //   }
  //   else
  //   {
  //     static_assert(MODE == PrintMode_Enum::Prototype);

  //     return "_matrix_unary_op_t_<OP> \n";
  //   }
  // }

  template <PrintMode_Enum MODE, typename IMPL>
  std::string
  print_item(PrintContext& printContext, const Matrix_Crtp<IMPL>& M)
  {
    std::string var_name = "M" + std::to_string(M.I_size());
    std::string var_type = var_name + "_IMPL";

    if constexpr (MODE == PrintMode_Enum::Expression)
    {
      printContext.matrix.insert(var_type);
      return var_name;
    }
    else
    {
      static_assert(MODE == PrintMode_Enum::Prototype);

      return "Matrix_Crtp<" + var_type + ">& " + var_name + " \n";
    }
  }
  template <PrintMode_Enum MODE, typename IMPL>
  std::string
  print_item(PrintContext& printContext, const Vector_Crtp<IMPL>& V)
  {
    std::string var_name = "V" + std::to_string(V.size());
    std::string var_type = var_name + "_IMPL";

    if constexpr (MODE == PrintMode_Enum::Expression)
    {
      printContext.vector.insert(var_type);
      return var_name;
    }
    else
    {
      static_assert(MODE == PrintMode_Enum::Prototype);

      return "Vector_Crtp<" + var_type + ">& " + var_name + " \n";
    }
  }

  template <PrintMode_Enum MODE>
  std::string
  print_item(PrintContext& printContext, const _product_t_&)
  {
    if constexpr (MODE == PrintMode_Enum::Expression)
    {
      return "*";
    }
    else
    {
      static_assert(MODE == PrintMode_Enum::Prototype);

      return "_product_t_ \n";
    }
  }
  template <PrintMode_Enum MODE>
  std::string
  print_item(PrintContext& printContext, const _plus_t_&)
  {
    if constexpr (MODE == PrintMode_Enum::Expression)
    {
      return "+";
    }
    else
    {
      static_assert(MODE == PrintMode_Enum::Prototype);

      return "_plus_t_ \n";
    }
  }
  template <PrintMode_Enum MODE>
  std::string
  print_item(PrintContext& printContext, const _minus_t_&)
  {
    if constexpr (MODE == PrintMode_Enum::Expression)
    {
      return "-";
    }
    else
    {
      static_assert(MODE == PrintMode_Enum::Prototype);

      return "_minus_t_ \n";
    }
  }
  template <PrintMode_Enum MODE>
  std::string
  print_item(PrintContext& printContext, const _unary_minus_t_&)
  {
    if constexpr (MODE == PrintMode_Enum::Expression)
    {
      return "-";
    }
    else
    {
      static_assert(MODE == PrintMode_Enum::Prototype);

      return "_unary_minus_t_ \n";
    }
  }

  std::string
  printConstext_template(const std::string& type_name, const std::set<std::string>& types)
  {
    std::stringstream str;

    auto iter           = types.begin();
    const auto iter_end = types.end();

    while (iter != iter_end)
    {
      str << type_name << " " << *iter;
      ++iter;
      if (iter != iter_end)
      {
        str << ", ";
      }
    }

    return str.str();
  }

  template <PrintMode_Enum MODE, typename D, typename... T>
  std::string
  print(D& d, const T&... t)
  {
    PrintContext printContext;
    std::stringstream str;

    if constexpr (MODE == PrintMode_Enum::Prototype) str << "//\n";

    str << "// ";
    str << print_item<PrintMode_Enum::Expression>(printContext, d) << " = ";
    ((str << " " << print_item<PrintMode_Enum::Expression>(printContext, t)), ...);
    str << std::endl;

    if constexpr (MODE == PrintMode_Enum::Prototype) str << "//\n";

    
    if constexpr (MODE == PrintMode_Enum::Prototype)
    {
      printContext.count_op=0; // CAVEAT
      
      str << "template<";
      str << printConstext_template("typename", printContext.matrix);
      str << ">\n";

      str << "void assign(" << print_item<MODE>(printContext, d);
      ((str << ", const " << print_item<MODE>(printContext, t)), ...);
      str << ")\n{\n\n}\n" << std::endl;
    }

    return str.str();
  }

  //////////////////////////////////////////////////////////////////

  namespace Detail
  {
    // Everything that's not a Detail::MetaExpr_Crtp is considered as a
    // final node
    template <typename T>
    static inline std::enable_if_t<not Is_Crtp_Interface_Of<Detail::MetaExpr_Crtp, T>::value,
                                   std::tuple<const T&>>
    from_metaexpr_to_reverse_Polish_tuple(const T& t) noexcept
    {
      return {t};
    }

    // UnaryOP
    template <typename IMPL>
    static inline auto
    from_metaexpr_to_reverse_Polish_tuple(
        const Detail::MetaExpr_UnaryOp_Crtp<IMPL>& expression_tree) noexcept
    {
      return std::tuple_cat(std::make_tuple(typename IMPL::operator_type()),
                            from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg()));
    }

    // BinaryOp
    template <typename IMPL>
    static inline auto
    from_metaexpr_to_reverse_Polish_tuple(
        const Detail::MetaExpr_BinaryOp_Crtp<IMPL>& expression_tree) noexcept
    {
      return std::tuple_cat(std::make_tuple(typename IMPL::operator_type()),
                            from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg_0()),
                            from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg_1()));
    }

    //////////////////////////////////////////////////////////////////
    // Functions to use in Vector/Matrix interface
    //////////////////////////////////////////////////////////////////
    //
    // -> we use VMT_Crtp to have a generic solution
    //
    template <PrintMode_Enum MODE, typename DEST_IMPL, typename... ARGS>
    static inline auto
    call_assign_from_reverse_Polish(VMT_Crtp<DEST_IMPL>& dest,
                                    const std::tuple<ARGS...>& args_as_tuple)
    {
      // CAVEAT: not args.impl()... as args can be integer,double etc...
      return std::apply([&](const auto&... args) { return print<MODE>(dest.impl(), args...); },
                        args_as_tuple);
    }

    template <PrintMode_Enum MODE, typename DEST_IMPL, typename SRC_IMPL>
    static inline auto
    call_assign(VMT_Crtp<DEST_IMPL>& dest, const Detail::MetaExpr_Crtp<SRC_IMPL>& metaExpr)
    {
      return call_assign_from_reverse_Polish<MODE>(
          dest.impl(), from_metaexpr_to_reverse_Polish_tuple(metaExpr.impl()));
    }
  }
}

using namespace LinearAlgebra;
int
main()
{
  Tiny_Matrix<int, 0, 0> M0;
  Tiny_Matrix<int, 1, 0> M1;
  Tiny_Matrix<int, 2, 0> M2;

  Tiny_Vector<int, 0> V0;
  Tiny_Vector<int, 1> V1;
  Tiny_Vector<int, 2> V2;

  std::cout << Detail::call_assign<PrintMode_Enum::Prototype>(M0, M1 * (M2 + M1));
  std::cout << Detail::call_assign<PrintMode_Enum::Prototype>(
      M0, -4 * (M1 * V2 + 2 * transpose(M1)) * M2);
  std::cout << Detail::call_assign<PrintMode_Enum::Prototype>(V0, -4 * transpose(M1) * V1 + 2 * V0);

  return 0;
}
