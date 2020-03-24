// -*- compile-command: "g++ -std=c++17  poub.cpp && ./a.out"; -*-
#include <array>
#include <iostream>
#include <memory>
#include <tuple>
#include <type_traits>

struct _plus_t_
{
};
struct _product_t_
{
};
struct _transpose_t_
{
};

struct Matrix
{
};
struct Vector
{
};

template <typename... ARGS>
struct Expression
{
  std::tuple<const ARGS&...> _args;
  Expression(const ARGS&... args) : _args(args...)
  {
  }
  Expression(const std::tuple<const ARGS&...> args) : _args(std::move(args))
  {
  }
};

auto transpose(const Matrix& M0)
{
}

auto operator*(const Matrix& M0, const Matrix& M1)
{
  return Expression{_product_t_(), M0, M1};
}

template <typename... ARGS>
auto operator*(const Expression<ARGS...>& A0, const Matrix& A1)
{
  constexpr auto op = _product_t_();
  return Expression{std::tuple_cat(std::tie(op), A0._args, std::tie(A1))};
}

template <typename F, typename A0, typename A1>
auto expand(const Expression<F, A0, A1>& expr)
{
}

template <typename T>
void print(const T&)
{
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
}

//
struct A
{
  const int& _n;
};

A foo(const int& n)
{
  return A{n};
};

int main()
{
  Matrix M1, M2;
  // auto   expression = M1 * M2;
  auto expression = M1 * M2 * M1 * M2;
  print(expression);

  auto a = foo(5);
  auto b = a;
  std::cout << b._n;
}

