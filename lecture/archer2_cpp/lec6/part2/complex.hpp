#ifndef CPPEX_COMPLEX_COMPLEX_HPP
#define CPPEX_COMPLEX_COMPLEX_HPP

#include <cmath>

// Simple complex number class
/* Add template typename definition here */
template <typename T>
class Complex {
public:
  // Default value is zero
  Complex() = default;
  Complex(T real);
  Complex(T real, T imag);

  // Access components
  T real() const;
  T imag() const;

  // Compute the complex conjugate
  Complex conj() const;

  // Compute the magnitude and squared magnitude
  T norm() const;
  T norm2() const;

  // Declare comparisons
  template<typename U1,typename U2>
  friend bool operator==(Complex<U1> const& a, Complex<U2> const& b);

  template<typename U1,typename U2>
  friend bool operator!=(Complex<U1> const& a, Complex<U2> const& b);

  // Declare binary arithmetic operators
  /* What if I want to add a Complex<double> to a Complex<int>?
     What would be returned in this case? What should the return type
     be to make this flexible?
  */

  template<typename U>
  friend Complex<U> operator+(Complex<U> const& a, Complex<U> const& b);

  // decltype(U1{}+U2{}) or std::common_type_t<U1,U2>
  template <typename U1, typename U2>
  friend Complex<decltype(U1{}+U2{})> operator+(const Complex<U1>& a, const Complex<U2>& b);

  template<typename U>
  friend Complex<U> operator-(Complex<U> const& a, Complex<U> const& b);

  template<typename U>
  friend Complex<U> operator*(Complex<U> const& a, Complex<U> const& b);

  template<typename U>
  friend Complex<U> operator/(Complex<U> const& a, Complex<U> const& b);
  // Question: how would you declare multiplication and division by a real number?

  // Unary negation
  template<typename U>
  friend Complex<U> operator-(Complex<U> const& a);

private:
  T re = 0.0;
  T im = 0.0;
};

template <typename T>
Complex<T>::Complex(T real) : re(real) {}

template <typename T>
Complex<T>::Complex(T real, T imag) : re(real), im(imag) {}


template <typename T>
T Complex<T>::real() const {
  return re;
}

template <typename T>
T Complex<T>::imag() const {
  return im;
}

template <typename T>
Complex<T> Complex<T>::conj() const {
  return Complex<T>{re, -im};
}

template <typename T>
T Complex<T>::norm() const {
  return std::sqrt(norm2());
}

template <typename T>
T Complex<T>::norm2() const {
  return re*re + im*im;
}

template<typename U1,typename U2>
bool operator==(Complex<U1> const& a, Complex<U2> const& b) {
  return (a.re == b.re) && (a.im == b.im);
}

template<typename U1,typename U2>
bool operator!=(Complex<U1> const& a, Complex<U2> const& b) {
  return !(a == b);
}


template<typename U>
Complex<U> operator+(Complex<U> const& a, Complex<U> const& b) {
  return Complex<U>{a.re + b.re, a.im + b.im};
}

template<typename U1, typename U2>
Complex<decltype(U1{}+U2{})> operator+(Complex<U1> const& a, Complex<U2> const& b) {
  return Complex<decltype(U1{}+U2{})> {a.re + b.re, a.im + b.im};
}


template<typename U>
Complex<U> operator-(Complex<U> const& a, Complex<U> const& b) {
  return Complex<U>{a.re - b.re, a.im - b.im};
}

template<typename U>
Complex<U> operator*(Complex<U> const& a, Complex<U> const& b) {
  return Complex<U>{a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re};
}

template <typename U>
Complex<U> operator-(Complex<U> const& a) {
  return Complex<U>{-a.re, -a.im};
}


#endif
