#include "LinearAlgebra/vector.hpp"

#include <array>
#include <vector>

using namespace LinearAlgebra;

int
main()
{
  // Construction of a dense vector using move(std::vector)
  //
  std::vector<int> data_1(4, 1);

  auto v_1 = create_vector(std::move(data_1));

  assert(data_1.size() == 0);
  static_assert(std::is_same_v<Vector<int>, decltype(v_1)>);

  std::cout << v_1 << std::endl;

  //================

  // Construction of a Tiny_Vector from a std::array copy
  //
  std::array<int, 4> data_2;
  for (auto& data_2_i : data_2) data_2_i = 2;

  auto v_2 = create_vector(data_2);

  static_assert(std::is_same_v<Tiny_Vector<int, 4>, decltype(v_2)>);

  std::cout << v_2 << std::endl;

  //================

  // Construction of a Tiny_Vector from a C array
  //
  auto v_3 = create_vector({3, 3, 3, 3});

  static_assert(std::is_same_v<Tiny_Vector<int, 4>, decltype(v_3)>);

  std::cout << v_3 << std::endl;
}
