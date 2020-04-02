#include "LinearAlgebra/matrix.hpp"

namespace LinearAlgebra
{
  template <typename M_IMPL, typename X0_IMPL>
  void
  cg(const Matrix_Crtp<M_IMPL>& M, Dense_Vector_Crtp<X0_IMPL>& X0)
  {
  }
}

using namespace LinearAlgebra;

int
main()
{
  Matrix<double> M(10, 10);
  Vector<double> X0(10);

  cg(M,X0);
	     
  std::cout << "toto";
}
