#include <iostream>
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

            Matrix(T* data, int r, int c);

            Matrix(T** data, int r, int c);

            int R();
            int C();
            void R(int r);
            void C(int c);

            void print();
    };

}

#endif
