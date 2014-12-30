#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
using namespace std;
template <class typ>
class Iterator
{
    public:
        virtual Iterator<typ>& operator++()=0;
        virtual typ* operator->()=0;
        virtual typ & operator*()=0;
        virtual Iterator<typ>& operator--() = 0;     //prefix
        virtual bool operator==(const Iterator<typ>& arg2)  = 0; 
        virtual bool operator!=(const Iterator<typ>& arg2) = 0;
    virtual typ *get() const = 0;
    protected:
    private:
};

#endif // ITERATOR_H
