#include "../headers/constants.h"
#include "../headers/complex.h"
#include "../headers/matrix.h"
#include "../headers/quantumRegister.h"
#include "../headers/quantumOperator.h"

#ifndef D_GUARD_QCIRCUIT
#define D_GUARD_QCIRCUIT

namespace quantum {
    class QuantumCircuit {
        private:
            QuantumOperator *ops;
            int numOps;

        public:
            QuantumCircuit();
            QuantumCircuit(QuantumOperator *nOps, int nNumOps);

            QuantumOperator* Operations();
            void Operations(QuantumOperator *newOps);

            int NumOps();
            void NumOps(int nNumOps);

            void AddOp(QuantumOperator nOp);
            void Execute(QuantumRegister *qReg1);
    };
}

#endif
