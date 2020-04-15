#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

namespace LinearAlgebra
{
  // Basic cg implementation
  // https://en.wikipedia.org/wiki/Conjugate_gradient_method
  //
  template <typename A_IMPL, typename X0_IMPL, typename B_IMPL>
  bool
  cg(const Matrix_Crtp<A_IMPL>& A, Dense_Vector_Crtp<X0_IMPL>& X0,
     const Dense_Vector_Crtp<B_IMPL>& b)
  {
    assert(A.I_size() == A.J_size());  
    assert(A.J_size() == X0.size());
    assert(A.J_size() == b.size());

    const double eps         = 1e-6;
    const double squared_eps = eps * eps;
    const size_t max_iter    = 100;

    auto r  = create_default_storable(X0);
    auto p  = create_default_storable(X0);
    auto Ap = create_default_storable(X0);

    r = b - A * X0;

    auto squared_norm_r_old = dot(r, r);

    if (squared_norm_r_old < squared_eps)
    {
      return true;
    }

    p = r;

    for (size_t i = 0; i < max_iter; i++)
    {
      Ap = A * p;

      auto alpha = squared_norm_r_old / dot(p, Ap);

      X0 = X0 + alpha * p;

      r = r - alpha * Ap;

      auto squared_norm_r_new = dot(r, r);

      std::cout << "iter " << i << " residue " << squared_norm_r_new << std::endl;

      if (squared_norm_r_new < squared_eps)
      {
        return true;
      }

      p = r + squared_norm_r_new / squared_norm_r_old * p;

      squared_norm_r_old = squared_norm_r_new;
    }
    return false;
  }
}

using namespace LinearAlgebra;

int
main()
{
  Matrix<double> M(10, 10);
  Vector<double> X0(10);
  Vector<double> b(10), r(10);

  M = 1;

  create_vector_view_matrix_diagonal(M) = 20;
  M(5, 6)                               = 2;
  M(6, 5)                               = 2;

  b  = 1;
  X0 = 0;

  bool status = cg(M, X0, b);

  std::cout << X0 << std::endl;
  std::cout << std::boolalpha << status << std::endl;
}
