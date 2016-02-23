#include "headers/complex.h"
#include "headers/matrix.h"
#include "headers/quantumRegister.h"
#include "headers/quantumOperator.h"
#include "headers/quantumCircuit.h"
#include <cstdlib>
#include <cmath>

using namespace quantum;

#ifndef D_GUARD_QCIRCUITS
#define D_GUARD_QCIRCUITS

Complex one(1, 0), zero(0,0);
QuantumOperator opID, opCNOT, opCCNOT, opSWAP, opHADAMARD, carryOPaux, carryOP;
int hadInit = 0;

void init() {
    Complex c2(1/sqrt(2), 0), c3(-1/sqrt(2), 0), *cid, *cHadamard, **cSwap, **cNotData, **ccNotData;

    hadInit = 1;

    cid = (Complex *) malloc(sizeof(Complex) * 4);
    cHadamard = (Complex *) malloc(sizeof(Complex) * 4);
    cSwap = (Complex **) malloc(sizeof(Complex) * 4);
    cNotData = (Complex **) malloc(sizeof(Complex*) * 4);
    ccNotData = (Complex **) malloc(sizeof(Complex*) * 8);

    for (int i = 0; i < 4; i++) {
        cSwap[i] = (Complex *) malloc(sizeof(Complex) * 4);
        for (int j = 0; j < 4; j++) {
            cSwap[i][j] = zero;
        }
    }

    for (int i = 0; i < 4; i++) {
        cNotData[i] = (Complex *) malloc(sizeof(Complex) * 4);
        for (int j = 0; j < 4; j++) {
            cNotData[i][j] = zero;
        }
    }

    for (int i = 0; i < 8; i++) {
        ccNotData[i] = (Complex *) malloc(sizeof(Complex) * 8);
        for (int j = 0; j < 8; j++) {
            ccNotData[i][j] = zero;
        }
    }

    cid[0] = one;
    cid[1] = zero;
    cid[2] = zero;
    cid[3] = one;
    Matrix<Complex> mid(cid, 2, 2);
    opID = *(new QuantumOperator(mid));

    cHadamard[0] = c2;
    cHadamard[1] = c2;
    cHadamard[2] = c2;
    cHadamard[3] = c3;
    Matrix<Complex> mHadamard(cHadamard, 2, 2);
    opHADAMARD = *(new QuantumOperator(mHadamard));

    cSwap[0][0] = one;
    cSwap[1][2] = one;
    cSwap[2][1] = one;
    cSwap[3][3] = one;
    Matrix<Complex> mSwap(cSwap, 4, 4);
    opSWAP = *(new QuantumOperator(mSwap));

    cNotData[0][0] = one;
    cNotData[1][1] = one;
    cNotData[2][3] = one;
    cNotData[3][2] = one;

    Matrix<Complex> mCNOT(cNotData, 4, 4);
    opCNOT = *(new QuantumOperator(mCNOT));


    ccNotData[0][0] = one;
    ccNotData[1][1] = one;
    ccNotData[2][2] = one;
    ccNotData[3][3] = one;
    ccNotData[4][4] = one;
    ccNotData[5][5] = one;
    ccNotData[6][7] = one;
    ccNotData[7][6] = one;

    Matrix<Complex> mCCNOT(ccNotData, 8, 8);
    opCCNOT = *(new QuantumOperator(mCCNOT));
}

QuantumCircuit createCarry(int totalQubits, int order) {
    Complex **carryccNotData;
    Matrix<Complex> m1, m2, m3, m4;

    QuantumOperator qcarryCCNOT, carryOP1, carryOP2, carryOP3;
    QuantumCircuit carry;

    carryccNotData = (Complex **) malloc(sizeof(Complex*) * 16);

    for (int i = 0; i < 16; i++) {
        carryccNotData[i] = (Complex *) malloc(sizeof(Complex) * 16);
        for (int j = 0; j < 8; j++) {
            carryccNotData[i][j] = zero;
        }
    }

    carryccNotData[0][0] = one; carryccNotData[1][1] = one;
    carryccNotData[2][2] = one; carryccNotData[3][3] = one;
    carryccNotData[4][4] = one; carryccNotData[5][5] = one;
    carryccNotData[6][6] = one; carryccNotData[7][7] = one;
    carryccNotData[8][8] = one; carryccNotData[9][9] = one;
    carryccNotData[10][11] = one; carryccNotData[11][10] = one;
    carryccNotData[12][12] = one; carryccNotData[13][13] = one;
    carryccNotData[14][15] = one; carryccNotData[15][14] = one;

    Matrix<Complex> mcarryCCNOT(carryccNotData, 16, 16);
    qcarryCCNOT = *(new QuantumOperator(mcarryCCNOT));

    carryOP1 = opID.Tensor(opCCNOT);
    carryOP2 = opID.Tensor(opCNOT.Tensor(opID));
    carryOP3 = qcarryCCNOT;
    if (!order)
        m1 = carryOP1.Operator();
    else
        m1 = carryOP3.Operator();
    m2 = carryOP2.Operator();
    if (!order)
        m3 = carryOP3.Operator();
    else
        m3 = carryOP1.Operator();

    carryOP = *(new QuantumOperator());
    carryOPaux = *(new QuantumOperator());

    //carry.AddOp(carryOP1);
    //carry.AddOp(carryOP2);
    //carry.AddOp(carryOP3);
    carryOPaux.Operator(m3 * m2 * m1);

    if (!order) {
        for (int i = 0; i < totalQubits; i++) {
            carryOP = carryOPaux;
            for (int j = 1; j < totalQubits; j++) {
                if (i < j)
                    carryOP = carryOP.Tensor(opID.Tensor(opID.Tensor(opID)));
                else
                    carryOP = opID.Tensor(opID.Tensor(opID.Tensor(carryOP)));
            }
            carry.AddOp(carryOP);
        }
    }
    else {
        for (int i = 0; i < totalQubits; i++) {
            if (i > 0)
                carryOP = carryOPaux;
            else
                carryOP = opID.Tensor(opID.Tensor(opID.Tensor(opID)));
            for (int j = 1; j < totalQubits; j++) {
                if (i < j)
                    carryOP = opID.Tensor(opID.Tensor(opID.Tensor(carryOP)));
                else
                    carryOP = carryOP.Tensor(opID.Tensor(opID.Tensor(opID)));
            }
        }
    }

    return carry;
}

QuantumCircuit createSum(int totalQubits) {
    QuantumOperator sumOP1, sumOP2, sumOP, sumOPaux, cNOTaux;
    QuantumCircuit sum;

    Matrix<Complex> m1, m2;

    sumOP1 = opID.Tensor(opCNOT.Tensor(opID));
    sumOP2 = opCNOT.Tensor(opID.Tensor(opID));

    sum.AddOp(sumOP1);

    m1 = sumOP1.Operator();
    m2 = sumOP2.Operator();

    //TERMINAR M2
    sumOP = *(new QuantumOperator());
    sumOPaux = *(new QuantumOperator());

    sumOPaux.Operator(m2 * m1);

    for (int i = 0; i < totalQubits; i++) {
        sumOP = sumOPaux;
        for (int j = 1; j < totalQubits; j++) {
            if (i < j)
                sumOP = opID.Tensor(opID.Tensor(opID.Tensor(sumOP)));
            else
                sumOP = sumOP.Tensor(opID.Tensor(opID.Tensor(opID)));
        }
        sum.AddOp(sumOP);
    }

    return sum;

}
#endif
