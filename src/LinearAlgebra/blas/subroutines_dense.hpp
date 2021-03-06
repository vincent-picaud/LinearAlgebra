//
// Wraps "subroutines" with dense (vector/matrix) objects
//
// This is the "abstract subroutine" one must preferably use.
//
#pragma once

// Note: this a quite "abstract" header, hence we include "blas.hpp"
// and dense vector & matrix headers
//
#include <cblas.h>
#include "LinearAlgebra/blas/blas.hpp"

#include "LinearAlgebra/blas/subroutines.hpp"
#include "LinearAlgebra/blas/to_cblas_diag.hpp"
#include "LinearAlgebra/blas/to_cblas_transpose.hpp"
#include "LinearAlgebra/blas/to_cblas_uplo.hpp"
#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/dense/matrix_view.hpp"
#include "LinearAlgebra/dense/memory_chunk_aliasing_p.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/sfinae_vmt_helpers.hpp"

namespace LinearAlgebra::Blas
{
  // [BEGIN_level_1]
  // #+begin_example
  //                            dim scalar vector   vector   scalars              5-element prefixes
  //
  // - [ ] : SUBROUTINE _ROTG (                                      A, B, C, S )          S, D
  // - [ ] : SUBROUTINE _ROTMG(                              D1, D2, A, B,        PARAM )  S, D
  // - [ ] : SUBROUTINE _ROT  ( N,         X, INCX, Y, INCY,               C, S )          S, D
  // - [ ] : SUBROUTINE _ROTM ( N,         X, INCX, Y, INCY,                      PARAM )  S, D
  // - [ ] : SUBROUTINE _SWAP ( N,         X, INCX, Y, INCY )                              S, D, C, Z
  // - [X] : SUBROUTINE _SCAL ( N,  ALPHA, X, INCX )                                       S, D, C, Z, CS, ZD
  // - [X] : SUBROUTINE _COPY ( N,         X, INCX, Y, INCY )                              S, D, C, Z
  // - [ ] : SUBROUTINE _AXPY ( N,  ALPHA, X, INCX, Y, INCY )                              S, D, C, Z
  // - [ ] : FUNCTION   _DOT  ( N,         X, INCX, Y, INCY )                              S, D, DS
  // - [ ] : FUNCTION   _DOTU ( N,         X, INCX, Y, INCY )                              C, Z
  // - [ ] : FUNCTION   _DOTC ( N,         X, INCX, Y, INCY )                              C, Z
  // - [ ] : FUNCTION   __DOT ( N,  ALPHA, X, INCX, Y, INCY )                              SDS
  // - [ ] : FUNCTION   _NRM2 ( N,         X, INCX )                                       S, D, SC, DZ
  // - [ ] : FUNCTION   _ASUM ( N,         X, INCX )                                       S, D, SC, DZ
  // - [ ] : FUNCTION   I_AMAX( N,         X, INCX )                                       S, D, C, Z
  //
  // #+end_example
  // [END_level_1]

  //==== copy ====
  //
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  copy(const Dense_Vector_Crtp<V1_IMPL>& V1, Dense_Vector_Crtp<V0_IMPL>& V0)
      -> std::enable_if_t<Always_True_v<
          decltype(Blas::copy(V0.size(), V1.data(), V1.increment(), V0.data(), V0.increment()))>>
  {
    assert(V0.size() == V1.size());

    Blas::copy(V0.size(), V1.data(), V1.increment(), V0.data(), V0.increment());
  }

  //==== scal ====
  //
  template <typename V_IMPL>
  auto
  scal(const Element_Type_t<V_IMPL>& alpha, Dense_Vector_Crtp<V_IMPL>& V) -> std::enable_if_t<
      Always_True_v<decltype(Blas::scal(V.size(), alpha, V.data(), V.increment()))>>
  {
    Blas::scal(V.size(), alpha, V.data(), V.increment());
  }

  // [BEGIN_level_2]
  // #+begin_example
  //
  //                 options            dim   b-width scalar matrix  vector   scalar vector   prefixes
  //
  // - [ ] : _GEMV (        TRANS,      M, N,         ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) S, D, C, Z
  // - [ ] : _GBMV (        TRANS,      M, N, KL, KU, ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) S, D, C, Z
  // - [ ] : _HEMV ( UPLO,                 N,         ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) C, Z
  // - [ ] : _HBMV ( UPLO,                 N, K,      ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) C, Z
  // - [ ] : _HPMV ( UPLO,                 N,         ALPHA, AP,     X, INCX, BETA,  Y, INCY ) C, Z
  // - [X] : _SYMV ( UPLO,                 N,         ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) S, D
  // - [ ] : _SBMV ( UPLO,                 N, K,      ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) S, D
  // - [ ] : _SPMV ( UPLO,                 N,         ALPHA, AP,     X, INCX, BETA,  Y, INCY ) S, D
  // - [X] : _TRMV ( UPLO, TRANS, DIAG,    N,                A, LDA, X, INCX )                 S, D, C, Z
  // - [ ] : _TBMV ( UPLO, TRANS, DIAG,    N, K,             A, LDA, X, INCX )                 S, D, C, Z
  // - [ ] : _TPMV ( UPLO, TRANS, DIAG,    N,                AP,     X, INCX )                 S, D, C, Z
  // - [X] : _TRSV ( UPLO, TRANS, DIAG,    N,                A, LDA, X, INCX )                 S, D, C, Z
  // - [ ] : _TBSV ( UPLO, TRANS, DIAG,    N, K,             A, LDA, X, INCX )                 S, D, C, Z
  // - [ ] : _TPSV ( UPLO, TRANS, DIAG,    N,                AP,     X, INCX )                 S, D, C, Z
  //
  // - [ ] :         options            dim   scalar vector   vector   matrix  prefixes
  //
  // - [ ] : _GER  (                    M, N, ALPHA, X, INCX, Y, INCY, A, LDA ) S, D
  // - [ ] : _GERU (                    M, N, ALPHA, X, INCX, Y, INCY, A, LDA ) C, Z
  // - [ ] : _GERC (                    M, N, ALPHA, X, INCX, Y, INCY, A, LDA ) C, Z
  // - [ ] : _HER  ( UPLO,                 N, ALPHA, X, INCX,          A, LDA ) C, Z
  // - [ ] : _HPR  ( UPLO,                 N, ALPHA, X, INCX,          AP )     C, Z
  // - [ ] : _HER2 ( UPLO,                 N, ALPHA, X, INCX, Y, INCY, A, LDA ) C, Z
  // - [ ] : _HPR2 ( UPLO,                 N, ALPHA, X, INCX, Y, INCY, AP )     C, Z
  // - [ ] : _SYR  ( UPLO,                 N, ALPHA, X, INCX,          A, LDA ) S, D
  // - [ ] : _SPR  ( UPLO,                 N, ALPHA, X, INCX,          AP )     S, D
  // - [ ] : _SYR2 ( UPLO,                 N, ALPHA, X, INCX, Y, INCY, A, LDA ) S, D
  // - [ ] : _SPR2 ( UPLO,                 N, ALPHA, X, INCX, Y, INCY, AP )     S, D
  // - [ ] :
  //
  // #+end_example
  // [END_level_2]

  //==== trmv ====
  //
  template <
      Matrix_Unary_Op_Enum OP,
      typename X_IMPL,
      typename M_IMPL,
      // CAVEAT: This one is REQUIRED to avoid a HARD error and make
      //         SFINAE works as expected.
      //
      // Note: If required you can use the same scheme for UpLo etc.. by adding
      //
      //       typename ENABLED_To_CBlas_UpLo = std::enable_if_t<Support_CBlas_UpLo_v<M_IMPL>>>
      //
      //
      // The key point to remember is that
      //
      //       "Substitution proceeds in LEXICAL ORDER and stops when
      //       a failure is encountered."
      //
      // Illuminating example: https://en.cppreference.com/w/cpp/language/sfinae
      // template <typename A>
      // struct B { using type = typename A::type; };
      //
      //----------------------------------------------------------------
      // template <
      //   class T,
      //   class U = typename T::type,      // SFINAE failure if T has no member type
      //   class V = typename B<T>::type    // hard error if T has no member type
      //                                    // (guaranteed to not occur as of C++14 because
      //                                    //  substitution into the default template argument
      //                                    //  of U would fail first)
      // > void foo (int);
      //----------------------------------------------------------------
      //
      //
      // See: extra information (not as illuminating as the previous example)
      //      https://stackoverflow.com/questions/44340209/special-rules-regarding-sfinae-for-incomplete-types
      //      https://stackoverflow.com/questions/15260685/what-exactly-is-the-immediate-context-mentioned-in-the-c11-standard-for-whic
      //
      typename ENABLED_To_CBlas_UpLo      = std::enable_if_t<Support_CBlas_UpLo_v<M_IMPL>>,
      typename ENABLED_To_CBlas_Transpose = std::enable_if_t<Support_CBlas_Transpose_v<OP>>,
      typename ENABLED_To_CBlas_Diag      = std::enable_if_t<Support_CBlas_Diag_v<M_IMPL>>>
  auto
  trmv(const _matrix_unary_op_t_<OP>,
       const Dense_Matrix_Crtp<M_IMPL>& M,
       Dense_Vector_Crtp<X_IMPL>& x)
      -> std::enable_if_t<
          (Is_Triangular_Matrix_v<M_IMPL> or Is_Unit_Triangular_Matrix_v<M_IMPL>)and Always_True_v<
              decltype(Blas::trmv(CblasColMajor,
                                  To_CBlas_UpLo_v<M_IMPL>,
                                  To_CBlas_Transpose_v<OP>,
                                  To_CBlas_Diag_v<M_IMPL>,
                                  M.I_size(),
                                  M.data(),
                                  M.leading_dimension(),
                                  x.data(),
                                  x.increment()))>>
  {
    Blas::trmv(CblasColMajor,
               To_CBlas_UpLo_v<M_IMPL>,
               To_CBlas_Transpose_v<OP>,
               To_CBlas_Diag_v<M_IMPL>,
               M.I_size(),
               M.data(),
               M.leading_dimension(),
               x.data(),
               x.increment());
  }

  //==== trsv ====
  //
  template <Matrix_Unary_Op_Enum OP,
            typename X_IMPL,
            typename M_IMPL,
            // CAVEAT: see trmv note
            typename ENABLED_To_CBlas_UpLo      = std::enable_if_t<Support_CBlas_UpLo_v<M_IMPL>>,
            typename ENABLED_To_CBlas_Transpose = std::enable_if_t<Support_CBlas_Transpose_v<OP>>,
            typename ENABLED_To_CBlas_Diag      = std::enable_if_t<Support_CBlas_Diag_v<M_IMPL>>>
  auto
  trsv(const _matrix_unary_op_t_<OP>,
       const Dense_Matrix_Crtp<M_IMPL>& M,
       Dense_Vector_Crtp<X_IMPL>& x)
      -> std::enable_if_t<
          (Is_Triangular_Matrix_v<M_IMPL> or Is_Unit_Triangular_Matrix_v<M_IMPL>)and Always_True_v<
              decltype(Blas::trsv(CblasColMajor,
                                  To_CBlas_UpLo_v<M_IMPL>,
                                  To_CBlas_Transpose_v<OP>,
                                  To_CBlas_Diag_v<M_IMPL>,
                                  M.I_size(),
                                  M.data(),
                                  M.leading_dimension(),
                                  x.data(),
                                  x.increment()))>>
  {
    Blas::trsv(CblasColMajor,
               To_CBlas_UpLo_v<M_IMPL>,
               To_CBlas_Transpose_v<OP>,
               To_CBlas_Diag_v<M_IMPL>,
               M.I_size(),
               M.data(),
               M.leading_dimension(),
               x.data(),
               x.increment());
  }

  //==== symv ====
  //
  // CAVEAT: blas only provides float, double
  //
  template <Matrix_Unary_Op_Enum OP,
            typename M_IMPL,
            typename X_IMPL,
            typename Y_IMPL,
            typename ENABLED_To_CBlas_UpLo = std::enable_if_t<Support_CBlas_UpLo_v<M_IMPL>>>
  auto
  symv(const Element_Type_t<Y_IMPL>& alpha,
       const _matrix_unary_op_t_<OP>,
       const Dense_Matrix_Crtp<M_IMPL>& M,
       const Dense_Vector_Crtp<X_IMPL>& X,
       const Element_Type_t<Y_IMPL>& beta,
       Dense_Vector_Crtp<Y_IMPL>& Y)
      -> std::enable_if_t<Is_Symmetric_Matrix_v<M_IMPL> and
                          ((OP == Matrix_Unary_Op_Enum::Identity) or
                           (OP == Matrix_Unary_Op_Enum::Transpose)) and
                          Always_True_v<decltype(symv(CblasColMajor,
                                                      To_CBlas_UpLo_v<M_IMPL>,
                                                      M.I_size(),
                                                      alpha,
                                                      M.data(),
                                                      M.leading_dimension(),
                                                      X.data(),
                                                      X.increment(),
                                                      beta,
                                                      Y.data(),
                                                      Y.increment()))>>
  {
    assert(are_not_aliased_p(M, Y) and are_not_aliased_p(X, Y));

    symv(CblasColMajor,
         To_CBlas_UpLo_v<M_IMPL>,
         M.I_size(),
         alpha,
         M.data(),
         M.leading_dimension(),
         X.data(),
         X.increment(),
         beta,
         Y.data(),
         Y.increment());
  }

  //==== gemv ====
  //
  template <Matrix_Unary_Op_Enum OP,
            typename M_IMPL,
            typename X_IMPL,
            typename Y_IMPL,
            typename ENABLED_To_CBlas_Transpose = std::enable_if_t<Support_CBlas_Transpose_v<OP>>>
  auto
  gemv(const Element_Type_t<Y_IMPL>& alpha,
       const _matrix_unary_op_t_<OP>,
       const Dense_Matrix_Crtp<M_IMPL>& M,
       const Dense_Vector_Crtp<X_IMPL>& X,
       const Element_Type_t<Y_IMPL>& beta,
       Dense_Vector_Crtp<Y_IMPL>& Y)
      -> std::enable_if_t<Is_Full_Matrix_v<M_IMPL> and
                          Always_True_v<decltype(gemv(CblasColMajor,
                                                      To_CBlas_Transpose_v<OP>,
                                                      M.I_size(),
                                                      M.J_size(),
                                                      alpha,
                                                      M.data(),
                                                      M.leading_dimension(),
                                                      X.data(),
                                                      X.increment(),
                                                      beta,
                                                      Y.data(),
                                                      Y.increment()))>>
  {
    gemv(CblasColMajor,
         To_CBlas_Transpose_v<OP>,
         M.I_size(),
         M.J_size(),
         alpha,
         M.data(),
         M.leading_dimension(),
         X.data(),
         X.increment(),
         beta,
         Y.data(),
         Y.increment());
  }

  // [BEGIN_level_3]
  // #+begin_example
  //
  //                 options                          dim      scalar matrix  matrix  scalar matrix  prefixes
  //
  // - [X] : _GEMM (             TRANSA, TRANSB,      M, N, K, ALPHA, A, LDA, B, LDB, BETA,  C, LDC ) S, D, C, Z
  // - [ ] : _SYMM ( SIDE, UPLO,                      M, N,    ALPHA, A, LDA, B, LDB, BETA,  C, LDC ) S, D, C, Z
  // - [ ] : _HEMM ( SIDE, UPLO,                      M, N,    ALPHA, A, LDA, B, LDB, BETA,  C, LDC ) C, Z
  // - [X] : _SYRK (       UPLO, TRANS,                  N, K, ALPHA, A, LDA,         BETA,  C, LDC ) S, D, C, Z
  // - [ ] : _HERK (       UPLO, TRANS,                  N, K, ALPHA, A, LDA,         BETA,  C, LDC ) C, Z
  // - [ ] : _SYR2K(       UPLO, TRANS,                  N, K, ALPHA, A, LDA, B, LDB, BETA,  C, LDC ) S, D, C, Z
  // - [ ] : _HER2K(       UPLO, TRANS,                  N, K, ALPHA, A, LDA, B, LDB, BETA,  C, LDC ) C, Z
  // - [ ] : _TRMM ( SIDE, UPLO, TRANSA,        DIAG, M, N,    ALPHA, A, LDA, B, LDB )                S, D, C, Z
  // - [ ] : _TRSM ( SIDE, UPLO, TRANSA,        DIAG, M, N,    ALPHA, A, LDA, B, LDB )                S, D, C, Z
  //
  // #+end_example
  // [END_level_3]

  //==== syrk ====
  //

  // AAt
  template <typename C_IMPL,
            typename A_IMPL,
            // CAVEAT: see trmv note
            typename ENABLED_To_CBlas_UpLo = std::enable_if_t<Support_CBlas_UpLo_v<C_IMPL>>>
  auto
  syrk_AAt(const Element_Type_t<A_IMPL>& alpha,
           const Dense_Matrix_Crtp<A_IMPL>& A,
           const Element_Type_t<C_IMPL>& beta,
           Dense_Matrix_Crtp<C_IMPL>& C)
      -> std::enable_if_t<Is_Full_Matrix_v<A_IMPL> and Is_Symmetric_Matrix_v<C_IMPL> and
                          Always_True_v<decltype(syrk(CblasColMajor,
                                                      To_CBlas_UpLo_v<C_IMPL>,
                                                      CblasNoTrans,  // AAt
                                                      C.I_size(),
                                                      A.J_size(),
                                                      alpha,
                                                      A.data(),
                                                      A.leading_dimension(),
                                                      beta,
                                                      C.data(),
                                                      C.leading_dimension()))>>
  {
    syrk(CblasColMajor,
         To_CBlas_UpLo_v<C_IMPL>,
         CblasNoTrans,  // AAt
         C.I_size(),
         A.J_size(),
         alpha,
         A.data(),
         A.leading_dimension(),
         beta,
         C.data(),
         C.leading_dimension());
  }

  // AtA
  template <typename C_IMPL,
            typename A_IMPL,
            // CAVEAT: see trmv note
            typename ENABLED_To_CBlas_UpLo = std::enable_if_t<Support_CBlas_UpLo_v<C_IMPL>>>
  auto
  syrk_AtA(const Element_Type_t<A_IMPL>& alpha,
           const Dense_Matrix_Crtp<A_IMPL>& A,
           const Element_Type_t<C_IMPL>& beta,
           Dense_Matrix_Crtp<C_IMPL>& C)
      -> std::enable_if_t<Is_Full_Matrix_v<A_IMPL> and Is_Symmetric_Matrix_v<C_IMPL> and
                          Always_True_v<decltype(syrk(CblasColMajor,
                                                      To_CBlas_UpLo_v<C_IMPL>,
                                                      CblasTrans,  // AtA
                                                      C.I_size(),
                                                      A.I_size(),
                                                      alpha,
                                                      A.data(),
                                                      A.leading_dimension(),
                                                      beta,
                                                      C.data(),
                                                      C.leading_dimension()))>>
  {
    syrk(CblasColMajor,
         To_CBlas_UpLo_v<C_IMPL>,
         CblasTrans,  // AtA
         C.I_size(),
         A.I_size(),
         alpha,
         A.data(),
         A.leading_dimension(),
         beta,
         C.data(),
         C.leading_dimension());
  }

  //==== gemm ====
  //
  template <
      Matrix_Unary_Op_Enum OP1,
      Matrix_Unary_Op_Enum OP2,
      typename A_IMPL,
      typename B_IMPL,
      typename C_IMPL,
      //
      typename ENABLED_1_To_CBlas_Transpose = std::enable_if_t<Support_CBlas_Transpose_v<OP1>>,
      typename ENABLED_2_To_CBlas_Transpose = std::enable_if_t<Support_CBlas_Transpose_v<OP2>>>
  auto
  gemm(const Element_Type_t<C_IMPL>& alpha,
       const _matrix_unary_op_t_<OP1> op1,
       const Dense_Matrix_Crtp<A_IMPL>& A,
       const _matrix_unary_op_t_<OP2>,
       const Dense_Matrix_Crtp<B_IMPL>& B,
       const Element_Type_t<C_IMPL>& beta,
       Dense_Matrix_Crtp<C_IMPL>& C)
      -> std::enable_if_t<Is_Full_Matrix_v<A_IMPL> and Is_Full_Matrix_v<B_IMPL> and
                          Is_Full_Matrix_v<C_IMPL> and
                          Always_True_v<decltype(gemm(
                              CblasColMajor,
                              To_CBlas_Transpose_v<OP1>,
                              To_CBlas_Transpose_v<OP2>,
                              C.I_size(),
                              C.J_size(),
                              (does_it_transpose_matrix_dimension(op1) ? A.I_size() : A.J_size()),
                              alpha,
                              A.data(),
                              A.leading_dimension(),
                              B.data(),
                              B.leading_dimension(),
                              beta,
                              C.data(),
                              C.leading_dimension()))>>
  {
    gemm(CblasColMajor,
         To_CBlas_Transpose_v<OP1>,
         To_CBlas_Transpose_v<OP2>,
         C.I_size(),
         C.J_size(),
         (does_it_transpose_matrix_dimension(op1) ? A.I_size() : A.J_size()),
         alpha,
         A.data(),
         A.leading_dimension(),
         B.data(),
         B.leading_dimension(),
         beta,
         C.data(),
         C.leading_dimension());
  }

}  // namespace LinearAlgebra::Blas
