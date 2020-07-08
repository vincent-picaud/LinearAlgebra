#pragma once

#include "LinearAlgebra/dense/vector_crtp.hpp"

// namespace LinearAlgebra
// {
//   struct LHS_Element_Type
//   {
//   };
// }  // namespace LinearAlgebra

// namespace std
// {
//   template <typename T>
//   struct common_type<T, LinearAlgebra::LHS_Element_Type>
//   {
//     using type = T;
//   };

//   // template <typename T>
//   // struct common_type<LinearAlgebra::LHS_Element_Type, T>
//   // {
//   //   using type = T;
//   // };

//   template <>
//   struct common_type<LinearAlgebra::LHS_Element_Type, LinearAlgebra::LHS_Element_Type>
//   {
//     using type = LinearAlgebra::LHS_Element_Type;
//   };

// }  // namespace std

namespace LinearAlgebra
{
  template <typename VECTOR_TYPE>
  class Vector_LHS;

  template <typename VECTOR_TYPE>
  struct Crtp_Type_Traits<Vector_LHS<VECTOR_TYPE>>
  {
    using element_type = typename VECTOR_TYPE::element_type;
    using size_type    = typename VECTOR_TYPE::size_type;
  };

  // TODO: matrix_lhs
  //
  template <typename VECTOR_TYPE>
  class Vector_LHS : public Vector_Crtp<Vector_LHS<VECTOR_TYPE>>
  {
    static_assert(Is_Crtp_Interface_Of_v<Vector_Crtp, VECTOR_TYPE>);

    // ////////////////
    // Types
    // ////////////////
    //
   public:
    using base_type   = Vector_Crtp<Vector_LHS<VECTOR_TYPE>>;
    using exact_type  = typename base_type::exact_type;
    using traits_type = typename base_type::traits_type;

    using element_type = typename traits_type::element_type;
    using size_type    = typename traits_type::size_type;

    // ////////////////
    // Members
    // ////////////////
    //
    const VECTOR_TYPE& _vector;

    // ////////////////
    // Constructors
    // ////////////////
    //
   public:
    Vector_LHS(const VECTOR_TYPE& vector) : _vector(vector) {}

    // ////////////////
    // Crtp Interface
    // ////////////////
    //
   public:
    size_type
    size() const
    {
      return _vector.size();
    }

    const Vector_LHS&
    as_const() const
    {
      return *this;
    }
  };

  template <typename IMPL>
  Vector_LHS<Vector_Crtp<IMPL>>
  lhs(const Vector_Crtp<IMPL>& vector)
  {
    return {vector};
  }
}  // namespace LinearAlgebra
