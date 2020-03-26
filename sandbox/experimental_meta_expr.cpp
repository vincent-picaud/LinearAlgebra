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
#include "LinearAlgebra/utils/type.hpp"
#include "LinearAlgebra/vector.hpp"

#include "LinearAlgebra/utils/crtp.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////

  // CAVEAT: as we test existance of expr function by Is_Complete must return something different of void
  // template <typename... ARGS>
  // void
  // expr(const ARGS&...)
  // {
  //   //    std::cerr << __PRETTY_FUNCTION__ << std::endl;

  //   static_assert(Always_False_v<ARGS...>,
  //                 "Undefined implementation");  // <- ne marche pas car capte tout
  // }

  // Everything that's not a Detail::MetaExpr_Crtp is considered as a
  // final node
  template <typename T>
  inline constexpr std::enable_if_t<not Is_Crtp_Interface_Of<Detail::MetaExpr_Crtp, T>::value,
                                    std::tuple<const T&>>
  expand(const T& t) noexcept
  {
    return {t};
  }

  // TODO add Unary op
  template <typename IMPL>
  inline constexpr auto
  expand(const Detail::MetaExpr_BinaryOp_Crtp<IMPL>& expression_tree) noexcept
  {
    // Attention: our convention is to not explicitly write down "_product_"
    if constexpr (std::is_same_v<typename Detail::MetaExpr_BinaryOp_Crtp<IMPL>::operator_type,
                                 _product_t_>)
    {
      return std::tuple_cat(expand(expression_tree.arg_0()), expand(expression_tree.arg_1()));
    }
    else
    {
      return std::tuple_cat(expand(expression_tree.arg_0()),
                            std::make_tuple(typename IMPL::operator_type()),
                            expand(expression_tree.arg_1()));
    }
  }

  // Functions to use in Vector/Matrix interface
  // -> here we only define the Matrix case

  template <typename M_DEST_IMPL, typename... ARGS>
  void
  compute(Matrix_Crtp<M_DEST_IMPL>& M_dest, const std::tuple<ARGS...>& args_as_tuple)
  {
    std::apply([&](const auto&... args) { expr(M_dest, _assign_, args...); }, args_as_tuple);
  }

  template <typename M_DEST_IMPL, typename SRC_IMPL>
  void
  compute(Matrix_Crtp<M_DEST_IMPL>& M_dest, const Detail::MetaExpr_Crtp<SRC_IMPL>& metaExpr)
  {
    compute(M_dest, expand(metaExpr.impl()));
  }

  //================================================================

  template <typename T>
  void
  print(const T&)
  {
    std::cerr << __PRETTY_FUNCTION__ << std::endl;
  }
}  // LinearAlgebra;

using namespace LinearAlgebra;

int
foo(double)
{
  return 0;
}

int
main()
{
  //  static_assert(Is_Complete_v<decltype(foo(5))>);
  static_assert(std::is_invocable_v<decltype(foo), double>);

  Matrix<double> M1;
  Tiny_Matrix<int, 2, 3> M2;
  static_assert(std::is_trivially_copyable_v<Tiny_Matrix<int, 2, 3>>);

  auto expression_2 = M2 * M1 * M2;
  auto expression   = 4 * M2 + 5 * M1;
  //print(expression);
  auto expanded = expand(expression);
  print(expand(expression));
  // std::apply(expr, expanded);
  // From:https://stackoverflow.com/a/37100646/2001017
  //  std::apply([](auto&&... args) { expr(args...); }, expanded);

  // Call our expr
  // std::apply([](auto&&... args) { expr(args...); }, expanded);

  //std::apply([&M2](const auto&... args) { expr(M2, _assign_, args...); }, expanded);
  //compute(M2, expression_2);
  expr(M2, _assign_, 2, _matrix_0_);
}
