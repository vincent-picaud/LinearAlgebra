#pragma once

#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  // #+begin_example
  //      value  lower bound       value  upper bound
  //        |      x_i >= value      |     x_i > value
  // -------========>            ----O=====>
  //    x_i domain               x_i domain
  //
  // - and O rejected region, = accepted region, contains x_i
  // #+end_example
  //
  // see PVBibliography/Cpp/lower_upper_bounds.org for futher details
  //

  // Returns the first index *idx* such "value <= x[idx]"
  //         or X.size() if such element index does not exist
  //
  template <typename IMPL>
  std::size_t
  lower_bound(const Dense_Vector_Crtp<IMPL>& X, const Element_Type_t<IMPL>& value)
  {
    std::size_t begin = 0, end = X.size();
    std::size_t candidate = end;

    while (end - begin > 0)
    {
      auto mid = (begin + end) / 2;

      if (X[mid] < value)
      {
        begin = mid + 1;
      }
      else
      {
        candidate = mid;
        end       = mid;
      }
    }

    return candidate;
  }

  // Returns the first index *idx* such "value < x[idx]"
  //         or X.size() if such element index does not exist
  //
  template <typename IMPL>
  std::size_t
  upper_bound(const Dense_Vector_Crtp<IMPL>& X, const Element_Type_t<IMPL>& value)
  {
    std::size_t begin = 0, end = X.size();
    std::size_t candidate = end;

    while (end - begin > 0)
    {
      auto mid = (begin + end) / 2;

      if (X[mid] <= value)
      {
        begin = mid + 1;
      }
      else
      {
        candidate = mid;
        end       = mid;
      }
    }

    return candidate;
  }
}  // namespace LinearAlgebra
