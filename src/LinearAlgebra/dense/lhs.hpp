#pragma once

#include "LinearAlgebra/dense/vmt_crtp.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

// namespace LinearAlgebra
// {
//   struct LHS_Element_Type
//   {
//   };
// }  // namespace LinearAlgebra

// namespace std
// {
//   template <typename T>
//   struct common_type<T, LinearAlgebra::LHS_Element_Type>
//   {
//     using type = T;
//   };

//   // template <typename T>
//   // struct common_type<LinearAlgebra::LHS_Element_Type, T>
//   // {
//   //   using type = T;
//   // };

//   template <>
//   struct common_type<LinearAlgebra::LHS_Element_Type, LinearAlgebra::LHS_Element_Type>
//   {
//     using type = LinearAlgebra::LHS_Element_Type;
//   };

// }  // namespace std

namespace LinearAlgebra
{
  template <typename ELEMENT_TYPE>
  class LHS;

  template <typename ELEMENT_TYPE>
  struct Crtp_Type_Traits<LHS<ELEMENT_TYPE>>
  {
    using element_type = ELEMENT_TYPE;
  };

  template <typename ELEMENT_TYPE>
  class LHS : public VMT_Crtp<LHS<ELEMENT_TYPE>>
  {
   public:
    using base_type    = VMT_Crtp<LHS<ELEMENT_TYPE>>;
    using element_type = typename base_type::element_type;
  };

  template <typename IMPL>
  LHS<Element_Type_t<IMPL>>
  f_LHS(const VMT_Crtp<IMPL>&)
  {
    return {};
  }
}  // namespace LinearAlgebra
