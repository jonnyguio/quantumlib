#include <iostream>
#include "../headers/complex.h"
#include "../headers/matrix.h"
#include "../headers/quantumRegister.h"
#include "../headers/quantumOperator.h"

using namespace quantum;

quantum::QuantumOperator::QuantumOperator() {
    this->op = Matrix<Complex>(Complex(1,0), 1, 1);
    this->err = 0.0;
}

quantum::QuantumOperator::QuantumOperator(Matrix<Complex> newOp) {
    this->op = newOp;
    this->err = 0.0;
}

quantum::QuantumOperator::QuantumOperator(Matrix<Complex> newOp, double nErr) {
    this->op = newOp;
    this->err = nErr;
}

void quantum::QuantumOperator::Operator(Matrix<Complex> newOp) {
    this->op = newOp;
}

Matrix<Complex> quantum::QuantumOperator::Operator() {
    return this->op;
}

void quantum::QuantumOperator::Execute(QuantumRegister *qReg1) {
    Matrix<Complex> m1, m2, m3;
    m1 = this->op;
    m2 = qReg1->Qubits();
    if (qReg1->Qubits().R() != this->op.C()) {
        return;
    }
    else {
        m3 = m1 * m2;
        qReg1->Qubits(m3);
    }
}

QuantumOperator quantum::QuantumOperator::Tensor(QuantumOperator b) {
    Matrix<Complex> m;
    Complex c(0,0);

    m = this->op.kronecker(b.Operator(), c);

    QuantumOperator qOp(m);

    return qOp;
}
