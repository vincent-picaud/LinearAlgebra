// -*- compile-command: "g++ -std=c++17  poub.cpp && ./a.out"; -*-
#include <array>
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

  namespace Detail
  {
    template <typename ELEMENT_TYPE, typename... ARGS>
    struct Meta_Expression
    {
      static_assert(((not Is_Tuple_v<ARGS>)and...));  // sanity check

      using element_type = ELEMENT_TYPE;

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
  }  // Detail

  // auto
  // transpose(const Matrix& M0)
  // {
  // }
  template <typename A1_IMPL>
  auto operator*(const Element_Type_t<A1_IMPL>& A0, const Matrix_Crtp<A1_IMPL>& A1)
  {
    using element_type = Common_Element_Type_t<A1_IMPL>;

    return Detail::create_meta_expression(LinearAlgebra::Type<element_type>(), _product_, A0, A1);
  }

  template <typename A0_IMPL, typename A1_IMPL>
  auto operator*(const Matrix_Crtp<A0_IMPL>& A0, const Matrix_Crtp<A1_IMPL>& A1)
  {
    using element_type = Common_Element_Type_t<A0_IMPL, A1_IMPL>;

    return Detail::create_meta_expression(LinearAlgebra::Type<element_type>(), _product_, A0, A1);
  }

  template <typename ELEMENT_TYPE, typename... ARGS, typename A1_IMPL>
  auto operator*(const Detail::Meta_Expression<ELEMENT_TYPE, ARGS...>& A0,
                 const Matrix_Crtp<A1_IMPL>& A1)
  {
    using A0_type      = Detail::Meta_Expression<ELEMENT_TYPE, ARGS...>;
    using element_type = Common_Element_Type_t<A0_type, A1_IMPL>;

    return Detail::create_meta_expression(
        LinearAlgebra::Type<element_type>(),
        std::tuple_cat(std::tie(_product_), A0._args, std::tie(A1)));
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

}

using namespace LinearAlgebra;
int
main()
{
  Matrix<double> M1;
  Tiny_Matrix<int, 2, 3> M2;
  auto Meta_Expression = 4 * M1;
  //  auto Meta_Expression = M1 * M2 * M1 * M2;
  print(Meta_Expression);

  std::cout << "\nzob";
}
