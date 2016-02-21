#include <iostream>
#include "../headers/complex.h"
#include "../headers/matrix.h"

Complex::Complex() {

}

Complex::Complex(double re, double im) {
    this->re = re;
    this->im = im;
}

double Complex::Re() const { return this->re; }
void Complex::Re(double re) { this->re = re; }
double Complex::Im() const { return this->im; }
void Complex::Im(double im) { this->im = im; }

Complex Complex::conj() {
    return Complex(re, -im);
}

Complex Complex::operator+(const Complex& cc) {
    Complex c;
    c.re = this->re + cc.re; c.im = this->im + cc.im;
    return c;
}

Complex Complex::operator-(const Complex& cc) {
    Complex c;
    c.re = this->re - cc.re; c.im = this->im - cc.im;
    return c;
}

Complex Complex::operator*(const Complex& cc) {
    Complex c;
    if (TAG_DEBUG) std::cout << cc.re << " " << cc.im << "i " << this->re << " " << this->im << "i" << std::endl;
    c.re = this->re * cc.re - this->im * cc.im;
    c.im = this->re * cc.im + this->im * cc.re;
    return c;
}

Complex Complex::operator/(Complex& cc) {
    Complex c, caux;
    caux = cc.conj();
    c = (*this) * caux;
    c.re /= (cc.re * cc.re + cc.im * cc.im);
    c.im /= (cc.re * cc.re + cc.im * cc.im);
    return c;
}

template class quantum::Matrix<Complex>;
