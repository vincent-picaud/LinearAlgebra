// #pragma once

// #include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
// #include "LinearAlgebra/utils/size_utils.hpp"

// namespace LinearAlgebra
// {
//   //////////////
//   // get_size //
//   //////////////
//   //
//   namespace Detail
//   {
//     template <typename IMPL, typename... IMPLs>
//     inline constexpr auto
//     get_static_size(const Vector_Crtp<IMPL>& V, const Vector_Crtp<IMPLs>&... Vs) noexcept
//     {
//       static_assert(Any_Has_Static_Size_v<IMPL, IMPLs...>);

//       if constexpr (Has_Static_Size_v<IMPL>)
//       {
//         return V.size();
//       }
//       else
//       {
//         return get_static_size(Vs...);
//       }
//     }
//   }

//   // Returns vector size, a static one if any
//   //
//   // CAVEAT: we do *not* check that these sizes are identical
//   //
//   //
//   template <typename IMPL, typename... IMPLs>
//   inline constexpr auto
//   get_size(const Vector_Crtp<IMPL>& V, const Vector_Crtp<IMPLs>&... Vs) noexcept
//   {
//     if constexpr (Any_Has_Static_Size_v<IMPL, IMPLs...>)
//     {
//       return Detail::get_static_size(V, Vs...);
//     }
//     else
//     {
//       return V.size();
//     }
//   }
// }
