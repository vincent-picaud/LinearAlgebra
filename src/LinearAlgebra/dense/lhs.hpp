#pragma once

#include "LinearAlgebra/dense/vmt_crtp.hpp"

namespace LinearAlgebra
{
  struct LHS_Element_Type
  {
  };
}  // namespace LinearAlgebra

namespace std
{
  template <typename T>
  struct common_type<T, LinearAlgebra::LHS_Element_Type>
  {
    using type = T;
  };

  // template <typename T>
  // struct common_type<LinearAlgebra::LHS_Element_Type, T>
  // {
  //   using type = T;
  // };

  template <>
  struct common_type<LinearAlgebra::LHS_Element_Type, LinearAlgebra::LHS_Element_Type>
  {
    using type = LinearAlgebra::LHS_Element_Type;
  };

}  // namespace std

namespace LinearAlgebra
{
  class LHS;

  template <>
  struct Crtp_Type_Traits<LHS>
  {
    using element_type = LHS_Element_Type;
  };

  class LHS : public VMT_Crtp<LHS>
  {
   public:
    using base_type    = VMT_Crtp<LHS>;
    using element_type = typename base_type::element_type;

   public:
  };

}  // namespace LinearAlgebra
