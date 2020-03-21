#include "LinearAlgebra/dense/vector_view.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Tiny_Vector_View, Constructor)
{
  Tiny_Vector<int, 10> v;

  auto view_v = view(v, 1, 3);
}
