// file:vmt_crtp.org
#pragma once

#include "LinearAlgebra/utils/crtp.hpp"

namespace LinearAlgebra
{
  // [BEGIN_VMT]
  //
  // Defines the Vector, Matrix, Tensor... base class
  //
  // Its role is to unifies argument capture in interface functions
  //
  template <typename IMPL>
  class VMT_Crtp : public Crtp_Find_Impl<VMT_Crtp, IMPL, Crtp>
  {
    //////////////////
    // Public Types
    //////////////////
    //
   public:
    using base_type = Crtp_Find_Impl<VMT_Crtp, IMPL, Crtp>;
    using base_type::impl;

    using exact_type  = typename base_type::exact_type;
    using traits_type = typename base_type::traits_type;

    using element_type = typename traits_type::element_type;

    // Prevent object slicing
   protected:
    VMT_Crtp& operator=(const VMT_Crtp&) = default;
  };
  // [END_VMT]

}  // namespace LinearAlgebra
