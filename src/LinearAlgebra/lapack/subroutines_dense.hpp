//
// Wraps "subroutines" with dense (vector/matrix) objects
//
#pragma once

// Note: this a quite "abstract" header, hence we include "lapack.hpp"
// and dense vector & matrix headers
//

#include "LinearAlgebra/lapack/lapack.hpp"
#include "LinearAlgebra/lapack/to_lapack_transpose.hpp"
#include "LinearAlgebra/lapack/to_lapack_uplo.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

//#include "LinearAlgebra/utils/sfinae_vmt_helpers.hpp"

namespace LinearAlgebra::Lapack
{
  //////////////////////////////////////////////////////////////////
  // gels
  //////////////////////////////////////////////////////////////////
  //
  template <Matrix_Unary_Op_Enum OP,
            typename MA_IMPL,
            typename MB_IMPL,
            typename = std::enable_if_t<Support_Lapack_Transpose_v<OP>>>
  [[nodiscard]] auto
  gels(const _matrix_unary_op_t_<OP>, Dense_Matrix_Crtp<MA_IMPL>& A, Dense_Matrix_Crtp<MB_IMPL>& B)
      -> std::enable_if_t<
          Always_True_v<decltype(Lapack::gels(Lapack::Lapack_Order_Enum::Column_Major,
                                              Lapack::To_Lapack_Transpose_v<OP>,
                                              A.I_size(),
                                              A.J_size(),
                                              B.J_size(),
                                              A.data(),
                                              A.leading_dimension(),
                                              B.data(),
                                              B.leading_dimension()))>
              //
              and
              //
              Is_Full_Matrix_v<MA_IMPL>
              //
              and
              //
              Is_Full_Matrix_v<MB_IMPL>,
          // return type
          lapack_int>
  {
    return Lapack::gels(Lapack::Lapack_Order_Enum::Column_Major,
                        Lapack::To_Lapack_Transpose_v<OP>,
                        A.I_size(),
                        A.J_size(),
                        B.J_size(),
                        A.data(),
                        A.leading_dimension(),
                        B.data(),
                        B.leading_dimension());
  }

  template <Matrix_Unary_Op_Enum OP,
            typename MA_IMPL,
            typename VB_IMPL,
            typename = std::enable_if_t<Support_Lapack_Transpose_v<OP>>>
  [[nodiscard]] auto
  gels(const _matrix_unary_op_t_<OP>, Dense_Matrix_Crtp<MA_IMPL>& A, Dense_Vector_Crtp<VB_IMPL>& B)
      -> std::enable_if_t<
          Always_True_v<decltype(Lapack::gels(Lapack::Lapack_Order_Enum::Column_Major,
                                              Lapack::To_Lapack_Transpose_v<OP>,
                                              A.I_size(),
                                              A.J_size(),
                                              1,
                                              A.data(),
                                              A.leading_dimension(),
                                              B.data(),
                                              A.I_size()))>
              //
              and
              //
              Is_Full_Matrix_v<MA_IMPL>,
          // return type
          lapack_int>
  {
    if (B.increment() == 1)
    {
      return Lapack::gels(Lapack::Lapack_Order_Enum::Column_Major,
                          Lapack::To_Lapack_Transpose_v<OP>,
                          A.I_size(),
                          A.J_size(),
                          1,
                          A.data(),
                          A.leading_dimension(),
                          B.data(),
                          A.I_size());
    }

    // Must copy B to have
    auto B_cpy = similar(B);
    B_cpy      = B;
    assert(B_cpy.increment() == 1);

    return Lapack::gels(Lapack::Lapack_Order_Enum::Column_Major,
                        Lapack::To_Lapack_Transpose_v<OP>,
                        A.I_size(),
                        A.J_size(),
                        1,
                        A.data(),
                        A.leading_dimension(),
                        B_cpy.data(),
                        A.I_size());
  }

  //////////////////////////////////////////////////////////////////
  // potrf
  //////////////////////////////////////////////////////////////////
  //
  template <typename IMPL, typename = std::enable_if_t<Support_Lapack_UpLo_v<IMPL>>>
  [[nodiscard]] auto
  potrf(Dense_Matrix_Crtp<IMPL>& M) -> std::enable_if_t<
      Always_True_v<decltype(Lapack::potrf(Lapack::Lapack_Order_Enum::Column_Major,
                                           Lapack::To_Lapack_UpLo_v<IMPL>,
                                           M.I_size(),
                                           M.data(),
                                           M.leading_dimension()))>
          //
          and
          //
          (Is_Hermitian_Matrix_v<IMPL> or Is_Symmetric_Matrix_v<IMPL>),
      // return type
      lapack_int>
  {
    return Lapack::potrf(Lapack::Lapack_Order_Enum::Column_Major,
                         Lapack::To_Lapack_UpLo_v<IMPL>,
                         M.I_size(),
                         M.data(),
                         M.leading_dimension());
  }

  //////////////////////////////////////////////////////////////////
  // potrs & posv
  //////////////////////////////////////////////////////////////////
  //
  //================================================================
  // potrs
  //================================================================

  template <typename MA_IMPL,
            typename MB_IMPL,
            typename = std::enable_if_t<Support_Lapack_UpLo_v<MA_IMPL>>>
  [[nodiscard]] auto
  potrs(Dense_Matrix_Crtp<MA_IMPL>& A, Dense_Matrix_Crtp<MB_IMPL>& B) -> std::enable_if_t<
      Always_True_v<decltype(Lapack::potrs(Lapack::Lapack_Order_Enum::Column_Major,
                                           Lapack::To_Lapack_UpLo_v<MA_IMPL>,
                                           A.I_size(),
                                           B.J_size(),
                                           A.data(),
                                           A.leading_dimension(),
                                           B.data(),
                                           B.leading_dimension()))>
          //
          and
          //
          (Is_Symmetric_Matrix_v<MA_IMPL> or Is_Hermitian_Matrix_v<MA_IMPL>)
          //
          and
          //
          Is_Full_Matrix_v<MB_IMPL>,
      // return type
      lapack_int>
  {
    return Lapack::potrs(Lapack::Lapack_Order_Enum::Column_Major,
                         Lapack::To_Lapack_UpLo_v<MA_IMPL>,
                         A.I_size(),
                         B.J_size(),
                         A.data(),
                         A.leading_dimension(),
                         B.data(),
                         B.leading_dimension());
  }

  template <typename MA_IMPL,
            typename VB_IMPL,
            typename = std::enable_if_t<Support_Lapack_UpLo_v<MA_IMPL>>>
  [[nodiscard]] auto
  potrs(Dense_Matrix_Crtp<MA_IMPL>& A, Dense_Vector_Crtp<VB_IMPL>& B) -> std::enable_if_t<
      Always_True_v<decltype(Lapack::potrs(Lapack::Lapack_Order_Enum::Column_Major,
                                           Lapack::To_Lapack_UpLo_v<MA_IMPL>,
                                           A.I_size(),
                                           1,
                                           A.data(),
                                           A.leading_dimension(),
                                           B.data(),
                                           A.I_size()))>
          //
          and
          //
          (Is_Symmetric_Matrix_v<MA_IMPL> or Is_Hermitian_Matrix_v<MA_IMPL>),
      // return type
      lapack_int>
  {
    if (B.increment() == 1)
    {
      return Lapack::potrs(Lapack::Lapack_Order_Enum::Column_Major,
                           Lapack::To_Lapack_UpLo_v<MA_IMPL>,
                           A.I_size(),
                           1,
                           A.data(),
                           A.leading_dimension(),
                           B.data(),
                           A.I_size());
    }

    // Must copy B to have
    auto B_cpy = similar(B);
    B_cpy      = B;
    assert(B_cpy.increment() == 1);

    return Lapack::potrs(Lapack::Lapack_Order_Enum::Column_Major,
                         Lapack::To_Lapack_UpLo_v<MA_IMPL>,
                         A.I_size(),
                         1,
                         A.data(),
                         A.leading_dimension(),
                         B_cpy.data(),
                         A.I_size());
  }

  //================================================================
  // posv
  //================================================================

  template <typename MA_IMPL,
            typename MB_IMPL,
            typename = std::enable_if_t<Support_Lapack_UpLo_v<MA_IMPL>>>
  [[nodiscard]] auto
  posv(Dense_Matrix_Crtp<MA_IMPL>& A, Dense_Matrix_Crtp<MB_IMPL>& B) -> std::enable_if_t<
      Always_True_v<decltype(Lapack::posv(Lapack::Lapack_Order_Enum::Column_Major,
                                          Lapack::To_Lapack_UpLo_v<MA_IMPL>,
                                          A.I_size(),
                                          B.J_size(),
                                          A.data(),
                                          A.leading_dimension(),
                                          B.data(),
                                          B.leading_dimension()))>
          //
          and
          //
          (Is_Symmetric_Matrix_v<MA_IMPL> or Is_Hermitian_Matrix_v<MA_IMPL>)
          //
          and
          //
          Is_Full_Matrix_v<MB_IMPL>,
      // return type
      lapack_int>
  {
    return Lapack::posv(Lapack::Lapack_Order_Enum::Column_Major,
                        Lapack::To_Lapack_UpLo_v<MA_IMPL>,
                        A.I_size(),
                        B.J_size(),
                        A.data(),
                        A.leading_dimension(),
                        B.data(),
                        B.leading_dimension());
  }

  template <typename MA_IMPL,
            typename VB_IMPL,
            typename = std::enable_if_t<Support_Lapack_UpLo_v<MA_IMPL>>>
  [[nodiscard]] auto
  posv(Dense_Matrix_Crtp<MA_IMPL>& A, Dense_Vector_Crtp<VB_IMPL>& B) -> std::enable_if_t<
      Always_True_v<decltype(Lapack::posv(Lapack::Lapack_Order_Enum::Column_Major,
                                          Lapack::To_Lapack_UpLo_v<MA_IMPL>,
                                          A.I_size(),
                                          1,
                                          A.data(),
                                          A.leading_dimension(),
                                          B.data(),
                                          A.I_size()))>
          //
          and
          //
          (Is_Symmetric_Matrix_v<MA_IMPL> or Is_Hermitian_Matrix_v<MA_IMPL>),
      // return type
      lapack_int>
  {
    if (B.increment() == 1)
    {
      return Lapack::posv(Lapack::Lapack_Order_Enum::Column_Major,
                          Lapack::To_Lapack_UpLo_v<MA_IMPL>,
                          A.I_size(),
                          1,
                          A.data(),
                          A.leading_dimension(),
                          B.data(),
                          A.I_size());
    }

    // Must copy B to have
    auto B_cpy = similar(B);
    B_cpy      = B;
    assert(B_cpy.increment() == 1);

    return Lapack::posv(Lapack::Lapack_Order_Enum::Column_Major,
                        Lapack::To_Lapack_UpLo_v<MA_IMPL>,
                        A.I_size(),
                        1,
                        A.data(),
                        A.leading_dimension(),
                        B_cpy.data(),
                        A.I_size());
  }
}  // namespace LinearAlgebra::Lapack
