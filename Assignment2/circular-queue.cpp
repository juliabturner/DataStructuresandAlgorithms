#include "circular-queue.h"
#include <iostream>

using namespace std;

typedef CircularQueue::QueueItem QueueItem;
const QueueItem CircularQueue::EMPTY_QUEUE = -9999;

CircularQueue::CircularQueue() {
    items_ = new QueueItem[16];
    capacity_ = 16;
    head_ = 0;
    tail_ = 0;
    size_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity) {

    items_ = new QueueItem[capacity];
    capacity_ = capacity;
    head_ = 0;
    tail_ = 0;
    size_ = 0;

}

CircularQueue::~CircularQueue() {
    delete [] items_;
}

bool CircularQueue::empty() const {
    if (size()== 0) {
        return true;
    }
    else {
        return false;
    }

}

bool CircularQueue::full() const {
    if (size()==capacity_) {
        return true;
    }
    else {
        return false;
    }
}

int CircularQueue::size() const {
    return size_;
}

bool CircularQueue::enqueue(QueueItem value) {
    if (full())
    {
        return false;
    }
    else if (empty()) {
        items_[head_] = value;
        tail_++;
        size_++;
        return true;
    }
    else {
        items_[tail_] = value;
        tail_++;
        size_++;
        return true;
    }
}

QueueItem CircularQueue::dequeue() {
    if (empty())
    {
        return EMPTY_QUEUE;
    }
    else {
        int holder = items_[head_];
        for (int i = 0; i < tail_; i++) {
            items_[i] = items_[i+1];
        }
        tail_--;
        size_--;
        return holder;
    }
}

QueueItem CircularQueue::peek() const {
    if (empty())
    {
        return EMPTY_QUEUE;
    }
    else {
        return items_[head_];
    }
}

void CircularQueue::print() const {
    for (int i = 0; i < size(); i++) {
        cout << "[" << items_[i] << "] ";
    }
    cout << endl;
}
