// [[file:call_assign_demo.org]]
// [BEGIN_call_assign_demo.cpp]
#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/utils/crtp.hpp"
#include "LinearAlgebra/utils/type.hpp"

#include <iostream>
namespace LinearAlgebra
{
  // [BEGIN_vector_type]
  //
  // This is the strict minimum to define a new vector inheritings [[id:de8a0a1f-0ae5-495d-a839-a7a5d1199091][The
  // =Dense_Vector_Crtp= class]].
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
  };

  // [END_vector_type]
}  // namespace LinearAlgebra

using namespace LinearAlgebra;

int
main()
{
  Minimal_Vector<int> V(5);

  std::cout << V.size();
}
// [END_call_assign_demo.cpp]
