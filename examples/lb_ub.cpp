#include "LinearAlgebra/vector.hpp"
#include "LinearAlgebra/utils/lower_upper_bound.hpp"

using namespace LinearAlgebra;

int
main()
{
  double data[13] = {1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6};
  auto X          = create_vector_view(data, 13);

  std::cout << X << std::endl;
  
  auto X_3 = create_vector_view(X, lower_bound(X, 3), upper_bound(X, 3));

  X_3=10;

  std::cout << X << std::endl;
}
