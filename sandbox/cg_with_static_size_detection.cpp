//
// Compared to the basic implementation in cg.cpp this version is better at detecting static size
//
// The important part to keep in mind is:
//
// template <typename T>
// auto
// create_vector(const std::size_t n)
// {
//   return Vector<T>{n};
// }
// template <typename T, std::size_t N>
// auto
// create_vector(const std::integral_constant<std::size_t, N>)
// {
//   return Tiny_Vector<T, N>{};
// }
//
// template <typename A_IMPL, typename X0_IMPL, typename B_IMPL>
// bool
// cg(const Matrix_Crtp<A_IMPL>& A, Dense_Vector_Crtp<X0_IMPL>& X0, const Dense_Vector_Crtp<B_IMPL>& b)
// {
//
//   assert(all_sizes_are_equal_p(A.I_size(), A.J_size(), X0.size(), b.size()));
//
//   // Working vector type, use a static size one if possible
//   //
//   using element_type = Common_Element_Type_t<A_IMPL, X0_IMPL, B_IMPL>;                         // <-- here
//   const auto n       = get_static_size_if_any(A.I_size(), A.J_size(), X0.size(), b.size());    // <-- here
//
//   auto r  = create_vector<element_type>(n);   // <-- here
//   auto p  = create_vector<element_type>(n);   // <-- here
//   auto Ap = create_vector<element_type>(n);   // <-- here
//  
// }
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

using namespace LinearAlgebra;

// Illustrates dynamic vs static size vectors
//
template <typename T>
auto
create_vector(const std::size_t n)
{
  return Vector<T>{n};
}
template <typename T, std::size_t N>
auto
create_vector(const std::integral_constant<std::size_t, N>)
{
  return Tiny_Vector<T, N>{};
}

// Basic CG implementation
// https://en.wikipedia.org/wiki/Conjugate_gradient_method
//
template <typename A_IMPL, typename X0_IMPL, typename B_IMPL>
bool
cg(const Matrix_Crtp<A_IMPL>& A, Dense_Vector_Crtp<X0_IMPL>& X0, const Dense_Vector_Crtp<B_IMPL>& b)
{
  // Parameters
  //
  const double eps         = 1e-6;
  const double squared_eps = eps * eps;
  const size_t max_iter    = 100;

  // Sanity check
  //
  static_assert(A_IMPL::matrix_special_structure_type::value ==  // For demo...
                Matrix_Special_Structure_Enum::Symmetric);       // could be: SFINAE,
                                                                 // hermitian, etc...

  assert(all_sizes_are_equal_p(A.I_size(), A.J_size(), X0.size(), b.size()));

  // Working vector type, use a static size one if possible
  //
  using element_type = Common_Element_Type_t<A_IMPL, X0_IMPL, B_IMPL>;
  const auto n       = get_static_size_if_any(A.I_size(), A.J_size(), X0.size(), b.size());

  auto r  = create_vector<element_type>(n);
  auto p  = create_vector<element_type>(n);
  auto Ap = create_vector<element_type>(n);

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
  // Dynamic vectors/matrices

  Symmetric_Matrix<double> M(10, 10);
  Vector<double> X0(10);
  Vector<double> b(10);

  // Here static one, no more dynamic memory allocations.

  // Tiny_Symmetric_Matrix<double, 10, 10> M;
  // Tiny_Vector<double, 10> X0;
  // Tiny_Vector<double, 10> b;

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
