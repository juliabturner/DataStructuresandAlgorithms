#include "doubly-linked-list.h"
#include <iostream>

using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
}

DoublyLinkedList::DoublyLinkedList()
{
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;

}
DoublyLinkedList::~DoublyLinkedList()
{

    while (head_)
    {
        Node* current = head_;
        head_ = head_->next;
        delete current;
    }
    
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    if (size() == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool DoublyLinkedList::full() const
{
    if (size() == capacity()) {
        return true;
    }
    else {
        return false;
    }
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if (index < size() && index >= 0) {
        Node* temp = getNode(index);
        return temp->value;
    }
    else {
        return tail_->value;
    }
}

unsigned int DoublyLinkedList::search(DataType value) const
{
    Node* ptr = head_;

    for (int i = 0; i < size(); i++) {
        if (ptr->value == value) {
            return i;
        }
        ptr = ptr->next;
    }
    return size();

}

void DoublyLinkedList::print() const
{
    Node* temp = head_;

    while (temp != NULL) {
        cout << temp->value << "->";
        temp = temp->next;
    }
    cout << endl;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    Node* temp = head_;

    for (int i = 0; i < size(); i++) {
        if (i == index) {
            return temp;
        }
        temp = temp->next;
    }
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    Node* newNode = new Node(value);


    if (index > size() || index < 0 || full())
    {
        return false;
    }
    else {
        if (size() == 0)
        {
            head_ = newNode;
            tail_ = newNode;
            newNode->next = NULL;
            newNode->prev = NULL;

            size_++;

            return true;
        }
        if (index == 0) {

            return insert_front(value);
        }

        if (index == size()) {

            return insert_back(value);
        }

        else {

            Node* current = getNode(index);
            Node* previous = current->prev;

            previous->next = newNode;
            newNode->prev = previous;
            newNode->next = current;
            current->prev = newNode;

            size_++;
            return true;
        }
    }
}

bool DoublyLinkedList::insert_front(DataType value)
{
    if(full()) {
        return false;
    }
    else {
        Node *newNode = new Node(value);
        newNode->value = value;

        if (size() == 0) {
            head_ = newNode;
            tail_ = newNode;
            newNode->next = NULL;
            newNode->prev = NULL;
            size_++;
            return true;
        } else {
            newNode->next = head_;
            newNode->prev = NULL;
            head_->prev = newNode;
            head_ = newNode;
            size_++;
            return true;
        }
    }
}

bool DoublyLinkedList::insert_back(DataType value)
{
    if(full()) {
        return false;
    }
    else {
        Node *newNode = new Node(value);

        if (size() == 0) {
            head_ = newNode;
            tail_ = newNode;
            newNode->next = NULL;
            newNode->prev = NULL;
            size_++;
            return true;
        } else {
            newNode->next = NULL;
            newNode->prev = tail_;
            tail_->next = newNode;
            tail_ = newNode;
            size_++;

            return true;
        }
    }

}

bool DoublyLinkedList::remove(unsigned int index)
{
    if (index < 0 || index >= size() || empty() || index > capacity()) {
        return false;
    }
    else if (index == 0) {
        return remove_front();
    }
    else if (index == size() - 1) {
        return remove_back();
    }
    else {
        Node* newNode = getNode(index);
        newNode->prev->next = newNode->next;
        newNode->next->prev = newNode->prev;
        delete newNode;
        size_--;
        return true;
    }
}


bool DoublyLinkedList::remove_front()
{
    if (empty()) {
        return false;
    }
    else {
        if (tail_ == head_)
        {
            tail_ = NULL;
            head_ = NULL;
        }
        else {
            Node* holder = head_->next;
            head_->next = NULL;
            head_->prev = NULL;
            head_->value = 0;
            head_ = holder;
        }
        size_--;

        return true;
    }
}

bool DoublyLinkedList::remove_back()
{
    if (empty()) {
        return false;
    }
    else {
        if (tail_ == head_)
        {
            tail_ = NULL;
            head_ = NULL;

        }
        else
        {
            tail_ = tail_->prev;
            tail_->next = NULL;

        }
        size_--;
        return true;
    }
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    Node* ptr = getNode(index);
    if (empty() || index >= size()) {
        return false;
    }
    else {
        ptr->value = value;
        return true;
    }
}


