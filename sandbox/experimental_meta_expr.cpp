// -*- compile-command: "g++ -std=c++17  poub2.cpp && ./a.out"; -*-
#include <array>
#include <ccomplex>
#include <iostream>
#include <memory>
#include <tuple>
#include <type_traits>

#include "LinearAlgebra/metaexpr/operator_overloading.hpp"

#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/vector.hpp"

#include "LinearAlgebra/utils/crtp.hpp"

namespace LinearAlgebra
{
  namespace Detail
  {
    //////////////////////////////////////////////////////////////////

    // Everything that's not a Detail::MetaExpr_Crtp is considered as a
    // final node
    template <typename T>
    inline constexpr std::enable_if_t<not Is_Crtp_Interface_Of<Detail::MetaExpr_Crtp, T>::value,
                                      std::tuple<const T&>>
    from_metaexpr_to_argument_tuple(const T& t) noexcept
    {
      return {t};
    }

    // TODO add Unary op
    template <typename IMPL>
    inline constexpr auto
    from_metaexpr_to_argument_tuple(
        const Detail::MetaExpr_BinaryOp_Crtp<IMPL>& expression_tree) noexcept
    {
      // Attention: our convention is to not explicitly write down "_product_"
      if constexpr (std::is_same_v<typename Detail::MetaExpr_BinaryOp_Crtp<IMPL>::operator_type,
                                   _product_t_>)
      {
        return std::tuple_cat(from_metaexpr_to_argument_tuple(expression_tree.arg_0()),
                              from_metaexpr_to_argument_tuple(expression_tree.arg_1()));
      }
      else
      {
        return std::tuple_cat(from_metaexpr_to_argument_tuple(expression_tree.arg_0()),
                              std::make_tuple(typename IMPL::operator_type()),
                              from_metaexpr_to_argument_tuple(expression_tree.arg_1()));
      }
    }

    // Functions to use in Vector/Matrix interface
    // -> here we only define the Matrix case

    template <typename M_DEST_IMPL, typename... ARGS>
    auto
    call_assign_from_argument_tuple(Matrix_Crtp<M_DEST_IMPL>& M_dest,
                                    const std::tuple<ARGS...>& args_as_tuple)
    {
      return std::apply([&](const auto&... args) { return assign(M_dest, args...); }, args_as_tuple);
    }

    template <typename M_DEST_IMPL, typename SRC_IMPL>
    auto
    call_assign_from_metaexpr(Matrix_Crtp<M_DEST_IMPL>& M_dest,
                              const Detail::MetaExpr_Crtp<SRC_IMPL>& metaExpr)
    {
      call_assign_from_argument_tuple(M_dest, from_metaexpr_to_argument_tuple(metaExpr.impl()));
    }
  }

  //================================================================

  template <typename T>
  void
  print(const T&)
  {
    std::cerr << __PRETTY_FUNCTION__ << std::endl;
  }
}  // LinearAlgebra;

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Replace expr by assign
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL_DEST, typename IMPL_ARG_1>
  std::integral_constant<Expr_Selector_Enum, Expr_Selector_Enum::Undefined>
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined>&,
         Matrix_Crtp<IMPL_DEST>& dest,                              // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1> alpha,  // alpha
         const Matrix_Crtp<IMPL_ARG_1>& arg_1                       // arg_1
  )
  {
    static_assert(Always_False_v<IMPL_DEST>, "Undefined");
    return {};
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL_DEST, typename IMPL_ARG_1>
  auto
  assign(Matrix_Crtp<IMPL_DEST>& dest,                              // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1> alpha,  // alpha
         const Matrix_Crtp<IMPL_ARG_1>& arg_1                       // arg_1
  )
  {
    return assign(Expr_Selector<>(), dest.impl(), alpha, arg_1.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  // from: to:
  //

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //
  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  //
  template <typename IMPL_DEST, typename IMPL_ARG_1>
  std::integral_constant<Expr_Selector_Enum, Expr_Selector_Enum::Generic>
  assign(const Expr_Selector<Expr_Selector_Enum::Generic>&,
         Dense_Matrix_Crtp<IMPL_DEST>& dest,                        // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1> alpha,  // alpha
         const Dense_Matrix_Crtp<IMPL_ARG_1>& arg_1                 // arg_1
  )
  {
    // Basic implementation for test
    fill_indexed(
        [alpha, &arg_1](const std::size_t i, const std::size_t j) { return alpha * arg_1(i, j); },
        dest);

    return {};
  }

  // //================================================================
  // //  Implementation: Generic
  // //================================================================
  // //
  // //
  // template <typename IMPL_DEST>
  // Expr_Selector_Enum
  // assign(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
  //      Dense_Matrix_Crtp<IMPL_DEST>& dest,                  // dest
  //      _assign_t_,                                         // =
  //      const typename IMPL_DEST::element_type alpha,           // alpha
  //      _dest_t_                                        // dest
  // )
  // {
  //   if (alpha == 0)
  //   {
  //     return assign(dest,  0);
  //   }

  //   if (alpha == 1)
  //   {
  //     return Expr_Selector_Enum::Generic;
  //   }

  //   if (alpha == -1)
  //   {
  //     transform([](const auto& dest_i) { return -dest_i; }, dest);
  //     return Expr_Selector_Enum::Generic;
  //   }

  //   transform([alpha](const auto& dest_i) { return dest_i * alpha; }, dest);

  //   return Expr_Selector_Enum::Generic;
  // }

  //================================================================
  //  Implementation: CBlas
  //================================================================
  //
  // #if (HAS_BLAS)

  // #endif

  //================================================================
  //  Implementation: Static
  //================================================================
  //
}

using namespace LinearAlgebra;

int
main()
{
  Matrix<double> M1;
  Tiny_Matrix<int, 2, 3> M2;
  static_assert(std::is_trivially_copyable_v<Tiny_Matrix<int, 2, 3>>);

  auto expression_2 = M1 + 4 * M2 * M1 * M2;
  auto expression   =  4 * M2;

  print(from_metaexpr_to_argument_tuple(expression));
  Detail::call_assign_from_metaexpr(M2, expression);
}
