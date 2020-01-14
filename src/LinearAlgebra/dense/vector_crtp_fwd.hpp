#pragma once

#include "LinearAlgebra/meta/crtp.hpp"

namespace LinearAlgebra
{
  template <typename IMPL = Crtp_Final_Impl>
  class Vector_Crtp;

  template <typename IMPL = Crtp_Final_Impl>
  class Default_Vector_Crtp;
}
