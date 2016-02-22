#include <iostream>
#include "../headers/constants.h"
#include "../headers/complex.h"
#include <cstdlib>

#ifndef D_GUARD_MATRIX
#define D_GUARD_MATRIX

namespace quantum {
    template<class T>
    class Matrix {
        private:
            int
                rows, columns;
            T**
                m;

        public:
            Matrix();

            Matrix(int r, int c);

            Matrix(T data, int r, int c);

            Matrix(T* data, int r, int c);

            Matrix(T** data, int r, int c);

            int R();
            int C();
            T** M();
            void R(int r);
            void C(int c);
            void M(T** nm);

            void print();

            Matrix<T> kronecker(Matrix<T> b, T initial);
            Matrix<T> operator+(Matrix<T> &b);
            Matrix<T> operator-(Matrix<T> &b);
            Matrix<T> operator*(Matrix<T> &b);
    };
}

template<class T>
quantum::Matrix<T>::Matrix() {
    this->rows = 0;
    this->columns = 0;
    this->m = NULL;
}

template<class T>
quantum::Matrix<T>::Matrix(T data, int r, int c){
    this->rows = r;
    this->columns = c;
    this->m = (T**) malloc(sizeof(T*) * r);
    if (TAG_DEBUG) std::cout << r << " " << c << std::endl;
    for (int i = 0; i < r; i++) {
        this->m[i] = (T*) malloc(sizeof(T) * c);
        for (int j = 0; j < c; j++) {
            if (TAG_DEBUG) std::cout << i << " " << j << std::endl;
            this->m[i][j] = data;
            //this->m[i][j] = (r == 1 || c == 1) ? data[i + j] :  data[i * r + j];
        }
    }
}

template<class T>
quantum::Matrix<T>::Matrix(T* data, int r, int c){
    this->rows = r;
    this->columns = c;
    this->m = (T**) malloc(sizeof(T*) * r);
    if (TAG_DEBUG) std::cout << r << " " << c << std::endl;
    for (int i = 0; i < r; i++) {
        this->m[i] = (T*) malloc(sizeof(T) * c);
        for (int j = 0; j < c; j++) {
            if (TAG_DEBUG) std::cout << i << " " << j << std::endl;
            this->m[i][j] = (r == 1 || c == 1) ? data[i + j] :  data[i * r + j];
        }
    }
}

template<class T>
quantum::Matrix<T>::Matrix(T** data, int r, int c){
    this->rows = r;
    this->columns = c;
    this->m = data;
}

template<class T>
void quantum::Matrix<T>::M(T** nm) { this->m = nm; }

template<class T>
T** quantum::Matrix<T>::M() { return this->m; }

template<class T>
void quantum::Matrix<T>::R(int r) { this->rows = r; }

template<class T>
int quantum::Matrix<T>::R() { return this->rows; }

template<class T>
void quantum::Matrix<T>::C(int c) { this->columns = c; }

template<class T>
int quantum::Matrix<T>::C() { return this->columns; }


template<class T>
void quantum::Matrix<T>::print() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            std::cout << this->m[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

template<class T>
quantum::Matrix<T> quantum::Matrix<T>::operator+(Matrix<T> &b) {
    int i, j, row, col;
    T **x, **y, **z, value;

    Matrix<T> m(value, this->rows, this->columns);

    if (this->rows < b.R())
        row = this->rows;
    else
        row = b.R();

    if (this->columns < b.C())
        col = this->columns;
    else
        col = b.C();


    x = m.M();
    y = this->m;
    z = b.M();

    for (i = 0; i < row; i++) {
        for (j= 0; j < col; j++) {
            x[i][j] = y[i][j] + z[i][j];
        }
    }

    return m;
}

template<class T>
quantum::Matrix<T> quantum::Matrix<T>::operator-(Matrix<T> &b) {
    int i, j, row, col;
    T **x, **y, **z, value;

    Matrix<T> m(value, this->rows, this->columns);

    if (this->rows < b.R())
        row = this->rows;
    else
        row = b.R();

    if (this->columns < b.C())
        col = this->columns;
    else
        col = b.C();


    x = m.M();
    y = this->m;
    z = b.M();

    for (i = 0; i < row; i++) {
        for (j= 0; j < col; j++) {
            x[i][j] = y[i][j] - z[i][j];
        }
    }

    return m;
}

template<class T>
quantum::Matrix<T> quantum::Matrix<T>::operator*(Matrix<T> &b) {
    int i, j, k;
    T **x, **y, **z, value;

    //std::cout << b.C() << std::endl;
    Matrix<T> m(value, this->rows, b.C());

    if (this->columns != b.R())
        return m;

    x = m.M();
    y = this->m;
    z = b.M();

    for (i = 0; i < this->rows; i++) {
        for (j= 0; j < b.C(); j++) {
            for (k = 0; k < b.R(); k++) {
                x[i][j] = x[i][j] + y[i][k] * z[k][j];
            }
        }
    }

    return m;
}

template<class T>
quantum::Matrix<T> quantum::Matrix<T>::kronecker(Matrix<T> b, T initial) {
    int i, j, k, l, rows, cols;
    T **x, **y, **z;

    if (TAG_DEBUG) std::cout << "ué" << std::endl;
    Matrix<T> m(initial, this->rows * b.R(), this->columns * b.C());

    x = m.M();
    y = this->m;
    z = b.M();

    rows = b.R();

    cols = b.C();

    if (TAG_DEBUG) std::cout << this->rows << " " << b.R() << " " << this->columns << " " << b.C() << std::endl;

    for (i = 0; i < this->rows; i++) {
        for (j = 0; j < b.R(); j++) {
            for (k = 0; k < this->columns; k++) {
                for (l = 0; l < b.C(); l++) {
                    if (TAG_DEBUG) std::cout << "x[" << i * rows + j << "][" << k * cols + l << "] = " << y[i][k] << " * " << z[j][l] << std::endl;
                    x[i * rows + j][k * cols + l] = y[i][k] * z[j][l];
                }
            }
        }
    }

    return m;
}

#endif
