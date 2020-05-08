#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

using namespace LinearAlgebra;

// Basic CG implementation
// https://en.wikipedia.org/wiki/Conjugate_gradient_method
//
template <typename A_IMPL, typename X0_IMPL, typename B_IMPL>
bool
cg(const Matrix_Crtp<A_IMPL>& A, Dense_Vector_Crtp<X0_IMPL>& X0, const Dense_Vector_Crtp<B_IMPL>& b)
{
  // Sanity checks
  //
  assert(all_sizes_are_equal_p(A.I_size(), A.J_size(), X0.size(), b.size()));
  static_assert(Is_Symmetric_Matrix_v<A_IMPL> or Is_Hermitian_Matrix_v<A_IMPL>);

  // Parameters
  //
  const double eps         = 1e-6;
  const double squared_eps = eps * eps;
  const size_t max_iter    = 100;

  // Working vector type
  //
  using element_type = Common_Element_Type_t<A_IMPL, X0_IMPL, B_IMPL>;

  auto r  = similar(Type_v<element_type>, X0);
  auto p  = similar(r);
  auto Ap = similar(r);

  // Initialization
  //
  r = b - A * X0;

  auto squared_norm_r_old = dot(r, r);

  if (squared_norm_r_old < squared_eps)
  {
    return true;
  }

  p = r;

  // Main loop
  //
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

int
main()
{
  Symmetric_Matrix<double> M(10, 10);
  Vector<double> X0(10);
  Vector<double> b(10);

  M       = 1;
  M(6, 5) = 5; // Note: in debug mode M(5, 6) = 2 would lead to an
	       // assert failure as by default symmetric matrices are
	       // stored into their lower part.

  create_vector_view_matrix_diagonal(M) = 10;

  b  = 1;
  X0 = 0;

  bool status = cg(M, X0, b);

  std::cout << X0 << std::endl;
  std::cout << std::boolalpha << status << std::endl;
}
