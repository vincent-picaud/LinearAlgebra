// Define the base class of Vector, Matrix, Tensor types
//
// Role: its role is to unifies argument capture in interface functions
//
#pragma once

#include "LinearAlgebra/utils/crtp.hpp"

namespace LinearAlgebra
{
  template <typename IMPL>
  class VMT_Crtp : public Crtp_Find_Impl<VMT_Crtp, IMPL, Crtp>
  {
    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Crtp_Find_Impl<VMT_Crtp, IMPL, Crtp>;
    using base_type::impl;

    using exact_type  = typename base_type::exact_type;
    using traits_type = typename base_type::traits_type;

    using element_type = typename traits_type::element_type;

  //////////////////
    // Prevent object slicing
    //////////////////
    //
   protected:
    VMT_Crtp& operator=(const VMT_Crtp&) = default;
  };

}
