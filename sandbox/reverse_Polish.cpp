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

  std::string
  printContext_template(const std::string& type_name, const std::set<std::string>& types)
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

  std::string
  common_element(const PrintContext& printContext)
  {
    assert(printContext.vector.size() + printContext.matrix.size() > 0);

    std::stringstream str;

    str << "Common_Element_Type_t<";
    str << printContext_template("", printContext.vector);
    if (printContext.vector.size()) str << ", ";
    str << printContext_template("", printContext.matrix);
    str << ">";

    return str.str();
  }

  template <PrintMode_Enum MODE>
  std::string
  print_item(PrintContext& printContext, const int s)
  {
    assert(s == 1 or s == 2);

    std::string var_name;
    switch (s)
    {
      case 1:
        var_name = "alpha";
        break;
      case 2:
        var_name = "beta";
        break;
      default:
        var_name = "???";
    }

    if constexpr (MODE == PrintMode_Enum::Expression)
    {
      return var_name;
    }
    else
    {
      static_assert(MODE == PrintMode_Enum::Prototype);

      return common_element(printContext) + "& " + var_name + " \n";
    }
  }

  template <PrintMode_Enum MODE>
  std::string
  print_item(PrintContext& printContext, const _transpose_t_)
  {
    printContext.count_op++;
    std::string var_name = "op" + std::to_string(printContext.count_op);
    std::string var_enum = "OP" + std::to_string(printContext.count_op) + "_ENUM";
    std::string var_type = "_matrix_unary_op_t_<" + var_enum + ">";

    if constexpr (MODE == PrintMode_Enum::Expression)
    {
      printContext.matrix_op.insert(var_enum);
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
      printContext.count_op = 0;  // CAVEAT

      str << "template<";
      str << printContext_template("Matrix_Unary_Op_Enum", printContext.matrix_op);
      if (printContext.matrix_op.size()) str << ", ";
      str << printContext_template("typename", printContext.vector);
      if (printContext.vector.size()) str << ", ";
      str << printContext_template("typename", printContext.matrix);

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

  constexpr int alpha = 1;
  constexpr int beta  = 2;

  //  constexpr int gamma = 2;

  std::cout << Detail::call_assign<PrintMode_Enum::Prototype>(M0, M1 * (M2 + M1));
  std::cout << Detail::call_assign<PrintMode_Enum::Prototype>(
      M0, alpha * (M1 * V2 + beta * transpose(M1)) * M2);
  std::cout << Detail::call_assign<PrintMode_Enum::Prototype>(
      V0, alpha * transpose(M1) * V1 + beta * transpose(V0));

  return 0;
}
//
// V0 =  + * * s-4 op1 M1 V1 * s2 op2 V0
//
//
// V0 =  + * * alpha op1 M1 V1 * beta op2 V0
//
template <Matrix_Unary_Op_Enum OP1_ENUM, Matrix_Unary_Op_Enum OP2_ENUM, typename V0_IMPL,
          typename V1_IMPL, typename M1_IMPL>
void
assign(Vector_Crtp<V0_IMPL>& V0, const _plus_t_, const _product_t_, const _product_t_,
       const Common_Element_Type_t<V0_IMPL, V1_IMPL, M1_IMPL>& alpha,
       const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<M1_IMPL>& M1,
       const Vector_Crtp<V1_IMPL>& V1, const _product_t_,
       const Common_Element_Type_t<V0_IMPL, V1_IMPL, M1_IMPL>& beta,
       const _matrix_unary_op_t_<OP2_ENUM> op2, const Vector_Crtp<V0_IMPL>& _V0)
{
}
