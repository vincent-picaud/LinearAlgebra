#pragma once

#include <array>
#include <vector>
#include "LinearAlgebra/dense/vector_fwd.hpp"

namespace LinearAlgebra
{
  template <typename T, std::size_t N>
  Tiny_Vector<T, N>
  create_vector(const std::array<T, N>& v) noexcept
  {
    using storage_scheme_type = typename Tiny_Vector<T, N>::storage_scheme_type;

    return {storage_scheme_type{}, v};
  }

  template <typename T>
  Vector<T>
  create_vector(std::vector<T>&& v) noexcept
  {
    using storage_scheme_type = typename Vector<T>::storage_scheme_type;

    return {storage_scheme_type{v.size()}, std::move(v)};
  }

  //================

  // See: https://stackoverflow.com/a/40241592/2001017
  //
  //      -> using std::initializer_list<T> is a bad idea as it is not
  //         easy to get size at compile time

  template <typename T, std::size_t N>
  Tiny_Vector<T, N>
  create_vector(T const (&data)[N])
  {
    using storage_scheme_type = typename Tiny_Vector<T, N>::storage_scheme_type;

    std::array<T, N> array;
    for (std::size_t i = 0; i < N; i++)
    {
      array[i] = data[i];
    }

    return {storage_scheme_type{}, array};
  }

}  // namespace LinearAlgebra
