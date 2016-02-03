#include <iostream>

using namespace std;

class Complex {
    private:

    public:

        double re, im;

        Complex() {}

        Complex(double re, double im) {
            this->re = re;
            this->im = im;
        }

        Complex conj() {
            return Complex(re, -im);
        }

        Complex operator+(const Complex& cc) {
            Complex c;
            c.re = this->re + cc.re; c.im = this->im + cc.im;
            return c;
        }
        Complex operator-(const Complex& cc) {
            Complex c;
            c.re = this->re - cc.re; c.im = this->im - cc.im;
            return c;
        }
        Complex operator*(const Complex& cc) {
            Complex c;
            cout << cc.re << " " << cc.im << "i " << this->re << " " << this->im << "i" << endl;
            c.re = this->re * cc.re - this->im * cc.im;
            c.im = this->re * cc.im + this->im * cc.re;
            return c;
        }
        Complex operator/(Complex& cc) {
            Complex c, caux;
            caux = cc.conj();
            c = (*this) * caux;
            c.re /= (cc.re * cc.re + cc.im * cc.im);
            c.im /= (cc.re * cc.re + cc.im * cc.im);
            return c;
        }
};

class Matrix {

};

class Quantum {

};

std::ostream& operator<<(std::ostream &str, const Complex &c) {
    return str << c.re << " + (" << c.im << ")i";
}

// MAIN FOR TESTS
int main(int argc, char **argv) {
    Complex c(1,1), c2(2, 3);
    int i;

    cout << "Sum: " << c + c2 << endl;
    cout << "Minus: " << c - c2 << endl;
    cout << "Product: " << c * c2 << endl;
    cout << "Division: " << c / c2 << endl;
}
