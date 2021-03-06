#include "LinearAlgebra/dense/matrix_storage_scheme.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Default_Matrix_Storage_Scheme, Basic)
{
  Default_Matrix_Storage_Scheme<Matrix_Storage_Mask_Enum::None,
                                std::integral_constant<size_t, 3>,
                                std::integral_constant<size_t, 2>,
                                std::integral_constant<size_t, 5>>
      storage_blas;

  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 3>, decltype(storage_blas.I_size())>));
  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 2>, decltype(storage_blas.J_size())>));
  EXPECT_EQ(2 * 5, storage_blas.required_capacity());  // value
  EXPECT_TRUE((std::is_same_v<
               std::integral_constant<size_t, 2 * 5>,
               decltype(storage_blas.required_capacity())>));  // but more importantly static type
}

TEST(Default_Matrix_Storage_Scheme, constexpr_test)
{
  constexpr Default_Matrix_Storage_Scheme<Matrix_Storage_Mask_Enum::None,
                                          std::integral_constant<size_t, 3>,
                                          std::integral_constant<size_t, 2>,
                                          std::integral_constant<size_t, 5>>
      storage_blas;

  // AFAIK there is not other way to check constexpr
  constexpr auto i_size = storage_blas.I_size();
  (void)i_size;

  constexpr auto j_size = storage_blas.J_size();
  (void)j_size;

  constexpr auto rc = storage_blas.required_capacity();
  (void)rc;
}

// check zero size as soon as one of N,M=0
TEST(Default_Matrix_Storage_Scheme, Zero_Sizes_I)
{
  Default_Matrix_Storage_Scheme<Matrix_Storage_Mask_Enum::None,
                                std::integral_constant<size_t, 0>,
                                std::integral_constant<size_t, 2>,
                                std::integral_constant<size_t, 5>>
      storage_blas;

  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 0>, decltype(storage_blas.I_size())>));
  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 2>, decltype(storage_blas.J_size())>));
  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 0>,
                              decltype(storage_blas.required_capacity())>));
}

TEST(Default_Matrix_Storage_Scheme, Zero_Sizes_J)
{
  Default_Matrix_Storage_Scheme<Matrix_Storage_Mask_Enum::None,
                                std::integral_constant<size_t, 2>,
                                std::integral_constant<size_t, 0>,
                                std::integral_constant<size_t, 5>>
      storage_blas;

  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 2>, decltype(storage_blas.I_size())>));
  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 0>, decltype(storage_blas.J_size())>));
  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 0>,
                              decltype(storage_blas.required_capacity())>));
}
