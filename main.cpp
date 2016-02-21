#include <iostream>
#include "headers/complex.h"
#include "headers/matrix.h"
#include "headers/quantumRegister.h"
#include <cstdlib>

using namespace std;
using namespace quantum;

// MAIN FOR TESTS

int main(int argc, char **argv) {
    QuantumRegister qReg1, qReg2;
    Complex c(1,1), c2(2, 3);

    Complex *cdata;
    cdata = (Complex *) malloc(sizeof(Complex) * 4);
    cdata[0] = c;
    cdata[1] = c2;
    cdata[2] = Complex(1,0);
    cdata[3] = Complex(0,0);

    Matrix<Complex> m(cdata, 2, 2);
    qReg1 = *(new QuantumRegister());
    qReg2 = *(new QuantumRegister(m, 2));

    cout << "Printing Quantum Register 1" << endl;
    qReg1.Qubits().print();
    cout << endl;

    cout << "Printing Quantum Register 2" << endl;
    qReg2.Qubits().print();
    cout << endl;

    cout << "Sum: " << c + c2 << endl;
    cout << "Minus: " << c - c2 << endl;
    cout << "Product: " << c * c2 << endl;
    cout << "Division: " << c / c2 << endl;
}
