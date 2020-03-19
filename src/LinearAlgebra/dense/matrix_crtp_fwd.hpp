#pragma once

#include "LinearAlgebra/meta/crtp.hpp"

namespace LinearAlgebra
{
  template <typename IMPL = Crtp_Final_Impl>
  class Matrix_Crtp;

  template <typename IMPL = Crtp_Final_Impl>
  class Dense_Matrix_Crtp;
}
