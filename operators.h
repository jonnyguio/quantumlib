#include "headers/constants.h"
#include "headers/complex.h"
#include "headers/matrix.h"
#include "headers/quantumRegister.h"
#include "headers/quantumOperator.h"
#include "headers/quantumCircuit.h"
#include <cstdlib>
#include <cmath>

using namespace quantum;

#ifndef D_GUARD_QOPERATORS
#define D_GUARD_QOPERATORS

Complex one(1, 0), zero(0,0);

QuantumOperator createCNOT(int tqubits, int *ctrls, int nctrls, int *nots, int nnots) {
    QuantumOperator cnot;
    Complex **m;
    int invert, i, j, k, l, size;

    size = (int) pow(2, tqubits);
    m = (Complex **) malloc(sizeof(Complex*) * size);

    for (i = 0; i < size; i++) {
        m[i] = (Complex *) malloc(sizeof(Complex) * size);
    }


    for (j = 0; j < size; j++) {
        invert = 0;
        for ( i = 0; i < nctrls; i++) {
            if (j % (int) pow(2, tqubits - ctrls[i] + 1) >= (int) pow(2, tqubits - ctrls[i])) {
                invert++;
            }
        }
        if (invert < nctrls)
            invert = 0;
        for ( i = 0; i < size; i++) {
            l = i;
            if (invert) {
                for ( k = 0; k < nnots; k++) {
                    if (j % (int) pow(2, (tqubits + 1 - nots[k])) < (int) pow(2, (tqubits + 1 - nots[k]) - 1))
                        l = (l - (tqubits + 1 - nots[k]));
                    else
                        l = (l + (tqubits + 1 - nots[k]));
                }
                l = l % size;
                if (l < 0)
                    l += size;
            }
            if (l % size == j)
                m[i][j] = one;
            else
                m[i][j] = zero;
        }
    }

    Matrix<Complex> matriz(m, size, size);
    cnot = *(new QuantumOperator(matriz, tqubits));

    return cnot;
}

QuantumOperator createSWAP(int tqubits, int *ctrls, int nctrls, int *swaps) {
    QuantumOperator swapOP;
    Complex **m;
    int
        swap, i, j, k, l, size, c,
        sizeSWAP00, sizeSWAP01, sizeSWAP10, sizeSWAP11;

    sizeSWAP00 = (int) pow(2, (tqubits - swaps[0] + 1));
    sizeSWAP01 = (int) pow(2, (tqubits - swaps[0]));
    sizeSWAP10 = (int) pow(2, (tqubits - swaps[1] + 1));
    sizeSWAP11 = (int) pow(2, (tqubits - swaps[1]));

    size = (int) pow(2, tqubits);
    m = (Complex **) malloc(sizeof(Complex*) * size);

    for (i = 0; i < size; i++) {
        m[i] = (Complex *) malloc(sizeof(Complex) * size);
    }


    for (j = 0; j < size; j++) {
        swap = 0;
        for ( i = 0; i < nctrls; i++) {
            if (j % (int) pow(2, tqubits - ctrls[i] + 1) >= (int) pow(2, tqubits - ctrls[i])) {
                swap++;
            }
        }
        if (swap < nctrls)
            swap = 0;
        //std::cout << swap << std::endl;
        for (i = 0; i < size; i++) {
            l = i;
            c = 0;
            if (swap) {
                if (j % sizeSWAP00 < sizeSWAP01) {
                    if (j % sizeSWAP10 >= sizeSWAP11) {
                        c = (swaps[0] > swaps[1]) ? sizeSWAP11 - sizeSWAP01 : sizeSWAP01 - sizeSWAP11;
                    }
                }
                else {
                    if (j % sizeSWAP10 < sizeSWAP11) {
                        c = (-swaps[0] < -swaps[1]) ? -(sizeSWAP11 - sizeSWAP01) : -(sizeSWAP01 - sizeSWAP11);
                    }
                }
            }

            l = (l - c) % size;

            /*std::cout << "\t" << c << " " << l << " " << j << "\t";
            std::cout << (j % sizeSWAP00 < sizeSWAP01) << " && " <<  (j % sizeSWAP10 >= sizeSWAP11) << "\t";
            std::cout << (j % sizeSWAP00 >= sizeSWAP01) << " && " << (j % sizeSWAP10 < sizeSWAP11) << std::endl;*/

            if (l % size == j)
                m[i][j] = one;
            else
                m[i][j] = zero;
        }
    }

    Matrix<Complex> matriz(m, size, size);
    swapOP = *(new QuantumOperator(matriz, tqubits));

    return swapOP;
}

#endif
