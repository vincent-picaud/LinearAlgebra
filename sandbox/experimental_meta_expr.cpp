// -*- compile-command: "g++ -std=c++17  poub2.cpp && ./a.out"; -*-
#include <array>
#include <ccomplex>
#include <iostream>
#include <memory>
#include <tuple>
#include <type_traits>

#include "LinearAlgebra/metaexpr/operator_overloading.hpp"

#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/vector.hpp"

#include "LinearAlgebra/utils/crtp.hpp"

template <typename T>
void
print(const T&)
{
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
}

using namespace LinearAlgebra;

int
main()
{
  Matrix<double> M1;
  Tiny_Matrix<int, 2, 3> M2;
  static_assert(std::is_trivially_copyable_v<Tiny_Matrix<int, 2, 3>>);

  auto expression_2 = M1 + 4 * M2 * M1 * M2;
  auto expression   = 4 * M2;

  print(from_metaexpr_to_argument_tuple(expression));
  //  Detail::call_assign_from_metaexpr(M2, expression);
}
