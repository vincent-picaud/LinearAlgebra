//
// Compute: X0 = X1 + α X2
//

#pragma once

#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/size_utils.hpp"

#include "LinearAlgebra/dense/vmt_crtp_fwd.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,  //
         const VMT_Crtp<X0_IMPL>& X0,                                  // X0
         VMT_Crtp<X1_IMPL>& X1,                                        // X1
         const _plus_t_,                                               // +
         const Common_Element_Type_t<X0_IMPL,                          //
                                     X1_IMPL,                          //
                                     X2_IMPL>                          //
             alpha,                                                    // alpha
         const VMT_Crtp<X2_IMPL>& X2                                   // X2
  )
  {
    static_assert(Always_False_v<X0_IMPL>, "Undefined implementation");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  // X0 = X1 + α X2
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  static inline Expr_Selector_Enum
  assign(VMT_Crtp<X0_IMPL>& X0,                // X0
         const VMT_Crtp<X1_IMPL>& X1,          // X1
         const _plus_t_,                       // +
         const Common_Element_Type_t<X0_IMPL,  //
                                     X1_IMPL,  //
                                     X2_IMPL>  //
             alpha,                            // alpha
         const VMT_Crtp<X2_IMPL>& X2           // X2
  )
  {
    return assign(Expr_Selector<>(), X0.impl(), X1.impl(), _plus_, alpha, X2.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  //
  // X0 = X1 - α X2
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  static inline Expr_Selector_Enum
  assign(VMT_Crtp<X0_IMPL>& X0,                //
         const VMT_Crtp<X1_IMPL>& X1,          //
         const _minus_t_,                      //
         const Common_Element_Type_t<X0_IMPL,  //
                                     X1_IMPL,  //
                                     X2_IMPL>  //
             alpha,                            //
         const VMT_Crtp<X2_IMPL>& X2           //
  )
  {
    return assign(Expr_Selector<>(), X0.impl(), X1.impl(), _plus_, -alpha, X2.impl());
  }

  //
  // X0 = α X2 + X1
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  static inline Expr_Selector_Enum
  assign(VMT_Crtp<X0_IMPL>& X0,                //
         const Common_Element_Type_t<X0_IMPL,  //
                                     X1_IMPL,  //
                                     X2_IMPL>  //
             alpha,                            //
         const VMT_Crtp<X2_IMPL>& X2,          //
         const _plus_t_,                       //
         const VMT_Crtp<X1_IMPL>& X1           //
  )
  {
    return assign(X0.impl(), X1.impl(), _plus_, alpha, X2.impl());
  }

  //
  // X0 = X1 + X2
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  static inline Expr_Selector_Enum
  assign(VMT_Crtp<X0_IMPL>& X0,        //
         const VMT_Crtp<X2_IMPL>& X2,  //
         const _plus_t_,               //
         const VMT_Crtp<X1_IMPL>& X1   //
  )
  {
    return assign(X0.impl(), X1.impl(), _plus_, 1, X2.impl());
  }

  //
  // X0 = X1 - X2
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  static inline Expr_Selector_Enum
  assign(VMT_Crtp<X0_IMPL>& X0,        //
         const VMT_Crtp<X2_IMPL>& X2,  //
         const _minus_t_,              //
         const VMT_Crtp<X1_IMPL>& X1   //
  )
  {
    return assign(X0.impl(), X1.impl(), _plus_, -1, X2.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,  //
         VMT_Crtp<X0_IMPL>& X0,                                      // X0
         const VMT_Crtp<X1_IMPL>& X1,                                // X1
         const _plus_t_,                                             // +
         const Common_Element_Type_t<X0_IMPL,                        //
                                     X1_IMPL,                        //
                                     X2_IMPL>                        //
             alpha,                                                  // alpha
         const VMT_Crtp<X2_IMPL>& X2                                 // X2
  )
  {
    // TODO check if X0==X1 etc.. and branch to the proper routine

    fill([&](const auto X1_component,
             const auto X2_component) { return X1_component + alpha * X2_component; },
         X0.impl(), X1.impl(), X2.impl());

    return selected;
  }

  //================================================================
  //  Implementation: Static
  //================================================================
  //
}
