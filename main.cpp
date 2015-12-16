#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <cstdio>

using namespace std;

void foo() {
    mpz_class a, b, c;
    a = "-5123";
    b = 1234;
    c = a + b;
    cout << "Sum: " << c << endl;
    cout << "Absolute value is: " << abs(c) << endl;
}

void bar() {
    int a, b, c;
    a = -5123;
    b = 1234;
    c = a + b;
    cout << "Sum: " << c << endl;
    cout << "Absolute value is: " << abs(c) << endl;
}

int main(int argc, char const *argv[]) {
    foo();
    return 0;
}
