#include <iostream>
#include "../headers/complex.h"
#include "../headers/matrix.h"
#include "../headers/quantumRegister.h"

using namespace quantum;

QuantumRegister::QuantumRegister() {
    Complex c(0,0);
    this->qubits = Matrix<Complex>(c, 1, 1);
    this->numQubits = 1;
}

QuantumRegister::QuantumRegister(int num) {
    Complex c(0,0);
    this->qubits = Matrix<Complex>(c, num, num);
    this->numQubits = num;
}

QuantumRegister::QuantumRegister(Matrix<Complex> q, int num) {
    this->qubits = q;
    this->numQubits = num;
}

Matrix<Complex> QuantumRegister::Qubits() {
    return this->qubits;
}

void QuantumRegister::Qubits(Matrix<Complex> q) {
    this->qubits = q;
}

short int QuantumRegister::NumQubits() {
    return this->numQubits;
}

void QuantumRegister::NumQubits(short int q) {
    this->numQubits = q;
}
