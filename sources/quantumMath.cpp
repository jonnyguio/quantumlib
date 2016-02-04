#include <iostream>
#include "../headers/complex.h"
#include "../headers/matrix.h"
#include <cstdlib>

using namespace std;
using namespace quantum;

// MAIN FOR TESTS

int main(int argc, char **argv) {
    Complex c(1,1), c2(2, 3);

    Complex *cdata;
    cdata = (Complex *) malloc(sizeof(Complex) * 4);
    cdata[0] = c;
    cdata[1] = c2;
    cdata[2] = Complex(1,0);
    cdata[3] = Complex(0,0);

    Matrix<Complex> m(cdata, 2, 2);

    cout << "Sum: " << c + c2 << endl;
    cout << "Minus: " << c - c2 << endl;
    cout << "Product: " << c * c2 << endl;
    cout << "Division: " << c / c2 << endl;

    m.print();
}
