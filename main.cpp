#include <iostream>
#include "headers/complex.h"
#include "headers/matrix.h"
#include "headers/quantumRegister.h"
#include "headers/quantumOperator.h"
#include "headers/quantumCircuit.h"
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace quantum;

// MAIN FOR TESTS

int main(int argc, char **argv) {
    QuantumRegister qReg1, qReg2, qReg3, qReg5, qReg6;
    QuantumOperator qzeroOp, qOp, qOp2;
    QuantumCircuit adder;
    Complex c(1,0), c2(1/sqrt(2), 0), c3(-1/sqrt(2), 0), *cdata, *czero, *cHadamard, **cNotData;
    double *probs;

    // TEST FULL ADDER

    cdata = (Complex *) malloc(sizeof(Complex) * 2);
    czero = (Complex *) malloc(sizeof(Complex) * 4);
    cHadamard = (Complex *) malloc(sizeof(Complex) * 4);
    cNotData = (Complex **) malloc(sizeof(Complex*) * 4);

    for (int i = 0; i < 4; i++) {
        cNotData[i] = (Complex *) malloc(sizeof(Complex) * 4);
        for (int j = 0; j < 4; j++) {
            cNotData[i][j] = Complex(0, 0);
        }
    }

    cdata[0] = c;
    cdata[1] = Complex(0, 0);
    Matrix<Complex> m(cdata, 2, 1);
    qReg1 = *(new QuantumRegister(m, 1));

    cdata[0] = Complex(0, 0);
    cdata[1] = c;
    Matrix<Complex> m2(cdata, 2, 1);
    qReg2 = *(new QuantumRegister(m2, 1));

    cdata[0] = Complex(0, 0);
    cdata[1] = c;
    Matrix<Complex> m5(cdata, 2, 1);
    qReg5 = *(new QuantumRegister(m5, 1));

    czero[0] = Complex(1, 0);
    czero[1] = Complex(0, 0);
    czero[2] = Complex(0, 0);
    czero[3] = Complex(0, 0);
    Matrix<Complex> mzero(czero, 2, 2);
    qzeroOp = *(new QuantumOperator(mzero));

    cHadamard[0] = c2;
    cHadamard[1] = c2;
    cHadamard[2] = c2;
    cHadamard[3] = c3;
    Matrix<Complex> m3(cHadamard, 2, 2);
    qOp = *(new QuantumOperator(m3));

    cNotData[0][0] = Complex(1, 0);
    cNotData[1][1] = Complex(1, 0);
    cNotData[2][3] = Complex(1, 0);
    cNotData[3][2] = Complex(1, 0);

    Matrix<Complex> m4(cNotData, 4, 4);
    qOp2 = *(new QuantumOperator(m4));

    adder.AddOp(qOp2);

    cout << "Printing Quantum Register 1" << endl;
    qReg1.Qubits().print();
    cout << endl;

    cout << "Printing Quantum Register 2" << endl;
    qReg2.Qubits().print();
    cout << endl;

    cout << "Printing Quantum Register 5" << endl;
    qReg5.Qubits().print();
    cout << endl;

    cout << "Printing Quantum Operator 1 (HADAMARD)" << endl;
    qOp.Operator().print();
    cout << endl;

    cout << "Printing Quantum Operator 2" << endl;
    qzeroOp.Operator().print();
    cout << endl;

    cout << "Printing Quantum Operator 1 on Quantum Register" << endl;
    qOp.Execute(qReg1);
    qReg1.Qubits().print();
    cout << endl;

    cout << "Printing Quantum Register 1 tensor Quantum Register 2 tensor Quantum Register 5" << endl;
    qReg3 = qReg1.Tensor(qReg2);
    qReg6 = qReg3.Tensor(qReg5);
    qReg3.Qubits().print();
    cout << endl;
    qReg6.Qubits().print();
    cout << endl;

    /*cout << "Printing Quantum Circuit (CNOT) on Quantum Register 3" << endl;
    adder.Execute(&qReg3);
    qReg3.Qubits().print();
    cout << endl;*/

    cout << "Calculating and printing probabilities of Quantum Register 3" << endl;
    qReg6.calcProb();
    qReg6.printProb();
    cout << endl;

    cout << "Measuring" << endl;
    qReg6.measure();
    qReg6.printProb();

    cout << "State:";
    qReg6.printState();
}
