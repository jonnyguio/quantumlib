#include "../headers/constants.h"
#include "../headers/complex.h"
#include "../headers/matrix.h"

using namespace quantum;

class QuantumRegister {
    private:
        Matrix<Complex> qubits;
        short int numQubits;
    public:
        QuantumRegister();
        QuantumRegister(int num);
        QuantumRegister(Matrix<Complex> q, int num);

        Matrix<Complex> Qubits();
        void Qubits(Matrix<Complex> q);

        short int NumQubits();
        void NumQubits(short int n);
};
