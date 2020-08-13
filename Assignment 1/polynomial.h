
#ifndef SYDE223_A1_POLYNOMIAL_H
#define SYDE223_A1_POLYNOMIAL_H


#include "doubly-linked-list.h"

class Polynomial {

public:

    DoublyLinkedList coefficientList;

    Polynomial(int *A, int size);

    ~Polynomial();

    Polynomial* add(Polynomial *rhs);
    Polynomial* sub(Polynomial *rhs);
    Polynomial* mul(Polynomial *rhs);

    void print() const;
};


#endif
