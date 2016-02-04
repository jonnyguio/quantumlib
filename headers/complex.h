#include <cstdlib>

#ifndef D_GUARD_COMPLEX
#define D_GUARD_COMPLEX

class Complex {
    private:
        double re, im;

    public:

        Complex();

        Complex(double re, double im);

        double Re() const;
        void Re(double re);
        double Im() const;
        void Im(double Im);

        Complex conj();

        Complex operator+(const Complex& cc);
        Complex operator-(const Complex& cc);
        Complex operator*(const Complex& cc);
        Complex operator/(Complex& cc);
};

inline std::ostream& operator<<(std::ostream &str, const Complex &c) {
    if (c.Im()) {
        return str << c.Re() << " + (" << c.Im() << ")i";
    }
    return str << c.Re();
}

#endif
