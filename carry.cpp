#include "carry.h"

using namespace std;

Carry::Carry(bool c0, bool a, bool b) {
    this->c0 = c0;
    this->a = a;
    this->b = b;
    this->c = 0;
}

void Carry::executeCarry() {
    if (a && b)
        c = !c;
    if (a)
        b = !b;
    if (c0 && b)
        c = !c;
}

bool Carry::readCarry() {
    return c;
}
