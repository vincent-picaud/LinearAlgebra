// [[file:how_to_new_vector.org]]
// [BEGIN_how_to_new_vector.cpp]
#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/metaexpr/metaexpr.hpp"  // required by V+V etc...

// CAVEAT: is not enough:
// #include "LinearAlgebra/expr/expr.hpp"
// each expression must be include individually
#include "LinearAlgebra/expr/V0_assign_alpha_V1_plus_V2.hpp"

#include <iostream>

namespace LinearAlgebra
{
  // [BEGIN_vector_type]
  //
  // This is the strict minimum to define a new vector type that inherits from =Vector_Crtp=.
  //
  template <typename T>
  class Minimal_Vector;

  template <typename T>
  struct Crtp_Type_Traits<Minimal_Vector<T>>
  {
    using element_type = T;
    using size_type    = std::size_t;
  };

  template <typename T>
  class Minimal_Vector : public Vector_Crtp<Minimal_Vector<T>>
  {
   public:
    using base_type    = Vector_Crtp<Minimal_Vector<T>>;
    using element_type = typename base_type::element_type;
    using size_type    = typename base_type::size_type;

   protected:
    // My data
    std::size_t _number;

   public:
    explicit Minimal_Vector(const size_t number) : _number(number) {}

    // Provides operator=() -> must be followed by impl_assign
    // implementation (see protected: section)
    VMT_ASSIGNMENT_OPERATOR(Minimal_Vector);

   protected:
    friend base_type;

    size_type
    impl_size() const
    {
      return 0;
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
      std::cout << __PRETTY_FUNCTION__ << std::endl;
      Detail::call_assign_from_MetaExpr(*this, metaExpr);  // code here ...
      return *this;
    }

    template <typename T_OTHER>
    Minimal_Vector<T>&
    impl_assign(const Minimal_Vector<T_OTHER>&)  // Compatible Vector
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
      // code here ...
      return *this;
    }

    Minimal_Vector<T>&
    impl_assign(const element_type&)  // Compatible Scalar
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
      // code here ...
      return *this;
    }
  };

  // [END_vector_type]

  // If no generic fill() function etc... you can always specialize the right assign
  //
  // CAVEAT: as both brach X2 or _lhs_ are tested in a dynamic way,
  // one must provide both implementation (otherwise you have a
  // compile time error)
  //
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Minimal_Vector<X0_IMPL>& X0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Minimal_Vector<X1_IMPL>& X1,
         const Minimal_Vector<X2_IMPL>& X2)

  {
    assert(0);

    // DEBUG_SET_SELECTED(selected);
  }
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Minimal_Vector<X0_IMPL>& X0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Minimal_Vector<X1_IMPL>& X1,
         const _lhs_t_)

  {
    assert(0);

    // DEBUG_SET_SELECTED(selected);
  }

}  // namespace LinearAlgebra

// [BEGIN_main]
using namespace LinearAlgebra;

int
main()
{
  Minimal_Vector<int> U(5), V(5), W(5);

  U = V + W;

  std::cout << V.size();
}
// [END_main]
// [END_how_to_new_vector.cpp]
