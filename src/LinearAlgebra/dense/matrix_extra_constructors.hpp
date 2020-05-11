#pragma once

#include "LinearAlgebra/dense/matrix_fwd.hpp"

namespace LinearAlgebra
{
  // See: https://stackoverflow.com/a/40241592/2001017
  //
  //      -> using std::initializer_list<T> is a bad idea as it is not
  //         easy to get size at compile time
  //
  template <typename T, std::size_t I_SIZE, std::size_t J_SIZE>
  Tiny_Matrix<T, I_SIZE, J_SIZE>
  create_matrix(T const (&data)[I_SIZE][J_SIZE])
  {
    Tiny_Matrix<T, I_SIZE, J_SIZE> to_return;
    fill_indexed([&data](const auto i, const auto j) { return data[i][j]; }, to_return);

    return to_return;
  }
}  // namespace LinearAlgebra
