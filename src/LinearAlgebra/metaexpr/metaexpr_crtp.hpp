// MetaExpr stores an expression tree. By example binary operators are defined as:
//
//  template <typename ELEMENT_TYPE, typename Op, typename ARG_0,
//  typename ARG_1> class MetaExpr_BinaryOp
//
// Note: the main reason to use Crtp is to simplify function argument
// filtering (see operator_overloading part).
//
#pragma once

#include "LinearAlgebra/utils/crtp.hpp"
#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/dense/matrix_crtp.hpp"

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
      // operator type is mainly used by expand() function
      // its type value is an expr_tag 
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
    // static_assert(std::is_trivially_copyable_v<
    //               Detail::MetaExpr_BinaryOp<double, _product_t_, Matrix<double>, Vector<double>>>);
  
        
  }  // Detail
}
