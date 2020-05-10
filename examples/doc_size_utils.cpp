#include <type_traits>
#include "LinearAlgebra/dense/vector_fwd.hpp"
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include "LinearAlgebra/utils/size_utils.hpp"

using namespace LinearAlgebra;

int
main()
{
  // Has_Static_Capacity_v
  //
  static_assert(not Has_Static_Capacity_v<Vector<double>>);
  static_assert(Has_Static_Capacity_v<Tiny_Matrix<int, 3, 4>>);

  // Has_Static_Size_v
  //
  static_assert(Has_Static_Size_v<Tiny_Vector<double, 3>>);
  static_assert(not Has_Static_Size_v<Vector<double>>);

  static_assert(not Has_Static_Size_v<Matrix<double>>);  // safely
                                                         // returns
                                                         // false, even
                                                         // if not a
                                                         // vector type

  // Any_has_static_size_v
  //
  static_assert(Any_Has_Static_Size_v<Vector<double>, Tiny_Vector<double, 3>>);

  // Has_Static_I_Size_v
  //
  static_assert(Has_Static_I_Size_v<Tiny_Matrix<int, 3, 4>>);
  static_assert(not Has_Static_I_Size_v<Matrix<int>>);

  // Any_Static_I_Size_v
  //
  static_assert(Any_Has_Static_I_Size_v<Vector<int>, Tiny_Matrix<int, 3, 4>>);

  // Has_Static_J_Size_v
  //
  static_assert(Has_Static_J_Size_v<Tiny_Matrix<int, 3, 4>>);
  static_assert(not Has_Static_J_Size_v<Matrix<int>>);

  // Any_Static_J_Size_v
  //
  static_assert(Any_Has_Static_J_Size_v<Vector<int>, Tiny_Matrix<int, 3, 4>>);
}
