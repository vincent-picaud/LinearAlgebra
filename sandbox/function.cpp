// -*- compile-command: "g++ -std=c++17 function.cpp && ./a.out"; -*-
#include <cstddef>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>

#include "LinearAlgebra/dense/vector_create_generic_view.hpp"

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
Function_T_T<T> as_Function_T_T(const Differentiable_Function_T_T<T>& f)
{
  using namespace std::placeholders;
  return std::bind(f, _1, _2, nullptr);
}

// A simple demo function
//
template <typename T>
void square_root(const T& x, T* f, T* df, T c)
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
void show_iteration(size_t iter, T x, T f)
{
  constexpr auto max_digits = std::numeric_limits<T>::max_digits10;

  std::cerr << std::setw(4) << iter << " x = " << std::setw(max_digits + 5) << std::setprecision(max_digits) << x
            << " f = " << std::setw(max_digits + 5) << std::setprecision(max_digits) << f << std::endl;
}

template <typename T>
bool Newton(const std::function<void(const T x, T* f, T* df)>& f_obj, T& x0, double epsilon = 1e-10,
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

    if (has_converged)
      break;
  }
  return has_converged;
}

int main()
{
  double x0 = 2;
  double c  = 6;
  auto   f  = [c](const double& x, double* f, double* df) -> void {
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
  auto                                cf = as_Function_T_T(wf);
  Newton<double>(wf, x0);

  double y;
  cf(5, &y);
  std::cout << "\n y " << y;
}
