#include <iostream>
#include <fstream>
#include "headers/complex.h"
#include "headers/matrix.h"
#include "headers/quantumRegister.h"
#include "headers/quantumOperator.h"
#include "headers/quantumCircuit.h"
#include "operators.h"
#include "circuits.h"
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace quantum;

#define QUBITSTEST 1

// MAIN FOR TESTS

int main(int argc, char **argv) {

    Complex *reg, *n;
    QuantumRegister *qRegs, qRegCarry, N;
    QuantumCircuit carry, sum, inverseCarry;
    QuantumOperator adder, iadder, adderMod, sumsfsodjf;

    std::ofstream out("results.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();

    init();
    std::cout << "ué" << std::endl;
    adder = createAdder(QUBITSTEST, 0);
    std::cout << "ué2" << std::endl;
    iadder = createAdder(QUBITSTEST, 1);
    std::cout << "ué3" << std::endl;

    qRegs = (QuantumRegister *) malloc(sizeof(QuantumRegister) * 4);
    reg = (Complex *) malloc(sizeof(Complex) * 2);
    reg[0] = one;
    reg[1] = zero;
    for (int i = 0; i < 4; i++) {
        qRegs[i] = *(new QuantumRegister(Matrix<Complex>(reg, 2, 1), 1));
    }

    opHADAMARD.Execute(&qRegs[1]);
    //opHADAMARD.Execute(&qRegs[2]);

    n = (Complex *) malloc(sizeof(Complex) * 2);
    n[0] = zero;
    n[1] = one;
    N = *(new QuantumRegister(Matrix<Complex>(n, 2, 1), 1));

    for (int i = 1; i < QUBITSTEST; i++) {
        N = N.Tensor(N);
    }
    N.printState();

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
            /*if (i + 1 < QUBITSTEST)
                qRegCarry = qRegCarry.Tensor(qRegs[0].Tensor(qRegs[1].Tensor(qRegs[2].Tensor(qRegs[3]))));
            else*/
                qRegCarry = qRegCarry.Tensor(qRegs[1].Tensor(qRegs[2].Tensor(qRegs[3])));
    }

    qRegCarry.printState();
    cout << endl;

    cout << "Calculating and printing probabilities of Quantum Register Carry" << endl;
    qRegCarry.calcProb();
    qRegCarry.printProb();
    cout << endl;

    /*cout << "Creating SWAP" << endl;

    int controller[1] = {3}, swap[2] = {1, 2};

    cnot = createSWAP(4, (int *) &controller, 1, (int *)  &swap);
    cnot.Operator().print();
    cnot.Execute(&qRegCarry);*/

    cout << "Printing Quantum Circuit (CARRY) on Quantum Register Carry" << endl;
    qRegCarry.printState();


    adder.Execute(&qRegCarry);

    iadder.Execute(&qRegCarry);


    /*std::cout.rdbuf(out.rdbuf());
    carry.print();
    std::cout.rdbuf(coutbuf);*/
    qRegCarry.printState();
    cout << endl;

    cout << "Executing adder modulo N" << endl;

    adderMod = createAdderMod(&qRegCarry, QUBITSTEST, N);
    qRegCarry.calcProb();
    qRegCarry.printProb();
    cout << endl;
    adderMod.Execute(&qRegCarry);

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
