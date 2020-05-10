#include "LinearAlgebra/matrix.hpp"

using namespace LinearAlgebra;

template <typename T>
using Matrix_nx2 = Default_Matrix<T,
                                  Matrix_Special_Structure_Enum::None,
                                  Matrix_Storage_Mask_Enum::None,
                                  std::size_t,
                                  std::integral_constant<std::size_t, 2>,
                                  std::integral_constant<std::size_t, 10>>;
//std::size_t>;

static_assert(not Has_Static_I_Size_v<Matrix_nx2<int>>);
static_assert(Has_Static_J_Size_v<Matrix_nx2<int>>);

// template <typename IMPL, typename ENABLE = void>
// struct Has_Static_Capacity : std::false_type
// {
// };

// template <typename IMPL>
// struct Has_Static_Capacity<IMPL,
//                            std::enable_if_t<Is_Std_Integral_Constant_Of_Type_v<
//                                std::size_t,
//                                typename IMPL::storage_scheme_type::required_capacity_type>>>
//     : std::true_type
// {
// };

// template <typename IMPL>
// inline constexpr bool Has_Static_Capacity_v = Has_Static_Capacity<IMPL>::value;

static_assert(not Has_Static_Capacity_v<Matrix_nx2<int>>);
static_assert(Has_Static_Capacity_v<Tiny_Matrix<int,2,3>>);
static_assert(Has_Static_Capacity_v<Tiny_Vector<int,2>>);

int
main()
{
  Matrix_nx2<double> M(15, 2);  // M(5,3) would lead to run-time error in debug mode
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
