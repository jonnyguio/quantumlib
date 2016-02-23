#include <iostream>
#include <fstream>
#include "headers/complex.h"
#include "headers/matrix.h"
#include "headers/quantumRegister.h"
#include "headers/quantumOperator.h"
#include "headers/quantumCircuit.h"
#include "circuits.h"
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace quantum;

#define QUBITSTEST 2

// MAIN FOR TESTS

int main(int argc, char **argv) {

    Complex *reg;
    QuantumRegister *qRegs, qRegCarry;
    QuantumCircuit carry, sum, inverseCarry;
    std::ofstream out("results.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();

    init();
    std::cout << "ué" << std::endl;
    carry = createCarry(QUBITSTEST, 0);
    inverseCarry = createCarry(QUBITSTEST, 1);
    sum = createSum(QUBITSTEST);
    std::cout << "ué2" << std::endl;

    qRegs = (QuantumRegister *) malloc(sizeof(QuantumRegister) * 4);
    reg = (Complex *) malloc(sizeof(Complex) * 2);
    reg[0] = one;
    reg[1] = zero;
    for (int i = 0; i < 4; i++) {
        qRegs[i] = *(new QuantumRegister(Matrix<Complex>(reg, 2, 1), 1));
    }

    opHADAMARD.Execute(&qRegs[1]);
    opHADAMARD.Execute(&qRegs[2]);

    // Test Carry

    cout << "Printing Quantum Register 0" << endl;
    qRegs[0].Qubits().print();
    cout << endl;

    cout << "Printing Quantum Register A" << endl;
    qRegs[1].Qubits().print();
    cout << endl;

    cout << "Printing Quantum Register B" << endl;
    qRegs[2].Qubits().print();
    cout << endl;

    cout << "Printing Quantum Register C (carry)" << endl;
    qRegs[3].Qubits().print();
    cout << endl;

    cout << "Printing Quantum Register Zero tensor Quantum Register A tensor Quantum Register B tensor Quantum Register C" << endl;
    for (int i = 0; i < QUBITSTEST; i++) {
        if (!i)
            qRegCarry = qRegs[0].Tensor(qRegs[1].Tensor(qRegs[2].Tensor(qRegs[3])));
        else
            qRegCarry = qRegCarry.Tensor(qRegs[1].Tensor(qRegs[2].Tensor(qRegs[3])));
    }
    qRegCarry.printState();
    cout << endl;

    cout << "Calculating and printing probabilities of Quantum Register Carry" << endl;
    qRegCarry.calcProb();
    qRegCarry.printProb();
    cout << endl;

    cout << "Printing Quantum Circuit (CARRY) on Quantum Register Carry" << endl;
    qRegCarry.printState();

    carry.Execute(&qRegCarry);
    qRegCarry.calcProb();
    qRegCarry.printProb();
    cout << endl;
    sum.Execute(&qRegCarry);
    inverseCarry.Execute(&qRegCarry);

    std::cout.rdbuf(out.rdbuf());
    sum.print();
    std::cout.rdbuf(coutbuf);
    qRegCarry.printState();
    cout << endl;

    cout << "Calculating and printing probabilities of Quantum Register Carry" << endl;
    qRegCarry.calcProb();
    qRegCarry.printProb();
    cout << endl;

    cout << "Measuring" << endl;
    qRegCarry.measure();
    qRegCarry.printProb();

    cout << "State: ";
    qRegCarry.printState();
}
