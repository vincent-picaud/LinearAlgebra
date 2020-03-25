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

#include "LinearAlgebra/utils/crtp.hpp"

namespace LinearAlgebra
{
  namespace Detail
  {
    //////////////////////////////////////////////////////////////////
    // Base class of all operators
    //////////////////////////////////////////////////////////////////
    //
    template <typename IMPL>
    class MetaExpr_Crtp : public Crtp_Find_Impl<MetaExpr_Crtp, IMPL, Crtp>
    {
      ///////////
      // Types //
      ///////////
      //
     public:
      using base_type = Crtp_Find_Impl<MetaExpr_Crtp, IMPL, Crtp>;
      using base_type::impl;

      using exact_type  = typename base_type::exact_type;
      using traits_type = typename base_type::traits_type;

      using operator_type = typename traits_type::operator_type;
    };

    //////////////////////////////////////////////////////////////////
    // Base class of all unary operators
    //////////////////////////////////////////////////////////////////
    //
    template <typename IMPL>
    class MetaExpr_UnaryOp_Crtp : public Crtp_Find_Impl<MetaExpr_UnaryOp_Crtp, IMPL, MetaExpr_Crtp>
    {
      ///////////
      // Types //
      ///////////
      //
     public:
      using base_type = Crtp_Find_Impl<MetaExpr_UnaryOp_Crtp, IMPL, Vector_Crtp>;

      using exact_type  = typename base_type::exact_type;
      using traits_type = typename base_type::traits_type;

      using operator_type = typename base_type::operator_type;
    };

    //////////////////////////////////////////////////////////////////
    // Base class of all binary operators
    //////////////////////////////////////////////////////////////////
    //
    template <typename IMPL>
    class MetaExpr_BinaryOp_Crtp
        : public Crtp_Find_Impl<MetaExpr_BinaryOp_Crtp, IMPL, MetaExpr_Crtp>
    {
      ///////////
      // Types //
      ///////////
      //
     public:
      using base_type = Crtp_Find_Impl<MetaExpr_BinaryOp_Crtp, IMPL, MetaExpr_Crtp>;

      using exact_type  = typename base_type::exact_type;
      using traits_type = typename base_type::traits_type;

      using operator_type = typename base_type::operator_type;

     public:
      ////////////////////
      // Crtp Interface //
      ////////////////////
      //
      constexpr auto&
      arg_0() const noexcept
      {
        return base_type::impl().impl_arg_0();
      }

      constexpr auto&
      arg_1() const noexcept
      {
        return base_type::impl().impl_arg_1();
      }
    };
  }  // Detail

  //////////////////////////////////////////////////////////////////
  // Binary operator default implementation
  //////////////////////////////////////////////////////////////////

  namespace Detail
  {
    template <typename BINARY_OPERATOR_TYPE, typename ARG_0_TYPE, typename ARG_1_TYPE>
    class MetaExpr_BinaryOp;
  }

  template <typename BINARY_OPERATOR_TYPE, typename ARG_0_TYPE, typename ARG_1_TYPE>
  struct Crtp_Type_Traits<Detail::MetaExpr_BinaryOp<BINARY_OPERATOR_TYPE, ARG_0_TYPE, ARG_1_TYPE>>
  {
    using operator_type = BINARY_OPERATOR_TYPE;
  };

  namespace Detail
  {
    template <typename Op, typename ARG_0, typename ARG_1>
    class MetaExpr_BinaryOp final
        : public MetaExpr_BinaryOp_Crtp<MetaExpr_BinaryOp<Op, ARG_0, ARG_1>>
    {
      ///////////
      // Types //
      ///////////
      //
     public:
      using base_type = MetaExpr_BinaryOp_Crtp<MetaExpr_BinaryOp<Op, ARG_0, ARG_1>>;

      using operator_type = typename base_type::operator_type;

      /////////////
      // Members //
      /////////////
      //
     protected:
      const ARG_0& _arg_0;
      const ARG_1& _arg_1;

      //////////////////
      // Constructors //
      //////////////////
      //
     public:
      constexpr MetaExpr_BinaryOp(const ARG_0& arg_0, const ARG_1& arg_1) noexcept
          : _arg_0(arg_0), _arg_1(arg_1)
      {
      }

      /////////////////////////
      // Crtp Implementation //
      /////////////////////////
      //
     protected:
      friend base_type;
      friend typename base_type::base_type;

      constexpr auto&
      impl_arg_0() const noexcept
      {
        return _arg_0;
      }

      constexpr auto&
      impl_arg_1() const noexcept
      {
        return _arg_1;
      }
    };
    static_assert(std::is_trivially_copyable_v<
                  Detail::MetaExpr_BinaryOp<_product_t_, Matrix<double>, Vector<double>>>);

  }  // Detail

  // template <typename Op, typename ARG_0, typename ARG_1>
  // struct BinaryOp
  // {
  //   const ARG_0& _arg_0;
  //   const ARG_1& _arg_1;
  //   BinaryOp(const ARG_0& arg_0, const ARG_1& arg_1) : _arg_0(arg_0), _arg_1(arg_1) {}
  // };

  //////////////////////////////////////////////////////////////////
  // Operators overloading
  //////////////////////////////////////////////////////////////////

  //================================================================
  // Product
  //================================================================
  //
  template <typename A0_IMPL, typename A1_IMPL>
  auto operator*(const Matrix_Crtp<A0_IMPL>& arg_0, const Matrix_Crtp<A1_IMPL>& arg_1)
  {
    return Detail::MetaExpr_BinaryOp<_product_t_, A0_IMPL, A1_IMPL>{arg_0.impl(), arg_1.impl()};
  }

  template <typename ARG_0_IMPL, typename A1_IMPL>
  auto operator*(const Detail::MetaExpr_Crtp<ARG_0_IMPL>& arg_0, const Matrix_Crtp<A1_IMPL>& arg_1)
  {
    return Detail::MetaExpr_BinaryOp<_product_t_, ARG_0_IMPL, A1_IMPL>{arg_0.impl(), arg_1.impl()};
  }

  //================================================================
  // Plus
  //================================================================
  //
  template <typename A0_IMPL, typename A1_IMPL>
  auto
  operator+(const Matrix_Crtp<A0_IMPL>& arg_0, const Matrix_Crtp<A1_IMPL>& arg_1)
  {
    return Detail::MetaExpr_BinaryOp<_plus_t_, A0_IMPL, A1_IMPL>{arg_0.impl(), arg_1.impl()};
  }

  template <typename ARG_0_IMPL, typename A1_IMPL>
  auto
  operator+(const Detail::MetaExpr_Crtp<ARG_0_IMPL>& arg_0, const Matrix_Crtp<A1_IMPL>& arg_1)
  {
    return Detail::MetaExpr_BinaryOp<_plus_t_, ARG_0_IMPL, A1_IMPL>{arg_0.impl(), arg_1.impl()};
  }

  template <typename ARG_0_IMPL, typename ARG_1_IMPL>
  auto
  operator+(const Matrix_Crtp<ARG_0_IMPL>& arg_0, const Detail::MetaExpr_Crtp<ARG_1_IMPL>& arg_1)
  {
    return Detail::MetaExpr_BinaryOp<_plus_t_, ARG_0_IMPL, ARG_1_IMPL>{arg_0.impl(), arg_1.impl()};
  }

  //////////////////////////////////////////////////////////////////

  template <typename... ARGS>
  void
  expr(const ARGS&...)
  {
    std::cerr << __PRETTY_FUNCTION__ << std::endl;
  }

  // Everything that's not an Detail::MetaExpr_Crtp is considered as a
  // final node
  template <typename T>
  inline constexpr std::enable_if_t<not Is_Crtp_Interface_Of<Detail::MetaExpr_Crtp, T>::value,
                                    std::tuple<const T&>>
  expand(const T& t) noexcept
  {
    return {t};
  }

  template <typename IMPL>
  inline constexpr auto
  expand(const Detail::MetaExpr_BinaryOp_Crtp<IMPL>& expression_tree) noexcept
  {
    return std::tuple_cat(expand(expression_tree.arg_0()),
                          std::make_tuple(typename IMPL::operator_type()),
                          expand(expression_tree.arg_1()));
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
  static_assert(std::is_trivially_copyable_v<Tiny_Matrix<int, 2, 3>>);

  //auto expression = M1 * M2;
  auto expression = M2 + M1 * M2;
  //print(expression);
  auto expanded = expand(expression);
  //  print(expand(expression));
  // std::apply(expr, expanded);
  // From:https://stackoverflow.com/a/37100646/2001017
  //  std::apply([](auto&&... args) { expr(args...); }, expanded);

  // Call our expr
  std::apply([](auto&&... args) { expr(args...); }, expanded);
}
