// -*- compile-command: "g++ -std=c++17 function.cpp && ./a.out"; -*-
#include <cstddef>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>

#include "LinearAlgebra/dense/vector_create_generic_view.hpp"
#include "LinearAlgebra/dense/vector_view.hpp"
#include "LinearAlgebra/vector.hpp"

using namespace LinearAlgebra;

// We define function as std::function
//
// Note: for _local_ use of
// lambda etc... you can use cref ref to avoid some copies
//
template <typename T>
using Function_T_T = std::function<void(const T& x, T* y)>;
template <typename T>
using Differentiable_Function_T_T = std::function<void(const T& x, T* y, T* dy)>;

template <typename T>
Function_T_T<T>
as_Function_T_T(const Differentiable_Function_T_T<T>& f)
{
  using namespace std::placeholders;
  return std::bind(f, _1, _2, nullptr);
}

//////////////////////////////////////////////////////////////////

template <typename T>
using Function_Tn_T = std::function<void(const Generic_Vector_Const_View<T>& x, T* y)>;
template <typename T>
using Differentiable_Function_Tn_T =
    std::function<void(const Generic_Vector_Const_View<T>& x, T* y, Generic_Vector_View<T>* grad)>;

// Note: for performance you can pass view of X0, direction, buffer_Xn, buffer_gradn
//
// CAVEAT: f_Tn_T is passed by reference (hence take care of dangling reference!)
//
template <typename T, typename X0_IMPL, typename DIRECTION_IMPL, typename BUFFER_XN_IMPL,
          typename BUFFER_GRADN_IMPL>
Differentiable_Function_T_T<T>
to_line_search_f_Tn_T_by_reference(const Differentiable_Function_Tn_T<T>& f_Tn_T,
                                   const Dense_Vector_Crtp<X0_IMPL>& X0,
                                   const Dense_Vector_Crtp<DIRECTION_IMPL>& direction,
                                   Dense_Vector_Crtp<BUFFER_XN_IMPL>&& buffer_Xn,
                                   Dense_Vector_Crtp<BUFFER_GRADN_IMPL>&& buffer_gradn)
{
  assert(X0.size() == direction.size());
  assert(X0.size() == buffer_Xn.size());
  assert(X0.size() == buffer_gradn.size());

  // TODO: here, for performance reason, f_Tn_T is taken by reference
  //       maybe define a new "to_line_search" that perform a copy.
  //
  auto wrap = [&f_Tn_T, _X0 = X0.impl(), _direction = direction.impl(),
               _buffer_Xn    = std::move(buffer_Xn.impl()),
               _buffer_gradn = std::move(buffer_gradn.impl())](const T& x, T* y,
                                                               T* dy) mutable -> void {
    if (y or dy)
    {
      _buffer_Xn = _X0 + x * _direction;
      if (dy)
      {
        auto view_buffer_gradn = create_generic_view(_buffer_gradn);
        f_Tn_T(create_generic_view(_buffer_Xn.as_const()), y, &view_buffer_gradn);
        *dy = dot(view_buffer_gradn, _direction);
      }
      else
      {
        f_Tn_T(create_generic_view(_buffer_Xn.as_const()), y, nullptr);
      }
    }
  };

  return {wrap};
}

//////////////////////////////////////////////////////////////////

// Rosenbrock function
//
template <typename T>
void
Rosenbrock(const Generic_Vector_Const_View<T>& x, T* y, Generic_Vector_View<T>* grad, double c)
{
  assert(x.size() == 2);
  assert(grad == nullptr or grad->size() == 2);

  if (y)
  {
    *y = (1 - x[0]) * (1 - x[0]) + c * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]);
  }

  if (grad)
  {
    (*grad)[0] = 2 * (-1 + x[0] + 2 * c * x[0] * x[0] * x[0] - 2 * c * x[0] * x[1]);
    (*grad)[1] = 2 * c * (x[1] - x[0] * x[0]);
  }
}

auto
test_wrap(double c)
{
  auto wrap_Rosenbrock = [c](const Generic_Vector_Const_View<double>& x, double* y,
                             Generic_Vector_View<double>* grad) { Rosenbrock(x, y, grad, c); };

  auto f = Differentiable_Function_Tn_T<double>{wrap_Rosenbrock};
  Vector<double> X0(2), direction(2), buffer_Xn(2), buffer_gradn(2);
  //  Tiny_Vector<double, 2> X0, direction, buffer;

  // Note: using views avoid copying vectors!
  //
  // auto f_lin = to_line_search(f, X0, direction, std::move(buffer));
  auto f_lin = to_line_search_f_Tn_T_by_reference(
      f, create_vector_view(X0), create_vector_view(direction), create_vector_view(buffer_Xn),
      create_vector_view(buffer_gradn));
}

// A simple demo function
//
template <typename T>
void
square_root(const T& x, T* f, T* df, T c)
{
  if (f)
  {
    (*f) = x * x - c;
  }
  if (df)
  {
    (*df) = 2 * x;
  }
}

// void
// foo(double (*f)(const Vector<double>& v)
// {
//   std::cout << "\n ttot " << v[0] + v[1];
// }c
template <typename T>
void
show_iteration(size_t iter, T x, T f)
{
  constexpr auto max_digits = std::numeric_limits<T>::max_digits10;

  std::cerr << std::setw(4) << iter << " x = " << std::setw(max_digits + 5)
            << std::setprecision(max_digits) << x << " f = " << std::setw(max_digits + 5)
            << std::setprecision(max_digits) << f << std::endl;
}

template <typename T>
bool
Newton(const std::function<void(const T x, T* f, T* df)>& f_obj, T& x0, double epsilon = 1e-10,
       size_t max_iter = 20)
{
  T f, df;

  bool has_converged = false;

  for (size_t iter = 1; iter <= max_iter; ++iter)
  {
    f_obj(x0, &f, &df);

    auto delta_x = -f / df;

    has_converged = std::abs(delta_x) < epsilon;

    x0 = x0 + delta_x;

    show_iteration(iter, x0, f);

    if (has_converged) break;
  }
  return has_converged;
}

int
main()
{
  test_wrap(10);
  return 0;

  double x0 = 2;
  double c  = 6;
  auto f    = [c](const double& x, double* f, double* df) -> void {
    if (f)
    {
      (*f) = x * x - c;
    }
    if (df)
    {
      (*df) = 2 * x;
    }
  };

  Differentiable_Function_T_T<double> wf{f};
  auto cf = as_Function_T_T(wf);
  Newton<double>(wf, x0);

  double y;
  cf(5, &y);
  std::cout << "\n y " << y;
}
