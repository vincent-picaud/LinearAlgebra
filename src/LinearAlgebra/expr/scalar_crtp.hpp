// file:scalar_crtp.org
#pragma once

#include "LinearAlgebra/utils/crtp.hpp"

#include <ccomplex>

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Scalar_Crtp
  //////////////////////////////////////////////////////////////////
  //
  // [BEGIN_Scalar_Crtp]
  template <typename IMPL>
  class Scalar_Crtp : public Crtp_Find_Impl<Scalar_Crtp, IMPL, Crtp>
  {
   public:
    using base_type = Crtp_Find_Impl<Scalar_Crtp, IMPL, Crtp>;
    using base_type::impl;

    using exact_type  = typename base_type::exact_type;
    using traits_type = typename base_type::traits_type;

    using element_type = typename traits_type::element_type;

   public:
    constexpr const element_type&
    value() const noexcept
    {
      return this->impl().impl_value();
    }

   protected:
    // Prevent object slicing
    constexpr Scalar_Crtp() noexcept                   = default;
    constexpr Scalar_Crtp(const Scalar_Crtp&) noexcept = default;
  };
  // [END_Scalar_Crtp]

  //////////////////////////////////////////////////////////////////
  // Scalar
  //////////////////////////////////////////////////////////////////
  //
  // [BEGIN_Scalar]
  template <typename ELEMENT_TYPE>
  class Scalar;

  template <typename ELEMENT_TYPE>
  struct Crtp_Type_Traits<Scalar<ELEMENT_TYPE>>
  {
    using element_type = ELEMENT_TYPE;
  };

  template <typename ELEMENT_TYPE>
  class Scalar : public Scalar_Crtp<Scalar<ELEMENT_TYPE>>
  {
    // avoid some recurrent errors like:
    //    Scalar<ALPHA_IMPL>(0)
    // instead of
    //    Scalar<Element_Type_t<ALPHA_IMPL>>(0)
    //
    static_assert(not Is_Crtp_Interface_Of_v<Scalar_Crtp, ELEMENT_TYPE>);

   public:
    using base_type    = Scalar_Crtp<Scalar<ELEMENT_TYPE>>;
    using element_type = typename base_type::element_type;

   private:
    // CAVEAT: check that this does not induce dangling reference
    //         before this line was:
    //         const element_type& _value;
    element_type _value;

   public:
    // CAVEAT: really use ELEMENT_TYPE and not element_type which
    // prevent C++ to use automatic template deduction:
    //
    // Scalar(std::complex<double>(3, 4)) <- would NOT work anymore
    //
    constexpr Scalar(const ELEMENT_TYPE& value) noexcept : _value(value) {}

   protected:
    friend base_type;

    constexpr const element_type&
    impl_value() const noexcept
    {
      return _value;
    }
  };

  static_assert(std::is_trivially_copyable_v<Scalar<double>>);

  // [END_Scalar]

  // TODO: not sure it is really usefull... comment me and check
  // complex specialization
  // -> define contruction from real part only
  // template <typename ELEMENT_TYPE>
  // class Scalar<std::complex<ELEMENT_TYPE>> final
  //     : public Scalar_Crtp<Scalar<std::complex<ELEMENT_TYPE>>>
  // {
  //  public:
  //   using base_type    = Scalar_Crtp<Scalar<std::complex<ELEMENT_TYPE>>>;
  //   using element_type = typename base_type::element_type;

  //  private:
  //   const element_type& _value;

  //  public:
  //   // CAVEAT: really use ELEMENT_TYPE and not element_type which
  //   // prevent C++ to use automatic template deduction:
  //   //
  //   // Scalar(std::complex<double>(3, 4)) <- would NOT work anymore
  //   //
  //   constexpr Scalar(const ELEMENT_TYPE& value) noexcept : _value(value) {}
  //   constexpr Scalar(const std::complex<ELEMENT_TYPE>& value) noexcept : _value(value) {}

  //  protected:
  //   friend base_type;

  //   constexpr const element_type&
  //   impl_value() const noexcept
  //   {
  //     return _value;
  //   }
  // };

}  // namespace LinearAlgebra
