#include "sequential-list.h"
#include "iostream"

using namespace std;

SequentialList::SequentialList(unsigned int cap)
{
    data_ = new DataType[cap];
    size_ = 0;
    capacity_ = cap;
}

SequentialList::~SequentialList()
{
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

unsigned int SequentialList::size() const
{
    return size_;
}

unsigned int SequentialList::capacity() const
{
    return capacity_;
}

bool SequentialList::empty() const
{
    if (size() == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool SequentialList::full() const
{
    if(size() == capacity()) {
        return true;
    }
    else {
        return false;
    }
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
    if (index < size()) {
        return data_[index];
    }
    else {
        return data_[size()-1];
    }
}

unsigned int SequentialList::search(DataType val) const
{
    for (unsigned int i = 0; i < size(); i++) {
        if (data_[i] == val) {
            return i;
        }
    }
    return size();
}

void SequentialList::print() const
{
    for (unsigned int i = 0; i < size(); i++) {
        cout << data_[i] << " | ";
    }
    cout << endl;
}

bool SequentialList::insert(DataType val, unsigned int index)
{
    if (full() || index > size()) {
        return false;
    }

    else if (index < size()) {
        for (unsigned int i = (size() - 1); i > index; i--){
            data_[i + 1] = data_[i];
        }
        data_[index+1] = data_[index];
    }
    data_[index] = val;
    size_++;
    return true;
}

bool SequentialList::insert_front(DataType val)
{
    return insert(val, 0);
}

bool SequentialList::insert_back(DataType val)
{
    return insert(val, size());
}

bool SequentialList::remove(unsigned int index)
{
    if (empty()|| index >= size()) {
        return false;
    }
    else
    {
        for(unsigned int i=index;i<=size()-1;i++)
        {
            data_[i]=data_[i+1];
        }
        data_[size()-1]={};
        size_--;
        
        return true;
    }
    
}

bool SequentialList::remove_front()
{
    return remove(0);
}

bool SequentialList::remove_back()
{
    return remove(size()-1);
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    if (empty()|| index >= capacity()) {
        return false;
    }
    else {
        data_[index] = val;
        return true;
    }
}
