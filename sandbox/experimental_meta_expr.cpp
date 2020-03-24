// -*- compile-command: "g++ -std=c++17  poub.cpp && ./a.out"; -*-
#include <array>
#include <iostream>
#include <memory>
#include <tuple>
#include <type_traits>

#include <LinearAlgebra/utils/type.hpp>

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

// For sanity checks
template <typename>
struct Is_Tuple : std::false_type
{
};

template <typename... T>
struct Is_Tuple<std::tuple<T...>> : std::true_type
{
};

template <typename... T>
constexpr auto Is_Tuple_v = Is_Tuple<T...>::value;
// For sanity checks END

template <typename ELEMENT_TYPE, typename... ARGS>
struct Meta_Expression
{
  static_assert(((not Is_Tuple_v<ARGS>)and...));

  std::tuple<const ARGS&...> _args;
  Meta_Expression(const ARGS&... args) : _args(args...) {}
  Meta_Expression(const std::tuple<const ARGS&...> args) : _args(std::move(args)) {}
};

template <typename ELEMENT_TYPE, typename... ARGS>
constexpr auto
create_meta_expression(const LinearAlgebra::Type<ELEMENT_TYPE>, const ARGS&... args) noexcept
{
  return Meta_Expression<ELEMENT_TYPE, ARGS...>(args...);
}
template <typename ELEMENT_TYPE, typename... ARGS>
constexpr auto
create_meta_expression(const LinearAlgebra::Type<ELEMENT_TYPE>,
                       const std::tuple<const ARGS&...>& args) noexcept
{
  return Meta_Expression<ELEMENT_TYPE, ARGS...>(args);
}

auto
transpose(const Matrix& M0)
{
}

auto operator*(const Matrix& M0, const Matrix& M1)
{
  return create_meta_expression(LinearAlgebra::Type<int>(), _product_t_(), M0, M1);
  //  return Meta_Expression<int>{_product_t_(), M0, M1};
}

template <typename ELEMENT_TYPE, typename... ARGS>
auto operator*(const Meta_Expression<ELEMENT_TYPE, ARGS...>& A0, const Matrix& A1)
{
  constexpr auto op = _product_t_();

  return create_meta_expression(LinearAlgebra::Type<int>(),
                                std::tuple_cat(std::tie(op), A0._args, std::tie(A1)));

  //  return Meta_Expression<int>{std::tuple_cat(std::tie(op), A0._args, std::tie(A1))};
}

// template <typename F, typename A0, typename A1>
// auto expand(const Meta_Expression<F, A0, A1>& expr)
// {
// }

template <typename T>
void
print(const T&)
{
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
}

//
struct A
{
  const int& _n;
};

A
foo(const int& n)
{
  return A{n};
};

int
main()
{
  Matrix M1, M2;
  // auto   Meta_Expression = M1 * M2;
  auto Meta_Expression = M1 * M2 * M1 * M2;
  print(Meta_Expression);

  auto a = foo(5);
  auto b = a;
  std::cout << b._n;
}
