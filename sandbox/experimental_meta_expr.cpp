// -*- compile-command: "g++ -std=c++17  poub2.cpp && ./a.out"; -*-
#include <array>
#include <ccomplex>
#include <iostream>
#include <memory>
#include <tuple>
#include <type_traits>

#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/utils/type.hpp"
#include "LinearAlgebra/vector.hpp"

namespace LinearAlgebra
{
  template <typename Op, typename ARG_0, typename ARG_1>
  struct BinaryOp
  {
    const ARG_0& _arg_0;
    const ARG_1& _arg_1;
    BinaryOp(const ARG_0& arg_0, const ARG_1& arg_1) : _arg_0(arg_0), _arg_1(arg_1) {}
  };

  template <typename A0_IMPL, typename A1_IMPL>
  auto operator*(const Matrix_Crtp<A0_IMPL>& arg_0, const Matrix_Crtp<A1_IMPL>& arg_1)
  {
    return BinaryOp<_product_t_, Matrix_Crtp<A0_IMPL>, Matrix_Crtp<A1_IMPL>>{arg_0, arg_1};
  }

  template <typename ARG_0_Op, typename ARG_0_T0, typename ARG_0_T1, typename A1_IMPL>
  auto operator*(const BinaryOp<ARG_0_Op, ARG_0_T0, ARG_0_T1>& arg_0,
                 const Matrix_Crtp<A1_IMPL>& arg_1)
  {
    return BinaryOp<_product_t_, BinaryOp<ARG_0_Op, ARG_0_T0, ARG_0_T1>, Matrix_Crtp<A1_IMPL>>{
        arg_0, arg_1};
  }

  template <typename... ARGS>
  void
  expr(const ARGS&...)
  {
    std::cerr << __PRETTY_FUNCTION__ << std::endl;
  }

  template <typename T>
  auto
  expand(const T& t)
  {
    return std::tuple<const T&>(t);
  }

  template <typename Op, typename T0, typename T1>
  auto
  expand(const BinaryOp<Op, T0, T1>& expression_tree)
  {
    return std::tuple_cat(expand(expression_tree._arg_0), std::make_tuple(Op()),
                          expand(expression_tree._arg_1));
  }

  template <typename T>
  void
  print(const T&)
  {
    std::cerr << __PRETTY_FUNCTION__ << std::endl;
  }
}  // LinearAlgebra;

using namespace LinearAlgebra;

int
main()
{
  Matrix<double> M1;
  Tiny_Matrix<int, 2, 3> M2;

  // auto   expression = M1 * M2;
  auto expression = M1 * M2 * M1 * M2;
  print(expression);
  auto expanded = expand(expression);
  //  print(expand(expression));
  // std::apply(expr, expanded);
  // From:https://stackoverflow.com/a/37100646/2001017
  std::apply([](auto&&... args) { expr(args...); }, expanded);
}
