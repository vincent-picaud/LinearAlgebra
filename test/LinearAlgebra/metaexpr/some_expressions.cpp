#include "LinearAlgebra/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;
namespace LinearAlgebra
{
  namespace Detail
  {
    struct Detail_ADL
    {
    };

    template <typename IMPL_0, typename IMPL_1>
    bool
    impl_comparison(const Detail_ADL detail_ADL, const Vector_Crtp<IMPL_0>& vector_0,
                    const Vector_Crtp<IMPL_1>& vector_1)
    {
      return impl_comparison(detail_ADL, vector_0.impl(), vector_1.impl());
    }
  }

  template <typename IMPL_0, typename IMPL_1>
  bool
  operator==(const Vector_Crtp<IMPL_0>& vector_0, const Vector_Crtp<IMPL_1>& vector_1)
  {
    return impl_comparison(Detail::Detail_ADL(), vector_0, vector_1);
  }

  namespace Detail
  {
    template <typename IMPL_0, typename IMPL_1>
    bool
    impl_comparison(const Detail_ADL detail_ADL, const Dense_Vector_Crtp<IMPL_0>& vector_0,
                    const Dense_Vector_Crtp<IMPL_1>& vector_1)
    {
      return true;
    }
  }
}
TEST(MetaExpr_Crtp, basic_1)
{
  const size_t n = 4;
  int data[n]    = {1, 2, 3, 4};

  auto V1 = create_vector_view(data, n);

  Vector<double> V2(n);
  V2 = 2;

  V2 = V2 + 4 * V1;

  EXPECT_EQ(V2[0], 2 + 4 * V1[0]);
  EXPECT_EQ(V2[1], 2 + 4 * V1[1]);

  Vector<double> V3(n);
  V3 = 2;

  // V3 = 4 * V1 + V3;

  // EXPECT_EQ(V2,V3);

  EXPECT_EQ(V2, V1);
}
