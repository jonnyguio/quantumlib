#include "../headers/constants.h"
#include "../headers/complex.h"
#include "../headers/matrix.h"

#ifndef D_GUARD_QREGISTER
#define D_GUARD_QREGISTER

namespace quantum {
    class QuantumRegister {
        private:
            Matrix<Complex> qubits;
            short int numQubits;
            double *probs;

        public:
            QuantumRegister();
            QuantumRegister(int num);
            QuantumRegister(Matrix<Complex> q, int num);

            Matrix<Complex> Qubits();
            void Qubits(Matrix<Complex> q);

            short int NumQubits();
            void NumQubits(short int n);

            double* Probs();

            QuantumRegister Tensor(QuantumRegister b);

            void calcProb();
            void printProb();
            void printState();
            void measure();
    };
}
#endif
