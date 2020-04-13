#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_special_structure_enum.hpp"
#include "LinearAlgebra/dense/matrix_view.hpp"
#include "LinearAlgebra/dense/vector_view.hpp"
#include "LinearAlgebra/lapack/lapack.hpp"
#include "LinearAlgebra/lapack/subroutines.hpp"
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/utils/crtp.hpp"

namespace LinearAlgebra
{
  template <typename IMPL, typename ENABLE = void>
  class Factorization_LLt;

  template <typename IMPL>
  class Factorization_LLt<IMPL, std::enable_if_t<Is_Crtp_Interface_Of_v<Dense_Matrix_Crtp, IMPL> and
                                                 ((IMPL::matrix_special_structure_type::value ==
                                                   Matrix_Special_Structure_Enum::Symmetric) or
                                                  (IMPL::matrix_special_structure_type::value ==
                                                   Matrix_Special_Structure_Enum::Hermitian))>>
  {
    // static_assert(
    //     (IMPL::matrix_special_structure_type::value == Matrix_Special_Structure_Enum::Symmetric) or
    //     (IMPL::matrix_special_structure_type::value == Matrix_Special_Structure_Enum::Hermitian));

   protected:
    IMPL _matrix;

   public:
    Factorization_LLt(Crtp<IMPL>&& matrix) : _matrix(std::move(matrix.impl()))
    {
      std::cout << "MATRIX:" << std::endl << _matrix << std::endl;
      _matrix=0;
    }
    Factorization_LLt(const Crtp<IMPL>& matrix) : _matrix(matrix.impl())
    {
      std::cout << "MATRIX:" << std::endl << _matrix << std::endl;
      _matrix=0;
    }
  };

  template <typename IMPL>
  Factorization_LLt<IMPL>
  create_LLt(Dense_Matrix_Crtp<IMPL>&& M)
  {
    return std::move(M);
  }
}

using namespace LinearAlgebra;

int
test()
{
  const size_t n = 5;

  Symmetric_Matrix<double> M(n, n);

  M                                     = 0;
  create_vector_view_matrix_diagonal(M) = 10;
  M(4, 0)                               = 5;
  // auto LLt                              = create_LLt(std::move(M));

  Factorization_LLt<Symmetric_Matrix<double>> LLt(std::move(M));

  std::cout << "MATRIX:" << std::endl << M << std::endl;

  return 0;
}

int
test_view()
{
  const size_t n = 5;

  Symmetric_Matrix<double> M(n, n);

  M                                     = 0;
  create_vector_view_matrix_diagonal(M) = 10;
  M(4, 0)                               = 5;

  auto M_view = create_matrix_view(M, 0, n, 0, n);

  std::cout << "MATRIX:" << std::endl << M << std::endl;

  Factorization_LLt<decltype(M_view)> LLt(M_view);

  std::cout << "MATRIX:" << std::endl << M << std::endl;

  return 0;
}

int
main()
{
  return test();

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

  auto L = create_matrix_view_lower_triangular(M.as_const());

  w = inverse(L) * w;
  w = inverse(transpose(L)) * w;

  std::cout << "w:" << std::endl << w << std::endl;
}
