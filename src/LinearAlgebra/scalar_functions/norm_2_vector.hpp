#pragma once

#include "LinearAlgebra/scalar_functions/norm_2.hpp"

#include "LinearAlgebra/blas/blas.hpp"
#include "LinearAlgebra/dense/vector_scan.hpp"
#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr_debug.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  template <typename IMPL>
  auto
  squared_norm_2(const Expr_Selector<Expr_Selector_Enum::Generic>,  //
                 const Dense_Vector_Crtp<IMPL>& VMT                 //
  )
  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Generic);

    decltype(squared_norm_2(VMT[0])) sum;
    sum = 0;

    scan([&sum](const auto& v0_component) { sum += squared_norm_2(v0_component); }, VMT);

    return sum;
  }

  template <typename IMPL>
  auto
  norm_2(const Expr_Selector<Expr_Selector_Enum::Generic>,  //
         const Dense_Vector_Crtp<IMPL>& VMT                 //
  )
  {
    using std::sqrt;
    return sqrt(squared_norm_2(VMT));
  }

//================================================================
//  Implementation: Blas
//================================================================
//
#if (HAS_BLAS)
  template <typename IMPL>
  auto
  norm_2(const Expr_Selector<Expr_Selector_Enum::Blas>,  //
         const Dense_Vector_Crtp<IMPL>& VMT              //
         ) -> decltype(Blas::nrm2(VMT.size(), VMT.data(), VMT.increment()))

  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Blas);

    return Blas::nrm2(VMT.size(), VMT.data(), VMT.increment());
  }

  template <typename IMPL>
  auto
  squared_norm_2(const Expr_Selector<Expr_Selector_Enum::Blas> sel,  //
                 const Dense_Vector_Crtp<IMPL>& VMT                  //
                 ) -> decltype(norm_2(sel, VMT))
  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Blas);

    using std::pow;

    return pow(norm_2(sel, VMT), 2);
  }
#endif

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename IMPL>
  auto
  squared_norm_2(const Expr_Selector<Expr_Selector_Enum::Static>,  //
                 const Dense_Vector_Crtp<IMPL>& VMT)
      -> std::enable_if_t<Any_Has_Static_Dimension_v<IMPL>,
                          decltype(squared_norm_2(Expr_Selector<Expr_Selector_Enum::Generic>(),
                                                  VMT.impl()))>

  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Static);

    return squared_norm_2(Expr_Selector<Expr_Selector_Enum::Generic>(), VMT.impl());
  }

  template <typename IMPL>
  auto
  norm_2(const Expr_Selector<Expr_Selector_Enum::Static>,  //
         const Dense_Vector_Crtp<IMPL>& VMT)
      -> std::enable_if_t<Any_Has_Static_Dimension_v<IMPL>,
                          decltype(norm_2(Expr_Selector<Expr_Selector_Enum::Generic>(),
                                          VMT.impl()))>

  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Static);

    return norm_2(Expr_Selector<Expr_Selector_Enum::Generic>(), VMT.impl());
  }
}
