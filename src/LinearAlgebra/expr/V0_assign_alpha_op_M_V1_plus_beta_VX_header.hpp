//
// Header to include, compute V = α op(M) V + β V
//
// As it is quite easy to miss some files we explicitly record them
// here.
//
// Design note:
//
// - functions that use _lhs_ or _lhs_1_, _lhs_2_ cannot be generated
//   by the "expression template" (sub dir metaExpr/). Thus they are
//   called directly by the user and the user must use the unique
//   canonical form, by example:
//
//   V0 = α op(M) V1 + β V0   <- here V0 == _lhs_
//
//   assign(y, 2, _identity_, M, x, _plus_, 0, _lhs_);
//
//   Thus we only need to define ONE canonical routine
//
#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_plus_beta_V0_driver.hpp"
//
// This file considers expression of the form
//
//   V0 = α op(M) V1 + β V2
//
// As this expression does not use _lhs_ or _lhs_1_, _lhs_2_ it can be
// generated from metaExpr. In this context and in order to provide
// some syntactic sugar it can be useful (but not mandatory) to
// provide some "alias" like:
//
//   V0 = M V1 + V2
//   V0 = M V1 - V2
//   V0 = V2 + α M V1
//
#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_plus_beta_V2_driver.hpp"
//
// Now we include computational routines
// CAVEAT: this routines must only use CANONICAL form, here:
//
// V0 = α op(M) V1 + β V0 or
//
// V0 = α op(M) V1 + β V2
//
#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_plus_beta_VX_blas.hpp"
#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_plus_beta_VX_generic.hpp"
