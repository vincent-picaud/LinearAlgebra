#include "LinearAlgebra/dense/memory_chunk_aliasing_p.hpp"
#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/matrix_view.hpp"
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

TEST(Memory_Chunck_Aliasing, matrix)
{
  Matrix<int> M1(10, 10);
  Tiny_Matrix<int, 4, 3> M2;

  EXPECT_FALSE(are_not_aliased_p(M1, M1));
  EXPECT_TRUE(are_not_aliased_p(M1, M2));
  EXPECT_TRUE(are_possibly_aliased_p(M1, M1));
  EXPECT_FALSE(are_possibly_aliased_p(M1, M2));

  auto M1_view_1 = create_matrix_view(M1, 2, 5, 4, 6);
  auto M1_view_2 = create_matrix_view(M1.as_const(), 6, 8, 4, 6);
  auto M1_view_3 = create_matrix_view(M1.as_const(), 2, 5, 2, 4);

  // CAVEAT: this is not a bug, they are considered aliased as the
  //          whole column is "stored" (leading dimension > I_size)
  //
  // 0               1               1               0
  // 0               1               1               0
  // 0               1               1               0
  // 0               0               0               0
  // 0               2               2               0
  // 0               2               2               0

  EXPECT_TRUE(are_possibly_aliased_p(M1_view_1, M1_view_2));

  // Ok here as columns are different
  //
  // 0               0               0               0               0
  // 3               3               1               1               0
  // 3               3               1               1               0
  // 3               3               1               1               0
  // 0               0               0               0               0
  // 0               0               0               0               0
  EXPECT_TRUE(are_not_aliased_p(M1_view_1, M1_view_3));

  EXPECT_TRUE(are_possibly_aliased_p(M1_view_2, M1));
  EXPECT_TRUE(are_possibly_aliased_p(M1, M1_view_2));

  EXPECT_FALSE(are_possibly_aliased_p(M2, M1_view_2));
}

// Mix of matrix and vector (->think to diagonal or row/col views)
//
TEST(Memory_Chunck_Aliasing, matrix_vector)
{
  Matrix<int> M1(10, 10);
  auto diagonal = create_vector_view_matrix_diagonal(M1);
  Vector<double> V1(10);

  EXPECT_TRUE(are_not_aliased_p(M1, V1));
  EXPECT_TRUE(are_possibly_aliased_p(M1, diagonal));
}
