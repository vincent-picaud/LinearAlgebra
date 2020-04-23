#include "LinearAlgebra/lapack/lapack.hpp"
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

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

  std::cout << "symmetric M :" << M << std::endl;
  std::cout << "v       :" << v << std::endl;
  std::cout << "w = M.v :" << w << std::endl;

  // Low level call of lapack: L*L^t decomposition
  //
  int info = Lapack::potrf(Lapack::Lapack_Order_Enum::Column_Major,
                           Lapack::Lapack_UpLo_Enum::Low,
                           M.I_size(),
                           M.data(),
                           M.leading_dimension());
  assert(info == 0);

  auto L = create_matrix_view_lower_triangular(M.as_const());
  std::cout << "L:" << L << std::endl;

  // inplace solve of w = M.v = L.L^t.v
  // caveat: at the end w "contains" v
  w = inverse(L) * w;             // L^(-1).w = L^t.v
  w = inverse(transpose(L)) * w;  // L^(-t).L^(-1).w = v

  std::cout << "v such that w=M.v :" << std::endl << w << std::endl;
}
