#ifndef MYLIST_H
#define MYLIST_H

#include "Container.h"
#include <exception>
#include "Iterator.h"
class before_first_exception : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Probowano ustawic iterator przed pierwszy element listy";
	}
} ;
class after_last_exception : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Probowano ustawic iterator za ostatni element listy";
	}
} ;
template <class typ>
class MyList : public Container<typ>
{
public:
	class Node
	{
	public:
		Node();
		~Node();
		Node* getPrev();
		Node* getNext();
		typ* getVal();
		void setPrev(Node* newPrev);
		void setNext(Node* newNext);
		void setVal(typ* newVal);
		void setList(MyList<typ> *lst);
		void remove(bool del);

	private:
		Node *next;
		Node *prev;
		typ *val;
		MyList<typ> *lista;
	};
	class Iterator : public ::Iterator<typ>
	{
	public:
		Iterator(Node *elnode) : elnode(elnode)
		{
			if(elnode==NULL)
				elptr=NULL;
			else elptr=elnode->getVal();
		}
		Iterator& operator++()
		{
			if((elptr==NULL) || (elnode->getNext()==NULL))
				throw after_last_exception();
			elnode=elnode->getNext();
			elptr=(elnode->getVal());
			return *this;
		}
		Iterator operator++(int)
		{
			//if((elptr==NULL) || (elnode->getNext()->getVal()==NULL))
			if((elptr==NULL) || (elnode->getNext()==NULL))
				throw after_last_exception();
			Iterator tmp = elnode;
			elnode=elnode->getNext();
			elptr=(elnode->getVal());
			return tmp;
		}
		Iterator& operator--()
		{
			if(elnode->getPrev()==NULL)
				throw before_first_exception();
			elnode=elnode->getPrev();
			elptr=elnode->getVal();
			return *this;
		}
		Iterator operator--(int)
		{
			if(elnode->getPrev()==NULL)
				throw before_first_exception();
			Iterator tmp = elnode;
			elnode=elnode->getPrev();
			elptr=elnode->getVal();
			return tmp;
		}
		bool operator==(const ::Iterator<typ>& arg2)
		{
			return elptr==arg2.get();
		}
		bool operator!=(const ::Iterator<typ>& arg2)
		{
			return elptr!=arg2.get();
		}
		typ* operator->()
		{
			return (elnode->getVal());
		}
		typ& operator*()
		{
			return *elnode->getVal();
		}
		Node* getnode() const
		{
			return elnode;
		}
		typ* get() const
		{
			return elptr;
		}
		Iterator(const Iterator& it)
		{
			elnode = it.getnode();
		}


	private:
		Node* elnode;
		typ *elptr;
	};

	class ReverseIterator : public ::Iterator<typ>
	{
	public:
		ReverseIterator(Node *elnode) : elnode(elnode)
		{
			if (elnode == NULL)
				elptr = NULL;
			else elptr = elnode->getVal();
		}
		ReverseIterator& operator--()
		{
			if ((elptr == NULL) || (elnode->getNext() == NULL))
				throw after_last_exception();
			elnode = elnode->getNext();
			elptr = (elnode->getVal());
			return *this;
		}
		ReverseIterator operator--(int)
		{
			//if((elptr==NULL) || (elnode->getNext()->getVal()==NULL))
			if ((elptr == NULL) || (elnode->getNext() == NULL))
				throw after_last_exception();
			ReverseIterator tmp = elnode;
			elnode = elnode->getNext();
			elptr = (elnode->getVal());
			return tmp;
		}
		ReverseIterator& operator++()
		{
			if (elnode->getPrev() == NULL)
				throw before_first_exception();
			elnode = elnode->getPrev();
			elptr = elnode->getVal();
			return *this;
		}
		ReverseIterator operator++(int)
		{
			if (elnode->getPrev() == NULL)
				throw before_first_exception();
			ReverseIterator tmp = elnode;
			elnode = elnode->getPrev();
			elptr = elnode->getVal();
			return tmp;
		}
		bool operator==(const ::Iterator<typ>& arg2)
		{
			return elptr == arg2.get();
		}
		bool operator!=(const ::Iterator<typ>& arg2)
		{
			return elptr != arg2.get();
		}
		typ* operator->()
		{
			return (elnode->getVal());
		}
		typ& operator*()
		{
			return *elnode->getVal();
		}
		Node* getnode() const
		{
			return elnode;
		}
		typ* get() const
		{
			return elptr;
		}
		ReverseIterator(const ReverseIterator& it)
		{
			elnode = it.getnode();
		}


	private:
		Node* elnode;
		typ *elptr;
	};

	MyList();
	~MyList();
	typ* push_back(typ frac);
	typ* push_back(typ *frac);
	Iterator begin();
	ReverseIterator rbegin();
	Iterator end();
	ReverseIterator rend();
	int size() const;
	Node *front;
	Node *back;
	Node *list_end;
	Node *list_start;

protected:
private:

	//Fraction *elptr;
};

template <class typ>
MyList<typ>::MyList()
{
	list_end = new MyList<typ>::Node();
	//list_end->setVal(NULL);
	list_end->setNext(NULL);
	list_end->setNext(NULL);
	list_start = new MyList<typ>::Node();
	list_start->setNext(NULL);
	list_start->setNext(NULL);
	front = back = NULL;// elptr =NULL;

	this->_size = 0;
}

template <class typ>
MyList<typ>::~MyList()
{
	while((front!=NULL) && front->getNext()!=NULL)
	{
		MyList<typ>::Node* tmp = front->getNext();
		//delete front->getVal();
		delete front;
		front = tmp;
	}
	delete list_end;
	delete list_start;
}

template <class typ>
typ* MyList<typ>::push_back(typ frac)
{
	//std::cout << &frac << std::endl;
	MyList<typ>::Node *p = new MyList<typ>::Node();
	typ *tmpfrac = new typ(frac);
	p->setVal(tmpfrac);
	if(back) back->setNext(p);
	p->setNext(list_end);
	p->setPrev(back);
	p->setList(this);
	back = p;
	list_end->setPrev(back);
	//elptr = *(back->getVal());
	if (!front)  
	{
		front = back;
		front->setPrev(list_start);
		list_start->setNext(front);
	}
	this->_size++;
	return tmpfrac;
}

template <class typ>
typ* MyList<typ>::push_back(typ *frac)
{
	MyList<typ>::Node *p = new MyList<typ>::Node();
	typ *tmpfrac = frac;
	p->setVal(tmpfrac);
	if (back) back->setNext(p);
	p->setNext(list_end);
	p->setPrev(back);
	p->setList(this);
	back = p;
	list_end->setPrev(back);
	//elptr = *(back->getVal());
	if (!front)
	{
		front = back;
		front->setPrev(list_start);
		list_start->setNext(front);
	}
	this->_size++;
	return tmpfrac;
}

template <class typ>
typename MyList<typ>::Iterator MyList<typ>::begin()
{
	return Iterator(front);
}
template <class typ>
typename MyList<typ>::ReverseIterator MyList<typ>::rbegin()
{
	return ReverseIterator(back);
}

template <class typ>
typename MyList<typ>::Iterator MyList<typ>::end()
{
	return Iterator(list_end);
}
template <class typ>
typename MyList<typ>::ReverseIterator MyList<typ>::rend()
{
	return ReverseIterator(list_start);
}

template <class typ>
int MyList<typ>::size() const
{
	return this->_size;
}

template <class typ>
MyList<typ>::Node::Node()
{
	prev = next = NULL;
	val = NULL;
}

template <class typ>
MyList<typ>::Node::~Node()
{
	delete(val);
}

template <class typ>
typename MyList<typ>::Node* MyList<typ>::Node::getPrev()
{
	return prev;
}

template <class typ>
typename MyList<typ>::Node* MyList<typ>::Node::getNext()
{
	return next;
}

template <class typ>
typ* MyList<typ>::Node::getVal()
{
	return val;
}

template <class typ>
typename void MyList<typ>::Node::setPrev(typename MyList<typ>::Node *newPrev)
{
	prev = newPrev;
}
template <class typ>
typename void MyList<typ>::Node::setNext(typename MyList<typ>::Node *newNext)
{
	next = newNext;
	//std::cout << "Tu " << std::endl;
}

template <class typ>
void MyList<typ>::Node::setVal(typ* newVal)
{
	val = newVal;
}

template <class typ>
void MyList<typ>::Node::remove(bool del)
{
	//_size--;
	Node *tmp;
	tmp = this;
	if (prev!=lista->list_start)
	{
		prev->setNext(next);
	}
	else
	{
		prev = lista->list_start;
		lista->list_start->setNext(next);
		lista->front = next;
		
	}
	
	if (next!=lista->list_end)
	{
		next->setPrev(prev);
		//std::cout << "Tu " << std::endl;
	}
	else
	{
		next = lista->list_end;
		lista->list_end->setPrev(prev);
		lista->back = prev;
	}
	if (del)
		delete (tmp);
	else
	{
		tmp->setVal(NULL);
		delete(tmp);
	}
	//lista->_size--;
}

template <class typ>
void MyList<typ>::Node::setList(MyList<typ> *lst)
{
	lista = lst;
}

#endif // MYLIST_H
