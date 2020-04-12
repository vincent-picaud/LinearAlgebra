#include "LinearAlgebra/lapack/lapack.hpp"

#if !(HAS_LAPACK)
#error "must have lapack"
#endif

#include <cassert>

int
main()
{
  double A[5][3] = {{1, 2, 3}, {4, 5, 1}, {3, 5, 2}, {4, 1, 4}, {2, 5, 3}};
  double b[5][2] = {{-10, 12}, {14, 16}, {18, -3}, {14, 12}, {16, 16}};
  lapack_int info, m, n, lda, ldb, nrhs;

  /* Initialization */
  m    = 5;
  n    = 3;
  nrhs = 2;
  lda  = 5;
  ldb  = 5;

  info = LAPACKE_dgels(LAPACK_COL_MAJOR, 'N', m, n, nrhs, *A, lda, *b, ldb);

  assert(info == 0);
}
