#include <iostream>
#include "../headers/complex.h"
#include "../headers/matrix.h"
#include "../headers/quantumRegister.h"
#include "../headers/quantumOperator.h"
#include "../headers/quantumCircuit.h"
#include <cstdlib>

using namespace quantum;

quantum::QuantumCircuit::QuantumCircuit() {
    this->ops = NULL;
    this->numOps = 0;
}

quantum::QuantumCircuit::QuantumCircuit(QuantumOperator *nOps, int nNumOps) {
    this->ops = nOps;
    this->numOps = nNumOps;
}

void quantum::QuantumCircuit::Operations(QuantumOperator *nOps) {
    this->ops = nOps;
}

QuantumOperator* quantum::QuantumCircuit::Operations() {
    return this->ops;
}

int quantum::QuantumCircuit::NumOps() {return this->numOps;}
void quantum::QuantumCircuit::NumOps(int nNumOps) { this->numOps = nNumOps;}

void quantum::QuantumCircuit::AddOp(QuantumOperator nOp) {
    this->ops = (QuantumOperator *) realloc(this->ops, sizeof(QuantumOperator) * (this->numOps + 1));
    this->ops[this->numOps] = nOp;
    this->numOps++;
}

void quantum::QuantumCircuit::print() {
    for (int i = 0; i < this->numOps; i++) {
        this->ops[i].Operator().print();
        std::cout << std::endl;
    }
}

void quantum::QuantumCircuit::Execute(QuantumRegister *qReg1) {
    for (int i = 0; i < this->numOps; i++) {
        this->ops[i].Execute(qReg1);
    }
}
