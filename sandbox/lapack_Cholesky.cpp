#include "LinearAlgebra/dense/matrix_view.hpp"
#include "LinearAlgebra/lapack/lapack.hpp"
#include "LinearAlgebra/lapack/subroutines.hpp"
#include "LinearAlgebra/matrix.hpp"

using namespace LinearAlgebra;

int
main()
{
  const size_t n = 5;

  Vector<double> v(n), w(n);
  v = 1;
  Symmetric_Matrix<double> M(n, n);

  M                                     = 0;
  create_vector_view_matrix_diagonal(M) = 10;
  M(4, 0)                               = 5;

  w = M * v;

  std::cout << "M:" << std::endl << M << std::endl;
  std::cout << "w:" << std::endl << w << std::endl;

  // L*LT
  int info = Lapack::potrf(Lapack::Lapack_Order_Enum::Column_Major, Lapack::Lapack_UpLo_Enum::Low,
                           M.I_size(), M.data(), M.leading_dimension());

  std::cout << "L:" << std::endl << M << std::endl;

  auto L = create_matrix_view_lower_triangular(M);

  w = inverse(L) * w;
  w = inverse(transpose(L)) * w;

  std::cout << "w:" << std::endl << w << std::endl;
}
