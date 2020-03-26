#include "LinearAlgebra/dense/memory_chunk_aliasing_p.hpp"
#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_view.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Memory_Chunck_Aliasing, vector)
{
  Vector<int> V1(10);
  Tiny_Vector<int, 4> V2;

  EXPECT_FALSE(are_not_aliased_p(V1, V1));
  EXPECT_TRUE(are_not_aliased_p(V1, V2));
  EXPECT_TRUE(are_possibly_aliased_p(V1, V1));
  EXPECT_FALSE(are_possibly_aliased_p(V1, V2));

  auto V1_view_1 = create_vector_view(V1, 2, 5);
  auto V1_view_2 = create_vector_view(V1.as_const(), 6, 8);

  EXPECT_TRUE(are_not_aliased_p(V1_view_1, V1_view_2));

  EXPECT_TRUE(are_possibly_aliased_p(V1_view_2, V1));
  EXPECT_TRUE(are_possibly_aliased_p(V1, V1_view_2));

  EXPECT_FALSE(are_possibly_aliased_p(V2, V1_view_2));
}
