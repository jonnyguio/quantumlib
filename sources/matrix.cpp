#include "../headers/matrix.h"

using namespace quantum;


template<class T>
quantum::Matrix<T>::Matrix() {
    this->rows = 0;
    this->columns = 0;
    this->m = NULL;
}

template<class T>
quantum::Matrix<T>::Matrix(T* data, int r, int c){
    this->rows = r;
    this->columns = c;
    this->m = (T**) malloc(sizeof(T*) * r);
    std::cout << r << " " << c << std::endl;
    for (int i = 0; i < r; i++) {
        this->m[i] = (T*) malloc(sizeof(T) * c);
        for (int j = 0; j < c; j++) {
            std::cout << i << " " << j << std::endl;
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
int quantum::Matrix<T>::R() { return this->rows; }

template<class T>
void quantum::Matrix<T>::R(int r) { this->rows = r; }

template<class T>
int quantum::Matrix<T>::C() { return this->columns; }

template<class T>
void quantum::Matrix<T>::C(int c) { this->columns = c; }

template<class T>
void quantum::Matrix<T>::print() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            std::cout << this->m[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
