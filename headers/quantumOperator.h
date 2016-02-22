#include "../headers/constants.h"
#include "../headers/complex.h"
#include "../headers/matrix.h"
#include "../headers/quantumRegister.h"

#ifndef D_GUARD_QOPERATOR
#define D_GUARD_QOPERATOR

namespace quantum {
    class QuantumOperator {
        private:
            Matrix<Complex> op;
            double err;

        public:
            QuantumOperator();
            QuantumOperator(Matrix<Complex> defineOp);
            QuantumOperator(Matrix<Complex> defineOp, double nErr);

            Matrix<Complex> Operator();
            void Operator(Matrix<Complex> newOp);

            void Execute(QuantumRegister &qReg);
    };
}

#endif
