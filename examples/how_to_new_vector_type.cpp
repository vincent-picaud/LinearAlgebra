// [[file:how_to_new_vector_type.org]]
// [BEGIN_how_to_new_vector.cpp]
#include "LinearAlgebra/dense/vector_crtp.hpp"

// [BEGIN_expr_include_caveat]
//
// These are the required includes.
//
// For Expression Templates, one needs:
#include "LinearAlgebra/metaexpr/metaexpr.hpp"

// For =assign()= function one needs to include *each individual*
// expressions. *It is not enough:* to simply include
// ="LinearAlgebra/expr/expr.hpp"= .
#include "LinearAlgebra/expr/V0_assign_alpha_V1_plus_V2.hpp"
#include "LinearAlgebra/expr/X_eq_aX_vector.hpp"
// [END_expr_include_caveat]

#include <iostream>
#include <ostream>
#include <type_traits>

namespace LinearAlgebra
{
  // [BEGIN_vector_type]
  //
  // You must start by defining the required types by specializing
  // =Crtp_Type_Traits=.
  //
  template <typename T>
  class Minimal_Vector;

  template <typename T>
  struct Crtp_Type_Traits<Minimal_Vector<T>>
  {
    using element_type = T;
    using size_type    = std::integral_constant<std::size_t, 2>;
  };

  // [DOC]
  //
  // Then define the vector class
  //
  template <typename T>
  class Minimal_Vector : public Vector_Crtp<Minimal_Vector<T>>
  {
   public:
    using base_type    = Vector_Crtp<Minimal_Vector<T>>;
    using element_type = typename base_type::element_type;
    using size_type    = typename base_type::size_type;

   protected:
    // My data
    std::array<T, size_type::value> _data;

   public:
    // [DOC]
    //
    // The most basic form of vector, =Vector_Crtp= does not impose
    // the existence of =operator[]=, by consequence you must provide
    // a way to access to data:
    //
    std::array<T, size_type::value>&
    data()
    {
      return _data;
    }
    const std::array<T, size_type::value>&
    data() const
    {
      return _data;
    }

    // [DOC]
    //
    // Provides =operator==
    //
    // Must be followed by impl_assign
    // implementation (see protected: section)
    //
    VMT_ASSIGNMENT_OPERATOR(Minimal_Vector);

    // [DOC]
    //
    // This section groups the methods (impl_XXX) you must overwrite.
    //
   protected:
    friend base_type;

    size_type
    impl_size() const
    {
      return {};
    }

    const Minimal_Vector&
    impl_as_const() const
    {
      return *this;
    }

    // VMT_ASSIGNMENT_OPERATOR most basic implementation
    //
    template <typename EXPR_IMPL>
    Minimal_Vector<T>&
    impl_assign(const Detail::MetaExpr_Crtp<EXPR_IMPL>& metaExpr)  // Expression Template
    {
      Detail::call_assign_from_MetaExpr(*this, metaExpr);
      return *this;
    }

    template <typename T_OTHER>
    Minimal_Vector<T>&
    impl_assign(const Minimal_Vector<T_OTHER>& other)  // Compatible Vector
    {
      _data[0] = other._data[0];
      _data[1] = other._data[1];

      return *this;
    }

    Minimal_Vector<T>&
    impl_assign(const element_type& alpha)  // Compatible Scalar
    {
      _data[0] = alpha;
      _data[1] = alpha;

      return *this;
    }

    // [DOC]
    //
    // Defines out to print vector
    //
    friend std::ostream&
    operator<<(std::ostream& out, const Minimal_Vector<T>& to_print)
    {
      out << "[" << to_print._data[0] << ", " << to_print._data[1] << "]";
      return out;
    }
  };
  // [END_vector_type]

  // [BEGIN_assign]
  //
  // If no generic =fill()=, =transform()=, ...  functions are
  // provided... you must specialize each assign functions
  //
  // CAVEAT: as both branches X2 or _lhs_ are tested in a dynamic way,
  // one must provide a *compilable* implementations for both versions
  // (otherwise you have a compile time error)
  //
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Minimal_Vector<X0_IMPL>& X0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Minimal_Vector<X1_IMPL>& X1,
         const Minimal_Vector<X2_IMPL>& X2)

  {
    X0.data()[0] = alpha.value() * X1.data()[0] + X2.data()[0];
    X0.data()[1] = alpha.value() * X1.data()[1] + X2.data()[1];

    DEBUG_SET_SELECTED(selected);
  }
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Minimal_Vector<X0_IMPL>& X0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Minimal_Vector<X1_IMPL>& X1,
         const _lhs_t_)

  {
    X0.data()[0] = alpha.value() * X1.data()[0] + X0.data()[0];
    X0.data()[1] = alpha.value() * X1.data()[1] + X0.data()[1];

    DEBUG_SET_SELECTED(selected);
  }
  // [END_assign]
}  // namespace LinearAlgebra

// [BEGIN_main]
using namespace LinearAlgebra;

int
main()
{
  Minimal_Vector<int> U, V, W;

  U = 1;
  V = 2;
  W = 3;

  std::cout << U << std::endl;

  // TODO: after having cleaned V=αW
  //
  // - must remove all tests like α==1 etc... which add extra
  //   complexity and are incompatible with AutoDiff for instance.
  // - must modify generic interface Dense_Vector_Crtp -> Vector_Crtp
  //   in order to let us use a generic fill method.
  //
  // U = 3 * V;
  //
  // std::cout << U << std::endl;

  U = V + W;

  std::cout << U << std::endl;

  U = W;

  std::cout << U << std::endl;
}
// [END_main]
// [END_how_to_new_vector.cpp]
