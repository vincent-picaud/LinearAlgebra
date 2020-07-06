// [[file:call_assign_demo.org]]
// [BEGIN_call_assign_demo.cpp]
#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/dense/vmt_assignment_operator_define.hpp"
#include "LinearAlgebra/metaexpr/call_assign_from_metaexpr.hpp"
#include "LinearAlgebra/metaexpr/metaexpr_crtp.hpp"
#include "LinearAlgebra/vector.hpp"

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
      // code here ...
      return *this;
    }

    template <typename T_OTHER>
    Minimal_Vector<T>&
    impl_assign(const Minimal_Vector<T_OTHER>&)  // Compatible Vector
    {
      // code here ...
      return *this;
    }

    Minimal_Vector<T>&
    impl_assign(const element_type&)  // Compatible Scalar
    {
      // code here ...
      return *this;
    }
  };

  // [END_vector_type]
}  // namespace LinearAlgebra

using namespace LinearAlgebra;

int
main()
{
  Minimal_Vector<int> V(5);

  //  V = V + V;

  std::cout << V.size();
}
// [END_call_assign_demo.cpp]
