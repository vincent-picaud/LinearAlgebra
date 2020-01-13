#include "LinearAlgebra/dense/matrix_storage_scheme.hpp"

#include <gtest/gtest.h>

using namespace KissDStream;

TEST(Default_Matrix_Storage_Scheme, Basic)
{
  Default_Matrix_Storage_Scheme<Matrix_Storage_Mask_Enum::None, std::integral_constant<size_t, 3>,
                                std::integral_constant<size_t, 2>,
                                std::integral_constant<size_t, 5>>
      storage_blas;

  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 3>, decltype(storage_blas.I_size())>));
  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 2>, decltype(storage_blas.J_size())>));
  EXPECT_EQ((3 - 1) + (2 - 1) * 5 + 1, storage_blas.required_capacity());  // value
  EXPECT_TRUE((std::is_same_v<
               std::integral_constant<size_t, (3 - 1) + (2 - 1) * 5 + 1>,
               decltype(storage_blas.required_capacity())>));  // but more importantly static type
}

TEST(Default_Matrix_Storage_Scheme, constexpr_test)
{
  constexpr Default_Matrix_Storage_Scheme<
      Matrix_Storage_Mask_Enum::None, std::integral_constant<size_t, 3>,
      std::integral_constant<size_t, 2>, std::integral_constant<size_t, 5>>
      storage_blas;

  // AFAIK there is not other way to check constexpr
  constexpr auto i_size = storage_blas.I_size();
  (void)i_size;

  constexpr auto j_size = storage_blas.J_size();
  (void)j_size;

  constexpr auto rc = storage_blas.required_capacity();
  (void)rc;
}

// Zero size peculiar case, can be problematic due, to use of N-1, M-1
TEST(Default_Matrix_Storage_Scheme, Zero_Sizes)
{
  Default_Matrix_Storage_Scheme<Matrix_Storage_Mask_Enum::None, std::integral_constant<size_t, 0>,
                                std::integral_constant<size_t, 2>,
                                std::integral_constant<size_t, 5>>
      storage_blas;

  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 0>, decltype(storage_blas.I_size())>));
  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 2>, decltype(storage_blas.J_size())>));
  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 0>,
                              decltype(storage_blas.required_capacity())>));
}
