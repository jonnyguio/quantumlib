#include <iostream>
#include "../headers/complex.h"
#include "../headers/matrix.h"
#include "../headers/quantumRegister.h"
#include <cmath>

using namespace quantum;

quantum::QuantumRegister::QuantumRegister() {
    Complex c(0,0);
    this->qubits = Matrix<Complex>(c, 1, 1);
    this->numQubits = 1;
    this->probs = NULL;
}

quantum::QuantumRegister::QuantumRegister(int num) {
    Complex c(0,0);
    this->qubits = Matrix<Complex>(c, pow(2,num), 1);
    this->numQubits = num;
    this->probs = NULL;
}

quantum::QuantumRegister::QuantumRegister(Matrix<Complex> q, int num) {
    this->qubits = q;
    this->numQubits = num;
    this->probs = NULL;
}

Matrix<Complex> quantum::QuantumRegister::Qubits() {
    return this->qubits;
}

void quantum::QuantumRegister::Qubits(Matrix<Complex> q) {
    this->qubits = q;
}

short int quantum::QuantumRegister::NumQubits() {
    return this->numQubits;
}

void quantum::QuantumRegister::NumQubits(short int q) {
    this->numQubits = q;
}

double* quantum::QuantumRegister::Probs() {
    return this->probs;
}

QuantumRegister quantum::QuantumRegister::Tensor(QuantumRegister b) {
    QuantumRegister qReg(b.NumQubits() + this->numQubits);

    if (TAG_DEBUG) std::cout << b.Qubits().R() << " * " << this->qubits.R() << " = " << b.Qubits().R() * this->qubits.R() << std::endl;
    Matrix<Complex> m;
    Complex c(0,0);

    m = this->qubits.kronecker(b.Qubits(), c);

    qReg.Qubits(qReg.Qubits() + m);

    return qReg;
}

void quantum::QuantumRegister::calcProb() {
    double *res;

    if (this->probs != NULL)
        free(this->probs);

    res = (double *) malloc(sizeof(double) * pow(2, this->numQubits));

    for (int i = 0; i < this->qubits.R(); i++) {
            res[i] = pow(this->qubits.M()[i][0].modulo(), 2);
    }

    this->probs = res;
}

void quantum::QuantumRegister::printProb() {
    for (int i = 0; i < this->qubits.R(); i++) {
        std::cout << "|";
        for (int k = 0; k < this->numQubits; k++) {
            if (i % (int) pow(2, this->numQubits - k) < (int) pow(2, this->numQubits - k - 1))
                std::cout << "0";
            else
                std::cout << "1";
        }
        std::cout << "> = " << this->probs[i] * 100 << "%" << std::endl;
    }
}

void quantum::QuantumRegister::measure() {
    srand(time(NULL));
    int random, choice = -1, total = 0;
    random = (int) rand()%100;

    for (int i = 0; i < pow(2, this->numQubits); i++) {
        total += (int) ceil(this->probs[i] * 100);
        if (random < total) {
            choice = i;
            break;
        }
    }
    for (int i = 0; i < pow(2, this->numQubits); i++) {
        if (i == choice) {
            this->probs[i] = 1;
            this->qubits.M()[i][0] = Complex(1, 0);
        }
        else {
            this->qubits.M()[i][0] = Complex(0, 0);
            this->probs[i] = 0;
        }
    }
}

void quantum::QuantumRegister::printState() {
    int controller = 0;
    for (int i = 0; i < this->qubits.R(); i++) {
        if (this->probs[i] > 0) {
            if (!controller)
                controller = 1;
            else
                std::cout << " +";
            if (this->probs[i] < 1)
                std::cout << this->probs[i] << " * ";
            std::cout << "|";
            for (int k = 0; k < this->numQubits; k++) {
                if (i % (int) pow(2, this->numQubits - k) < (int) pow(2, this->numQubits - k - 1))
                    std::cout << "0";
                else
                    std::cout << "1";
            }
            std::cout << ">";
        }
    }
    std::cout << std::endl;
}
