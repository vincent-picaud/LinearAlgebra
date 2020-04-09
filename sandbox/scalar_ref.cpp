#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

using namespace LinearAlgebra;

template <typename T>
void
print(const T&)
{
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
}

void
test_dot()
{
  Vector<double> V1(5);
  Vector<double> V2(5);

  V1 = 2;
  V2 = 3;

  dot(V1, V2);  //  5 * 2 * 3
}

void
test_dot_return_type()
{
  Vector<std::complex<float>> V1(5);
  V1 = std::complex<float>(3, 2);

  auto Z = dot(V1, V1);

  print(Z);
}

namespace LinearAlgebra
{
  // Fallback
  //
  // Greatly reduce the length of error message. This was one of the
  // main reason to introduce Scalar_CRef
  //
  template <typename DEST_IMPL, typename... ARG_IMPL>
  void
  assign(Crtp<DEST_IMPL>&, const Crtp<ARG_IMPL>&...)
  {
    static_assert(Always_False_v<DEST_IMPL>, "Unknown expression");
  }

  // Scalar
  //
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
    // constexpr Scalar_CRef() noexcept = default;

    constexpr const element_type&
    value() const noexcept
    {
      return this->impl().impl_value();
    }
  };

  template <typename ELEMENT_TYPE>
  class Scalar_CRef;

  template <typename ELEMENT_TYPE>
  struct Crtp_Type_Traits<Scalar_CRef<ELEMENT_TYPE>>
  {
    using element_type = ELEMENT_TYPE;
  };

  template <typename ELEMENT_TYPE>
  class Scalar_CRef final : public Scalar_Crtp<Scalar_CRef<ELEMENT_TYPE>>
  {
   public:
    using base_type    = Scalar_Crtp<Scalar_CRef<ELEMENT_TYPE>>;
    using element_type = typename base_type::element_type;

   private:
    const element_type& _value;

   public:
    // CAVEAT: really use ELEMENT_TYPE and not element_type which
    // prevent C++ to use automatic template deduction:
    //
    // Scalar_CRef(std::complex<double>(3, 4)) <- would NOT work anymore
    //
    constexpr Scalar_CRef(const ELEMENT_TYPE& value) noexcept : _value(value) {}

   protected:
    friend base_type;

    constexpr const element_type&
    impl_value() const noexcept
    {
      return _value;
    }
  };

  static_assert(std::is_trivially_copyable_v<Scalar_CRef<double>>);

}

void
test_scalar()
{
  static_assert(std::is_trivially_copyable_v<Scalar_CRef<double>>);
  static constexpr int n = 3;
  constexpr Scalar_CRef<int> sr{n};

  constexpr int d = sr.value();
  (void)d;
}

// template <typename T>
// auto operator*(const typename std::vector<T>::value_type s, const std::vector<T>& v)
// {
//   std::cerr << __PRETTY_FUNCTION__ << std::endl;
// }

template <typename O>
struct A
{
  const O& _o;
  A(const O& o) noexcept : _o(o){};
};

// This one let the user explicitly define scalar type
template <typename U, typename T>
auto operator*(const Scalar_CRef<U>& s, const std::vector<T>& v)
{
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
  return A{s};
}
template <typename T>
auto operator*(const Scalar_CRef<typename std::vector<T>::value_type>& s, const std::vector<T>& v)
{
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
  return A{s};
}
template <typename T>
auto operator*(const Scalar_CRef<std::complex<typename std::vector<T>::value_type>>& s,
               const std::vector<T>& v)
{
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
  return A{s};
}

void
test_error()
{
  Matrix<int> M1, M0;
  Vector<int> V1;

  //  V1 = M1 * M1 * V1;

  std::vector<int> v;
  auto t = 4. * v;

  std::cout << "\n hello : " << t._o.value();

  auto t2 = std::complex<int>(3, 4) * v;
  std::cout << "\n hello : " << t2._o.value();

  auto t3 = Scalar_CRef(std::complex<double>(3, 4)) * v;
  std::cout << "\n hello : " << t2._o.value();
}

void
test_TODO()
{
  Matrix<int> M1, M0;
  Vector<int> V1;

  //  M0 = M1 + V1; // <- Generate an error
}

int
main()
{
  test_error();
  return 0;

  test_dot();
  return 0;

  test_dot_return_type();
  return 0;
}
