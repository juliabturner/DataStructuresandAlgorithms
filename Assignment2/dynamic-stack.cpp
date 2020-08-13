#include "dynamic-stack.h"
#include <iostream>

using namespace std;

typedef DynamicStack::StackItem StackItem;
const StackItem DynamicStack::EMPTY_STACK = -9999;

DynamicStack::DynamicStack() {
    items_ = new StackItem[16];
    size_ = 0;
    init_capacity_ = 16;
    capacity_ = 16;
}

DynamicStack::DynamicStack(unsigned int capacity){
    items_ = new StackItem[capacity];
    init_capacity_ = capacity;
    capacity_ = capacity;
    size_ = 0;

}

DynamicStack::~DynamicStack() {
    delete [] items_;
}

bool DynamicStack::empty() const {
    if (size()==0) {
        return true;
    }
    else {
        return false;
    }
}

int DynamicStack::size() const {
    return size_;
}

void DynamicStack::push(StackItem value) {

    if (size_ != capacity_) {
        items_[size_] = value;
        size_++;
    }
    else {
        StackItem *double_array = new StackItem[capacity_ *2];

        for (int i = 0; i < size(); i++) {
            double_array[i] = items_[i];
        }
        delete[] items_;
        items_ = double_array;
        capacity_ = capacity_*2;

        items_[size()] = value;
        size_++;
    }
}

DynamicStack::StackItem DynamicStack::pop() {
    if(!empty()) {
        int holder = items_[size()-1];
        items_[size()-1] = {};
        size_--;
        if ((size() <= capacity_/4) && (capacity_/2 >= init_capacity_)) {
                StackItem *half_array = new StackItem[capacity_/2];

                for (int i = 0; i <= size_; i++) {
                    half_array[i] = items_[i];
                }
                delete[] items_;
                items_ = half_array;
                capacity_ = capacity_/2;
            }
        return holder;
    }
    else {
        return EMPTY_STACK;
    }
}

DynamicStack::StackItem DynamicStack::peek() const {
    if(!empty()) {
        return items_[size()-1];
    }
    else {
        return EMPTY_STACK;
    }
}

void DynamicStack::print() const {
    for (int i = size() - 1; i >=0; i--) {
        cout << items_[i] << " | ";
    }
    cout << endl;
}
