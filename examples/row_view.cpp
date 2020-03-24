#include "LinearAlgebra/matrix.hpp"

#include <sstream>
#include <string>

using namespace LinearAlgebra;

enum class Row_Colum_Enum
{
  Row,
  Column
};

template <Row_Colum_Enum RC, typename IMPL>
void
test_all_row_view(Dense_Matrix_Crtp<IMPL>& M)
{
  std::size_t count = 0;
  if constexpr (RC == Row_Colum_Enum::Row)
  {
    for (size_t i = 0; i < M.I_size(); ++i)
    {
      auto row_view = create_view_matrix_row(M, i);
      fill([&count]() { return ++count; }, row_view);
    }
  }
  else
  {
    static_assert(RC == Row_Colum_Enum::Column);

    for (size_t j = 0; j < M.J_size(); ++j)
    {
      auto column_view = create_view_matrix_column(M, j);
      fill([&count]() { return ++count; }, column_view);
    }
  }
}

template <Row_Colum_Enum RC, typename IMPL>
std::string
test_all_row_view_type(Dense_Matrix_Crtp<IMPL>& M, const std::size_t I_size,
                       const std::size_t J_size)
{
  std::stringstream out;

  const auto lambda = [&](const auto& special_structure, const auto& mask) {
    auto M_submatrix             = create_view_submatrix(M, 0, I_size, 0, J_size);
    auto M_submatrix_with_struct = create_view_matrix_type(M_submatrix, special_structure, mask);
    expr(M, _assign_, 0);
    test_all_row_view<RC>(M_submatrix_with_struct);
    out << M << std::endl;
  };

  lambda(
      std::integral_constant<Matrix_Special_Structure_Enum, Matrix_Special_Structure_Enum::None>(),
      std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::None>());

  lambda(std::integral_constant<Matrix_Special_Structure_Enum,
                                Matrix_Special_Structure_Enum::Triangular>(),
         std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower>());

  lambda(std::integral_constant<Matrix_Special_Structure_Enum,
                                Matrix_Special_Structure_Enum::Triangular>(),
         std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper>());

  lambda(
      std::integral_constant<Matrix_Special_Structure_Enum,
                             Matrix_Special_Structure_Enum::Triangular_Strict>(),
      std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower_Strict>());

  lambda(
      std::integral_constant<Matrix_Special_Structure_Enum,
                             Matrix_Special_Structure_Enum::Triangular_Strict>(),
      std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper_Strict>());

  return out.str();
}

const std::string row_tall =
    "\n"
    "               1               2               3               0               0\n"
    "               4               5               6               0               0\n"
    "               7               8               9               0               0\n"
    "              10              11              12               0               0\n"
    "              13              14              15               0               0\n"
    "\n"
    "               1               0               0               0               0\n"
    "               2               3               0               0               0\n"
    "               4               5               6               0               0\n"
    "               7               8               9               0               0\n"
    "              10              11              12               0               0\n"
    "\n"
    "               1               2               3               0               0\n"
    "               0               4               5               0               0\n"
    "               0               0               6               0               0\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n"
    "\n"
    "               0               0               0               0               0\n"
    "               1               0               0               0               0\n"
    "               2               3               0               0               0\n"
    "               4               5               6               0               0\n"
    "               7               8               9               0               0\n"
    "\n"
    "               0               1               2               0               0\n"
    "               0               0               3               0               0\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n";

const std::string row_wide =
    "\n"
    "               1               2               3               4               5\n"
    "               6               7               8               9              10\n"
    "              11              12              13              14              15\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n"
    "\n"
    "               1               0               0               0               0\n"
    "               2               3               0               0               0\n"
    "               4               5               6               0               0\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n"
    "\n"
    "               1               2               3               4               5\n"
    "               0               6               7               8               9\n"
    "               0               0              10              11              12\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n"
    "\n"
    "               0               0               0               0               0\n"
    "               1               0               0               0               0\n"
    "               2               3               0               0               0\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n"
    "\n"
    "               0               1               2               3               4\n"
    "               0               0               5               6               7\n"
    "               0               0               0               8               9\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n";

const std::string column_tall =
    "\n"
    "               1               6              11               0               0\n"
    "               2               7              12               0               0\n"
    "               3               8              13               0               0\n"
    "               4               9              14               0               0\n"
    "               5              10              15               0               0\n"
    "\n"
    "               1               0               0               0               0\n"
    "               2               6               0               0               0\n"
    "               3               7              10               0               0\n"
    "               4               8              11               0               0\n"
    "               5               9              12               0               0\n"
    "\n"
    "               1               2               4               0               0\n"
    "               0               3               5               0               0\n"
    "               0               0               6               0               0\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n"
    "\n"
    "               0               0               0               0               0\n"
    "               1               0               0               0               0\n"
    "               2               5               0               0               0\n"
    "               3               6               8               0               0\n"
    "               4               7               9               0               0\n"
    "\n"
    "               0               1               2               0               0\n"
    "               0               0               3               0               0\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n";

const std::string column_wide =
    "\n"
    "               1               4               7              10              13\n"
    "               2               5               8              11              14\n"
    "               3               6               9              12              15\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n"
    "\n"
    "               1               0               0               0               0\n"
    "               2               4               0               0               0\n"
    "               3               5               6               0               0\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n"
    "\n"
    "               1               2               4               7              10\n"
    "               0               3               5               8              11\n"
    "               0               0               6               9              12\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n"
    "\n"
    "               0               0               0               0               0\n"
    "               1               0               0               0               0\n"
    "               2               3               0               0               0\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n"
    "\n"
    "               0               1               2               4               7\n"
    "               0               0               3               5               8\n"
    "               0               0               0               6               9\n"
    "               0               0               0               0               0\n"
    "               0               0               0               0               0\n";

int
main()
{
  Matrix<int> M(5, 5);

  expr(M, _assign_, 0);

  std::cout << std::boolalpha << (row_tall == test_all_row_view_type<Row_Colum_Enum::Row>(M, 5, 3));
  std::cout << std::boolalpha << (row_wide == test_all_row_view_type<Row_Colum_Enum::Row>(M, 3, 5));

  std::cout << std::boolalpha
            << (column_tall == test_all_row_view_type<Row_Colum_Enum::Column>(M, 5, 3));
  std::cout << std::boolalpha
            << (column_wide == test_all_row_view_type<Row_Colum_Enum::Column>(M, 3, 5));
}
