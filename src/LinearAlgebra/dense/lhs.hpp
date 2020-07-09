// [[file:lhs.org]]
#pragma once

#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/dense/vector_crtp.hpp"

namespace LinearAlgebra
{
  // ////////////////////////////////////////////////////////////////
  // Vector
  // ////////////////////////////////////////////////////////////////
  //
  template <typename VECTOR_TYPE>
  class Vector_LHS;

  template <typename VECTOR_TYPE>
  struct Crtp_Type_Traits<Vector_LHS<VECTOR_TYPE>>
  {
    using element_type = typename VECTOR_TYPE::element_type;
    using size_type    = typename VECTOR_TYPE::size_type;
  };

  // [BEGIN_Vector_LHS]
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

    // Cannot be copied
    Vector_LHS& operator=(const Vector_LHS& vector) = delete;
    // [END_Vector_LHS]

    // ////////////////
    // Crtp Implementation
    // ////////////////
    //
   protected:
    friend base_type;

    size_type
    impl_size() const
    {
      return _vector.size();
    }
    // [BEGIN_Vector_LHS]
  };
  // [END_Vector_LHS]

  // [BEGIN_lhs]
  //
  // Returns a lhs Vector object
  //
  template <typename IMPL>
  Vector_LHS<Vector_Crtp<IMPL>>
  lhs(const Vector_Crtp<IMPL>& vector)
  {
    return {vector};
  }
  // [END_lhs]

  // ////////////////////////////////////////////////////////////////
  // Matrix
  // ////////////////////////////////////////////////////////////////
  //
  template <typename MATRIX_TYPE>
  class Matrix_LHS;

  template <typename MATRIX_TYPE>
  struct Crtp_Type_Traits<Matrix_LHS<MATRIX_TYPE>>
  {
    using element_type = typename MATRIX_TYPE::element_type;
    using I_size_type  = typename MATRIX_TYPE::I_size_type;
    using J_size_type  = typename MATRIX_TYPE::J_size_type;
  };

  // [BEGIN_Matrix_LHS]
  template <typename MATRIX_TYPE>
  class Matrix_LHS : public Matrix_Crtp<Matrix_LHS<MATRIX_TYPE>>
  {
    static_assert(Is_Crtp_Interface_Of_v<Matrix_Crtp, MATRIX_TYPE>);

    // ////////////////
    // Types
    // ////////////////
    //
   public:
    using base_type   = Matrix_Crtp<Matrix_LHS<MATRIX_TYPE>>;
    using exact_type  = typename base_type::exact_type;
    using traits_type = typename base_type::traits_type;

    using element_type = typename traits_type::element_type;
    using I_size_type  = typename traits_type::I_size_type;
    using J_size_type  = typename traits_type::J_size_type;

    // ////////////////
    // Members
    // ////////////////
    //
    const MATRIX_TYPE& _matrix;

    // ////////////////
    // Constructors
    // ////////////////
    //
   public:
    Matrix_LHS(const MATRIX_TYPE& matrix) : _matrix(matrix) {}

    // Cannot be copied
    Matrix_LHS& operator=(const Matrix_LHS& matrix) = delete;
    // [END_Matrix_LHS]

    // ////////////////
    // Crtp Implementation
    // ////////////////
    //
   public:
    I_size_type
    impl_I_size() const
    {
      return _matrix.I_size();
    }

    J_size_type
    impl_J_size() const
    {
      return _matrix.J_size();
    }

    // [BEGIN_Matrix_LHS]
  };
  // [END_Matrix_LHS]

  // [BEGIN_lhs]
  //
  // Returns a lhs Matrix object
  //
  template <typename IMPL>
  Matrix_LHS<Matrix_Crtp<IMPL>>
  lhs(const Matrix_Crtp<IMPL>& matrix)
  {
    return {matrix};
  }
  // [END_lhs]

}  // namespace LinearAlgebra
