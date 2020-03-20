#pragma once

#include "LinearAlgebra/utils/crtp.hpp"

namespace LinearAlgebra
{
  template <typename IMPL = Crtp_Final_Impl>
  class Vector_Crtp;

  template <typename IMPL = Crtp_Final_Impl>
  class Dense_Vector_Crtp;
}
