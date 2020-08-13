#include "polynomial.h"
#include "doubly-linked-list.h"
#include <iostream>

using namespace std;

Polynomial::Polynomial(int A[], int size) {
    for (int i = 0; i < size; i++) {
        coefficientList.insert(A[i], i);
    }
}

Polynomial::~Polynomial() {
    
}

void Polynomial::print() const {

    int size = coefficientList.size();
    for (int i = coefficientList.size()-1; i >= 0; i--) {
        if(i == 0) {
            if(coefficientList.select(i) == 0) {
                continue;
            }
            else if (coefficientList.select(i) < 0) {
                cout << "(" << coefficientList.select(i) << ")" << "x^" << i;
            }
            else {
                cout << coefficientList.select(i) << "x^" << i;
            }
        }
        else if (i == coefficientList.size()-1) {
            if(coefficientList.select(i) == 0) {
                continue;
            }
            else if ((coefficientList.select(i) < 0)) {
                cout << "(" << coefficientList.select(i) << ")" << "x^" << i;

                for (int m = i; m > 0; m--) {
                    if (coefficientList.select(m-1) != 0) {
                        cout << " + ";
                        break;
                    }
                }
            }
            else {
                cout << coefficientList.select(i) << "x^" << i;

                for (int j = i; j > 0; j--) {
                    if (coefficientList.select(j-1) != 0) {
                        cout << " + ";
                        break;
                    }
                }
            }
        }
        else {
            if(coefficientList.select(i) == 0) {
                continue;
            }
            else if (coefficientList.select(i) < 0) {
                cout << "(" << coefficientList.select(i) << ")" << "x^" << i;

                for (int m = i; m > 0; m--) {
                    if (coefficientList.select(m-1) != 0) {
                        cout << " + ";
                        break;
                    }
                }

            }
            else {
                cout << coefficientList.select(i) << "x^" << i;

                for (int m = i; m > 0; m--) {
                    if (coefficientList.select(m-1) != 0) {
                        cout << " + ";
                        break;
                    }
                }

            }
        }
    }
    cout << endl;
}

Polynomial* Polynomial::add(Polynomial* rhs) {
    Polynomial *pre = new Polynomial({}, 0);
    int size = 0;
    if (this->coefficientList.size() >= rhs->coefficientList.size()) {
        size = this->coefficientList.size();
    }
    else {
        size = rhs->coefficientList.size();
    }
    for (int i = 0; i < size; i++) {
        int holder = this->coefficientList.select(i) + rhs->coefficientList.select(i);
        pre->coefficientList.insert(holder, i);
        holder = 0;
    }
    return pre;
}

Polynomial* Polynomial::sub(Polynomial *rhs) {

    Polynomial *pre = new Polynomial({}, 0);
    for (int i = 0; i < 6; i++) {
        int holder = this->coefficientList.select(i) - rhs->coefficientList.select(i);
        pre->coefficientList.insert(holder, i);
        holder = 0;
    }
    return pre;
}

Polynomial* Polynomial::mul(Polynomial *rhs) {
    Polynomial *pre = new Polynomial({}, 0);
    int newsize = this->coefficientList.size() + rhs->coefficientList.size() - 1;
    int *productlist = new int[newsize];

    for (int i = 0; i < newsize; i++)

        productlist[i] = 0;

    for (int i=0; i < this->coefficientList.size(); i++)
    {
        for (int j=0; j< rhs->coefficientList.size(); j++)
            productlist[i+j] += this->coefficientList.select(i)*rhs->coefficientList.select(j);
    }

    for (int i = 0; i < newsize; i++) {
        pre->coefficientList.insert(productlist[i], i);
    }
    return pre;

}
