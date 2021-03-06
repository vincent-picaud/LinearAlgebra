// Allows to add an order of preference to select computational
// subroutines.
//
// By example:
//
// #+begin_src cpp
//   enum class Expr_Selector_Enum : int
//   {
//     Undefined,
//     Generic,
//     Blas,
//     Static,
//     END
//   };
//
// void expr(const Expr_Selector<Expr_Selector_Enum::Generic>&, Args... );  // <-- Generic specialization
// void expr(const Expr_Selector<Expr_Selector_Enum::Blas>&, Args... );     // <-- Blas    specialization
//
// void expr(Args...) // <-- call site
// {
//   expr(Expr_Selector<>(),Args...); // This call will try, *in order*,
// 				   // to use Static, Blas, Generic
// 				   // implementations
// }
// #+end_src
//
#pragma once

#include <type_traits>

namespace LinearAlgebra
{
  // [BEGIN_enum]
  enum class Expr_Selector_Enum : int
  {
    Undefined,
    Generic,
    Blas,
    Static,
    END
  };
 // [END_enum]
  
  // [BEGIN_class]
  template <Expr_Selector_Enum EXPR_ORDER = Expr_Selector_Enum::END>
  struct Expr_Selector
      : Expr_Selector<static_cast<Expr_Selector_Enum>(
            static_cast<std::underlying_type_t<Expr_Selector_Enum>>(EXPR_ORDER) - 1)>
  {
    static constexpr Expr_Selector_Enum value = EXPR_ORDER;
    constexpr operator Expr_Selector_Enum() const noexcept { return value; }
  };
  template <>
  struct Expr_Selector<Expr_Selector_Enum::Undefined>
  {
    static constexpr Expr_Selector_Enum value = Expr_Selector_Enum::Undefined;
    constexpr operator Expr_Selector_Enum() const noexcept { return Expr_Selector_Enum::Undefined; }
  };
  // [END_class]
}
