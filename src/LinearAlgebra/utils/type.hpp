//
// * Role:
//
// Useful to pass type information as function argument
//
// By example, instead of
//
//    template<typename T> void foo(int n);
//
// define
//
//    template<typename T> void foo(Type<T>, int n);
//
// Used by:
//   - create_default_storable_vector()
//   - create_default_storable_matrix()
//
#pragma once

namespace LinearAlgebra
{
  // CAVEAT: do not define using type = ... as it would lead to weird
  //         syntax like type<T>::type.
  //
  // Type
  //
  template <typename T>
  struct Type
  {
  };

  template <typename T>
  constexpr auto Type_v = Type<T>();

}
