#include "LinearAlgebra/matrix.hpp"

using namespace LinearAlgebra;

template <typename T>
using Matrix_nx2 =
    Default_Matrix<T,
                   Matrix_Special_Structure_Enum::None,       // Dense matrix
                   Matrix_Storage_Mask_Enum::None,            //
                   std::size_t,                               // Dynamic number of rows
                   std::integral_constant<std::size_t, 2>,    // Static number of columns, here 2
                   std::integral_constant<std::size_t, 10>>;  // Static leading dimension, here 10

// note: having a static leading dimension=10 allows to statically
//       allocate matrix, but this also limits max row size to 10.

static_assert(not Has_Static_I_Size_v<Matrix_nx2<int>>);
static_assert(Has_Static_J_Size_v<Matrix_nx2<int>>);

static_assert(Has_Static_Capacity_v<Matrix_nx2<int>>);
static_assert(Has_Static_Capacity_v<Tiny_Matrix<int, 2, 3>>);
static_assert(Has_Static_Capacity_v<Tiny_Vector<int, 2>>);

int
main()
{
  // Note:
  //
  // 1. M(5,3) would lead to run-time error in debug mode
  //    Reason: request 3 columns, 2 expected
  //
  // 2. M(15, 2) would lead to run-time error in debug mode
  //    Reason: number of rows > statically defined leading dimension
  //
  Matrix_nx2<double> M(5, 2);
  M = 0;

  // Note: one can also write
  // "create_vector_view_matrix_row(M,2)=2;"
  auto row_2 = create_vector_view_matrix_row(M, 2);
  row_2      = 2;

  auto col_1 = create_vector_view_matrix_column(M, 1);
  col_1      = 1;

  static_assert(Has_Static_Dimension_v<decltype(row_2)>);
  static_assert(not Has_Static_Dimension_v<decltype(col_1)>);

  std::cout << M;

  return 0;
}
