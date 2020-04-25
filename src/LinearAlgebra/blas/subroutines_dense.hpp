//
// Wraps "subroutines" with dense (vector/matrix) objects
//
// This is the "abstract subroutine" one must preferably use.
//
#pragma once

// Note: this a quite "abstract" header, hence we include "blas.hpp"
// and dense vector & matrix headers
//
#include "LinearAlgebra/blas/blas.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/sfinae_vmt_helpers.hpp"

namespace LinearAlgebra::Blas
{
  /////////////
  // Level 1 //
  /////////////
  //
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

}  // namespace LinearAlgebra::Blas
