#pragma once

#include "LinearAlgebra/meta/crtp.hpp"

namespace LinearAlgebra
{
  template <typename IMPL = Crtp_Final_Impl>
  class Matrix_Crtp;

  template <typename IMPL = Crtp_Final_Impl>
  class Default_Matrix_Crtp;
}
