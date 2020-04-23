#pragma once

#include "LinearAlgebra/lapack/lapack_config.hpp"

#if !(HAS_LAPACK)
#error
#endif

// Defines our proper enums to be independent of the actual lapack
// library... A better place is maybe "lapack_config.hpp"
namespace LinearAlgebra::Lapack
{
  // Note: we generally use enum CLASS, however here we already are
  // into 2 nested namespaces (LinearAlgebra & Lapack)... this is
  // certainly sufficient to avoid name collision.
  //
  enum Lapack_Order_Enum : int
  {
    Row_Major    = LAPACK_ROW_MAJOR,
    Column_Major = LAPACK_COL_MAJOR
  };

  //
  enum Lapack_UpLo_Enum : char
  {
    Up  = 'U',
    Low = 'L'
  };
}
