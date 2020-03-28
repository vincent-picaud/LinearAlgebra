// Define: V = α V
//
// CAVEAT: two cases:
// - V0 = α V1
// - V0 = α V0
#pragma once

#include "LinearAlgebra/blas/blas.hpp"

#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/size_utils.hpp"

#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

// specific includes
#include "LinearAlgebra/dense/vector_fill.hpp"
#include "LinearAlgebra/dense/vector_is_same.hpp"
#include "LinearAlgebra/dense/vector_transform.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL_DEST, typename IMPL_ARG_1>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         Vector_Crtp<IMPL_DEST>& dest,                              // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1> alpha,  // alpha
         const Vector_Crtp<IMPL_ARG_1>& arg_1                       // arg_1
  )
  {
    static_assert(Always_False_v<IMPL_DEST>, "Undefined");
    return selected;
  }

  template <typename IMPL_DEST, typename IMPL_ARG_1>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         Vector_Crtp<IMPL_DEST>& dest,                              // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1> alpha,  // alpha
         const _vector_0_t_                                         // arg_1
  )
  {
    static_assert(Always_False_v<IMPL_DEST>, "Undefined");
    return selected;
  }
  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //

  // V0 = α V1
  template <typename IMPL_DEST, typename IMPL_ARG_1>
  static inline Expr_Selector_Enum
  assign(Vector_Crtp<IMPL_DEST>& dest,                              // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1> alpha,  // alpha
         const Vector_Crtp<IMPL_ARG_1>& arg_1                       // arg_1
  )
  {
    if (is_same(dest.impl(), arg_1.impl()))
    {
      return assign(Expr_Selector<>(), dest.impl(), alpha, _vector_0_);
    }
    else
    {
      return assign(Expr_Selector<>(), dest.impl(), alpha, arg_1.impl());
    }
  }

  // Special case V0 = α V0
  template <typename IMPL_DEST>
  static inline Expr_Selector_Enum
  assign(Vector_Crtp<IMPL_DEST>& dest,                  // dest
         const Common_Element_Type_t<IMPL_DEST> alpha,  // alpha
         const _vector_0_t_                             // arg_1
  )
  {
    return assign(Expr_Selector<>(), dest.impl(), alpha, _vector_0_);
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  // from: to:
  //

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //
  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  //
  template <typename IMPL_DEST, typename IMPL_ARG_1>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Dense_Vector_Crtp<IMPL_DEST>& dest,                        // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1> alpha,  // alpha
         const Dense_Vector_Crtp<IMPL_ARG_1>& arg_1                 // arg_1
  )
  {
    // Basic implementation for test
    fill_indexed([alpha, &arg_1](const std::size_t i) { return alpha * arg_1[i]; }, dest);

    return selected;
  }

  template <typename IMPL_DEST>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Dense_Vector_Crtp<IMPL_DEST>& dest,            // dest
         const Common_Element_Type_t<IMPL_DEST> alpha,  // alpha
         const _vector_0_t_                             // arg_1
  )
  {
    // Basic implementation for test
    transform([alpha](const auto& dest_component) { return alpha * dest_component; }, dest);

    return selected;
  }

  //================================================================
  //  Implementation: CBlas
  //================================================================
  //

#if (HAS_BLAS)
  // TODO
#endif

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename IMPL_DEST, typename IMPL_ARG_1>
  static inline std::enable_if_t<Any_Has_Static_Size_v<IMPL_DEST, IMPL_ARG_1>, Expr_Selector_Enum>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Dense_Vector_Crtp<IMPL_DEST>& dest,                        // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1> alpha,  // alpha
         const Dense_Vector_Crtp<IMPL_ARG_1>& arg_1                 // arg_1
  )
  {
    // Skip dynamic BLAS like specialization
    return assign(Expr_Selector<Expr_Selector_Enum::Generic>(), dest, alpha, arg_1);
  }

  template <typename IMPL_DEST>
  static inline std::enable_if_t<Any_Has_Static_Size_v<IMPL_DEST>, Expr_Selector_Enum>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Dense_Vector_Crtp<IMPL_DEST>& dest,            // dest
         const Common_Element_Type_t<IMPL_DEST> alpha,  // alpha
         const _vector_0_t_                             // arg_1
  )
  {
    // Skip dynamic BLAS like specialization
    return assign(Expr_Selector<Expr_Selector_Enum::Generic>(), dest, alpha, _vector_0_);
  }
}
