#pragma once

#include <cassert>
#include <iostream>
#include <type_traits>

namespace LinearAlgebra
{
  struct Crtp_Final_Impl;

  template <template <typename> class THIS, typename IMPL, template <typename> class SUPERCLASS>
  using Crtp_Find_Impl = SUPERCLASS<
      std::conditional_t<std::is_same_v<IMPL, Crtp_Final_Impl>, THIS<Crtp_Final_Impl>, IMPL>>;

  //! @brief Crtp_Type_Traits
  template <typename IMPL>
  struct Crtp_Type_Traits;

  //! @brief CRTP base class
  template <typename IMPL>
  class Crtp
  {
   public:
    using exact_type  = IMPL;
    using traits_type = Crtp_Type_Traits<exact_type>;

   public:
    const exact_type&
    impl() const noexcept  //!< use exact_type instance
    {
      return static_cast<const exact_type&>(*this);
    };
    exact_type&
    impl() noexcept  //!< use exact_type instance
    {
      return static_cast<exact_type&>(*this);
    };

   protected:
    Crtp& operator=(const Crtp&) = default;
  };

  template <template <typename> class CRTP_INTERFACE, typename OBJ, typename ENABLE = void>
  struct Is_Crtp_Interface_Of : std::false_type
  {
  };

  template <template <typename> class CRTP_INTERFACE, typename OBJ>
  struct Is_Crtp_Interface_Of<
      CRTP_INTERFACE, OBJ,
      std::enable_if_t<std::is_same_v<CRTP_INTERFACE<Crtp_Final_Impl>, OBJ> ||
                       std::is_base_of_v<CRTP_INTERFACE<typename OBJ::exact_type>, OBJ>>>
      : std::true_type
  {
  };

  template <template <typename> class CRTP_INTERFACE, typename OBJ>
  constexpr auto Is_Crtp_Interface_Of_v = Is_Crtp_Interface_Of<CRTP_INTERFACE, OBJ>::value;

}  // namespace LinearAlgebra
