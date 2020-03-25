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

      // element type is required to restrict operator overloading
      // involving scalar like α.M
      using element_type  = typename traits_type::element_type;
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

      using element_type  = typename traits_type::element_type;
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

      using element_type  = typename traits_type::element_type;
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
    template <typename ELEMENT_TYPE, typename BINARY_OPERATOR_TYPE, typename ARG_0_TYPE,
              typename ARG_1_TYPE>
    class MetaExpr_BinaryOp;
  }

  template <typename ELEMENT_TYPE, typename BINARY_OPERATOR_TYPE, typename ARG_0_TYPE,
            typename ARG_1_TYPE>
  struct Crtp_Type_Traits<
      Detail::MetaExpr_BinaryOp<ELEMENT_TYPE, BINARY_OPERATOR_TYPE, ARG_0_TYPE, ARG_1_TYPE>>
  {
    using element_type  = ELEMENT_TYPE;
    using operator_type = BINARY_OPERATOR_TYPE;
  };

  namespace Detail
  {
    template <typename ELEMENT_TYPE, typename Op, typename ARG_0, typename ARG_1>
    class MetaExpr_BinaryOp final
        : public MetaExpr_BinaryOp_Crtp<MetaExpr_BinaryOp<ELEMENT_TYPE, Op, ARG_0, ARG_1>>
    {
      ///////////
      // Types //
      ///////////
      //
     public:
      using base_type = MetaExpr_BinaryOp_Crtp<MetaExpr_BinaryOp<ELEMENT_TYPE, Op, ARG_0, ARG_1>>;

      using element_type  = typename base_type::element_type;
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
                  Detail::MetaExpr_BinaryOp<double, _product_t_, Matrix<double>, Vector<double>>>);

  }  // Detail

  //////////////////////////////////////////////////////////////////
  // Operators overloading
  //////////////////////////////////////////////////////////////////
  //
  // Allowed arguments (beside scalar)
  //
  template <typename... IMPL>
  constexpr auto Is_Supported_MetaExpr_Argument_v =
      ((Is_Crtp_Interface_Of_v<Detail::MetaExpr_Crtp, IMPL> or
        Is_Crtp_Interface_Of_v<Vector_Crtp, IMPL> or
        Is_Crtp_Interface_Of_v<Matrix_Crtp, IMPL>)and...);

  // Product
  //================================================================
  //
  template <typename A0_IMPL, typename A1_IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A0_IMPL, A1_IMPL>,
                   Detail::MetaExpr_BinaryOp<Common_Element_Type_t<A0_IMPL, A1_IMPL>, _product_t_,
                                             A0_IMPL, A1_IMPL>>
  operator*(const Crtp<A0_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0.impl(), arg_1.impl()};
  }

  // scalar * Crpt<> product
  template <typename A1_IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A1_IMPL>,
                   Detail::MetaExpr_BinaryOp<Element_Type_t<A1_IMPL>, _product_t_,
                                             Element_Type_t<A1_IMPL>, A1_IMPL>>
  operator*(const Element_Type_t<A1_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0, arg_1.impl()};
  }

  //
  //================================================================
  // Plus
  //================================================================
  //
  template <typename A0_IMPL, typename A1_IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A0_IMPL, A1_IMPL>,
                   Detail::MetaExpr_BinaryOp<Common_Element_Type_t<A0_IMPL, A1_IMPL>, _plus_t_,
                                             A0_IMPL, A1_IMPL>>
  operator+(const Crtp<A0_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0.impl(), arg_1.impl()};
  }

  //////////////////////////////////////////////////////////////////

  template <typename... ARGS>
  void
  expr(const ARGS&...)
  {
    std::cerr << __PRETTY_FUNCTION__ << std::endl;
  }

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
main()
{
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
  compute(M2, expression_2);
  //expr(M2, _assign_, 2, _matrix_0_);
}
