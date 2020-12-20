#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

template <class elemType> 
class arrayList
{

private:
    elemType *list; // pointer of the array
    int size;       // number of elements currently in the list
    int maxSize;    // maximum size of the list


public:
    //constructors
    arrayList();
    arrayList(int length);

    //destructor
    ~arrayList();


    //function declarations required by the lab
    bool isEmpty() const;
    bool isFull() const;
    int listSize() const;
    int maxListSize() const;
    void print();
    bool isItemAtEqual(int, elemType);
    void insertAt(int, elemType);
    void insertAtEnd(elemType);
    void removeAt(int);
    elemType retreiveAt(int);
    void replaceAt(int, elemType);
    void clearList();
    arrayList& operator=(const arrayList& otherList);

    elemType getMin();

};


// constructors
template<class elemType>
arrayList<elemType>::arrayList()
{
    this->list = new elemType[1];
    this->maxSize = 1;
    this->size = 0;
}

template<class elemType>
arrayList<elemType>::arrayList(int length)
{
    this->list = new elemType[length];
    this->maxSize = length;
    this->size = 0;
}


//destructor
template<class elemType>
arrayList<elemType>::~arrayList()
{
    delete[] this->list;
};


// checks if list is empty
template<class elemType>
bool arrayList<elemType>::isEmpty() const
{
    return this->size == 0;
}


// checks if list is full
template<class elemType>
bool arrayList<elemType>::isFull() const
{
    return this->size == this->maxSize;
}


// returns the size of the list
template<class elemType>
int arrayList<elemType>::listSize() const
{
    return this->size;
}


// returns the maximum possible size of the list
template<class elemType>
int arrayList<elemType>::maxListSize() const
{
    return this->maxSize;
}


// prints the elements of the list on the console
template<class elemType>
void arrayList<elemType>::print()
{
    cout << "( ";
    for (int i = 0; i < this->size; i++)
    {
        cout << "[" << this->list[i] << "] ";
    }

    cout << ")" << endl << endl;
}


// checks if item at position matches 2nd parameter
template<class elemType>
bool arrayList<elemType>::isItemAtEqual(int pos, elemType elem)
{
    if (pos > this->size - 1 || pos < 0) {
        return false;
    }

    return this->list[pos] == elem;
}


// inserts 2nd parameter at position
template<class elemType>
void arrayList<elemType>::insertAt(int pos, elemType elem)
{
    if (pos < 0 || pos > this->size || this->isFull()) {
        return;
    }

    int i;
    for (i = this->size; i > pos; i--)
    {
        this->list[i] = this->list[i - 1];
    }

    this->list[i] = elem;
    this->size++;
}


// inserts object to end of the list
template<class elemType>
void arrayList<elemType>::insertAtEnd(elemType elem)
{
    if (this->isFull()) {
        return;
    }

    // this->insertAt(this->size, elem);
    this->list[this->size] = elem;
    this->size++;
}


// removes object at position
template<class elemType>
void arrayList<elemType>::removeAt(int pos)
{
    if (pos < 0 || pos >= this->size || this->isEmpty()) {
        return;
    }

    int i;
    for (i = pos; i < this->size - 1; i++)
    {
        list[i] = list[i + 1];
    }

    this->size--;
}


// retrieves object at position
template<class elemType>
elemType arrayList<elemType>::retreiveAt(int pos)
{
    if (pos < 0 || pos >= this->size || this->isEmpty()) {
        return (elemType) 0;
    }

    return this->list[pos];
}


// retrieves string object at position
template<>
string arrayList<string>::retreiveAt(int pos)
{
    if (pos < 0 || pos >= this->size || this->isEmpty()) {
        return "";
    }

    return this->list[pos];
}


// replaces object at position with 2nd parameter
template<class elemType>
void arrayList<elemType>::replaceAt(int pos, elemType elem)
{
    if (pos < 0 || pos >= this->size || this->isEmpty()) {
        return;
    }

    this->list[pos] = elem;
}


// empties the list
template<class elemType>
void arrayList<elemType>::clearList()
{
    this->size = 0;
}


// overload the assignment operator to create a copy of existing array
template<class elemType>
arrayList<elemType>& arrayList<elemType>::operator=(const arrayList<elemType>& otherList)
{
    // self-assignment check
    if (this == &otherList) {
        return *this;
    }

    // storage cannot be reused
    if (otherList.size != this->size) {
        if (this->size > 0) {
            // destroy old storage in this
            delete[] this->list;
            this->size = 0;

            // just in case new throws exception
            this->list = NULL;
        }

        // create storage for this
        this->list = new elemType[otherList.maxSize];
        this->size = otherList.size;
        this->maxSize = otherList.maxSize;
    }

    for (int i = 0; i < otherList.size; ++i)
    {
        this->list[i] = otherList.list[i];
    }

    // return the existing object so we can chain this operator
    return *this;
}


template<class elemType>
elemType arrayList<elemType>::getMin()
{
    arrayList<elemType> duplicate;
    duplicate = *this;
    duplicate.removeAt(0);

    if (duplicate.listSize() == 1) {
        return duplicate.list[0];
    }

    elemType dupMin = duplicate.getMin();
    if (this->list[0] < dupMin) {
        return this->list[0];
    } else {
        return dupMin;
    }

}

#endif
