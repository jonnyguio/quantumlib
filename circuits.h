#include "headers/complex.h"
#include "headers/matrix.h"
#include "headers/quantumRegister.h"
#include "headers/quantumOperator.h"
#include "headers/quantumCircuit.h"
#include "operators.h"
#include <cstdlib>
#include <cmath>

using namespace quantum;

#ifndef D_GUARD_QCIRCUITS
#define D_GUARD_QCIRCUITS

QuantumOperator
    opcarryCCNOT, opID, opCNOT, opCCNOT, opSWAP, opHADAMARD,
    icarryOPaux, carryOPaux, carryOP, carryOP1, carryOP2, carryOP3;

int hadInit = 0;

void init() {
    Complex c2(1/sqrt(2), 0), c3(-1/sqrt(2), 0), *cid, *cHadamard, **cSwap, **cNotData, **ccNotData, **carryccNotData;;

    hadInit = 1;

    cid = (Complex *) malloc(sizeof(Complex) * 4);
    cHadamard = (Complex *) malloc(sizeof(Complex) * 4);
    cSwap = (Complex **) malloc(sizeof(Complex) * 4);
    cNotData = (Complex **) malloc(sizeof(Complex*) * 4);
    ccNotData = (Complex **) malloc(sizeof(Complex*) * 8);
    carryccNotData = (Complex **) malloc(sizeof(Complex*) * 16);

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

    for (int i = 0; i < 16; i++) {
        carryccNotData[i] = (Complex *) malloc(sizeof(Complex) * 16);
        for (int j = 0; j < 8; j++) {
            carryccNotData[i][j] = zero;
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

    carryccNotData[0][0] = one; carryccNotData[1][1] = one;
    carryccNotData[2][2] = one; carryccNotData[3][3] = one;
    carryccNotData[4][4] = one; carryccNotData[5][5] = one;
    carryccNotData[6][6] = one; carryccNotData[7][7] = one;
    carryccNotData[8][8] = one; carryccNotData[9][9] = one;
    carryccNotData[10][11] = one; carryccNotData[11][10] = one;
    carryccNotData[12][12] = one; carryccNotData[13][13] = one;
    carryccNotData[14][15] = one; carryccNotData[15][14] = one;

    Matrix<Complex> mcarryCCNOT(carryccNotData, 16, 16);
    opcarryCCNOT = *(new QuantumOperator(mcarryCCNOT));
}

QuantumOperator createCarry(int totalQubits, int reverse) {
    Matrix<Complex> m1, m2, m3, m4;

    QuantumOperator c;
    Complex **x;
    int ctrls[4], nots[4];

    ctrls[0] = 2; ctrls[1] = 3; nots[0] = 4;
    carryOP1 = createCNOT(4, (int *) ctrls, 2, (int *) nots, 1); //opID.Tensor(opCCNOT);
    ctrls[0] = 2; nots[0] = 3;
    carryOP2 = createCNOT(4, (int *) ctrls, 1, (int *) nots, 1);//opID.Tensor(opCNOT.Tensor(opID));
    ctrls[0] = 1; ctrls[1] = 3; nots[0] = 4;
    carryOP3 = createCNOT(4, (int *) ctrls, 2, (int *) nots, 1);//opcarryCCNOT;
    m1 = carryOP1.Operator();
    m2 = carryOP2.Operator();
    m3 = carryOP3.Operator();

    carryOP = *(new QuantumOperator());
    carryOPaux = *(new QuantumOperator());
    icarryOPaux = *(new QuantumOperator());

    carryOPaux.Operator(m3 * m2 * m1);
    icarryOPaux.Operator(m1 * m2 * m3);
    for (int i = 0; i < (totalQubits * 3 + 1); i++) {
        if (i)
            c = c.Tensor(opID);
        else
            c = opID;
    }

    for (int i = 0; i < totalQubits; i++) {
        if (!reverse)
            carryOP = carryOPaux;
        else
            carryOP = icarryOPaux;
        for (int j = 1; j < totalQubits; j++) {
            if (!reverse) {
                if (i < j)
                    carryOP = carryOP.Tensor(opID.Tensor(opID.Tensor(opID)));
                else
                    carryOP = opID.Tensor(opID.Tensor(opID.Tensor(carryOP)));
            }
            else {
                if (i < j)
                    carryOP = opID.Tensor(opID.Tensor(opID.Tensor(carryOP)));
                else
                    carryOP = carryOP.Tensor(opID.Tensor(opID.Tensor(opID)));
            }
        }
        m1 = c.Operator();
        m2 = carryOP.Operator();
        c.Operator(m2 * m1);
    }

    return c;
}

QuantumOperator createSum(int totalQubits, int reverse) {
    QuantumOperator sumOP1, sumOP2, sumOP, sumOPaux, cNOTaux;
    QuantumCircuit sum;
    QuantumOperator s;

    Matrix<Complex> m1, m2, m3;
    int ctrls[4], nots[4];

    ctrls[0] = 2; nots[0] = 3;
    sumOP1 = createCNOT(4, (int *) ctrls, 1, (int *) nots, 1);//opID.Tensor(opCNOT.Tensor(opID));
    ctrls[0] = 1; nots[0] = 3;
    sumOP2 = createCNOT(4, (int *) ctrls, 1, (int *) nots, 1);//opCNOT.Tensor(opID.Tensor(opID));

    //sum.AddOp(sumOP1);

    m1 = sumOP1.Operator();
    m2 = sumOP2.Operator();

    for (int i = 0; i < (totalQubits * 3 + 1); i++) {
        if (i)
            s = s.Tensor(opID);
        else
            s = opID;
    }
    sum.AddOp(createCNOT(totalQubits * 3 + 1, (int *) ctrls, 1, (int *) nots, 1));

    //TERMINAR M2
    sumOP = *(new QuantumOperator());
    sumOPaux = *(new QuantumOperator());

    sumOPaux.Operator(m2 * m1);

    for (int i = 0; i < totalQubits; i++) {
        sumOP = sumOPaux;
        if (i > 0) {
            if (!reverse)
                carryOP = icarryOPaux;
            else
                carryOP = carryOPaux;
            for (int j = 1; j < totalQubits; j++) {
                if (i < j) {
                    sumOP = opID.Tensor(opID.Tensor(opID.Tensor(sumOP)));
                    carryOP = opID.Tensor(opID.Tensor(opID.Tensor(carryOP)));
                }
                else {
                    sumOP = sumOP.Tensor(opID.Tensor(opID.Tensor(opID)));
                    carryOP = carryOP.Tensor(opID.Tensor(opID.Tensor(opID)));
                }
            }
        }
        else {
            ctrls[0] = totalQubits * 3 - 1;
            nots[0] = totalQubits * 3;
            carryOP = createCNOT(totalQubits * 3 + 1, (int *) ctrls, 1, (int *) nots, 1);
            for (int j = 1; j < totalQubits; j++)
                sumOP = opID.Tensor(opID.Tensor(opID.Tensor(sumOP)));
        }
        m1 = s.Operator();
        m2 = carryOP.Operator();
        m3 = sumOP.Operator();
        if (!reverse)
            s.Operator(m3 * m2 * m1);
        else
            s.Operator(m1 * m2 * m3);
    }

    return s;

}

QuantumOperator createAdder(int totalQubits, int reverse) {
    QuantumOperator carry, sum, res;
    Matrix<Complex> m1, m2;

    carry = createCarry(totalQubits, reverse);
    sum = createSum(totalQubits, reverse);
    m1 = carry.Operator();
    m2 = sum.Operator();

    if (!reverse)
        res.Operator(m2 * m1);
    else
        res.Operator(m1 * m2);

    return res;
}

QuantumOperator createAdderMod(int totalQubits, Matrix<Complex> N) {
    QuantumOperator adderMod;
    return adderMod;
}

#endif
