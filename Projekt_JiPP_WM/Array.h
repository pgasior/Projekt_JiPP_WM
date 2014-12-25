#ifndef ARRAY_H
#define ARRAY_H

#include "Container.h"

#include "Iterator.h"
#include <iostream>
#include <cstdlib>

using namespace std;

class unknown_element_exception : public std::exception
{

    virtual const char* what() const throw()
    {
        return "Probowano uzyskac dostep do nieistniejacego elementu ";
    }
} ;

template <class typ>
class Array : public Container<typ>
{

public:
    class Iterator : public ::Iterator<typ>
    {
    public:
        Iterator(typ *fracptr) : fracptr(fracptr) {}
        Iterator(Array arr) {}
        Iterator& operator++()
        {
            fracptr++;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = fracptr;
            fracptr++;
            return tmp;
        }
        Iterator& operator--()
        {
            fracptr--;
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator tmp = fracptr;
            fracptr--;
            return tmp;
        }
        bool operator==(const ::Iterator<typ>& arg2)
        {
            //cout << "Porownanie z Array\n";
            return fracptr==arg2.get();
        }
        bool operator!=(const ::Iterator<typ>& arg2)
        {
            return fracptr!=arg2.get();
        }
        bool operator<(const Iterator& arg2)
        {
            return fracptr<arg2.get();
        }
        bool operator>(const Iterator& arg2)
        {
            return fracptr>arg2.get();
        }
        typ* operator->()
        {
            return fracptr;
        }
        typ& operator*()
        {
            return *fracptr;
        }
        typ* get() const
        {
            return fracptr;
        }
        Iterator(const Iterator& it)
        {
            fracptr = it.get();
        }
    private:
        typ* fracptr;
        int indeks;
    };

    Array();
    Array(int size);
    ~Array();
    void push_back(typ newfrac);
    Iterator begin();
    Iterator end();
    int size();
    void clear();
    typ& operator[](int i);

protected:
private:
    typ* tab;
    int _size;
};





template <class typ>
Array<typ>::Array()
{
    _size=0;
    try
    {
        tab = new typ[_size];
    }

    catch (std::bad_alloc& ba)
    {
        std::cerr << "Nie moge utowrzyc tablicy. bad_alloc: " << ba.what() << '\n';
        exit(1);
    }
}


template <class typ>
Array<typ>::Array(int size)
{
    _size=size;
    if(size>20)
        throw (int)-1;
    try
    {
        tab = new typ[_size];
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "Nie moge utowrzyc tablicy. bad_alloc: " << ba.what() << '\n';
        exit(1);
    }
}

template <class typ>
Array<typ>::~Array()
{
    if(tab!=NULL)
        delete[](tab);
}

template <class typ>
void Array<typ>::push_back(typ newfrac)
{
    if((_size+1)>20)
        throw too_big_exception();
    _size++;
    typ *tab_new;
    try
    {
        tab_new = new typ[_size];
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "Nie moge dodac elementu do tablicy. bad_alloc: " << ba.what() << '\n';
        exit(1);
    }
    for(int i=0; i<_size-1; i++)
        tab_new[i]=tab[i];
    delete[](tab);
    tab=tab_new;
    tab[_size-1]=newfrac;
}



template <class typ>
int Array<typ>::size()
{
    return _size;
}
template <class typ>
void Array<typ>::clear()
{
    delete(tab);
    tab=NULL;
}
template <class typ>
typ& Array<typ>::operator[] (int i)
{
    if(i<0 || i>=_size)
        throw unknown_element_exception();
    return tab[i];
}
template <class typ>
typename Array<typ>::Iterator Array<typ>::begin()
{
    return Array<typ>::Iterator(tab);
}
template <class typ>
typename Array<typ>::Iterator Array<typ>::end()
{
    return Array<typ>::Iterator(tab+_size);
}




#endif // ARRAY_H
