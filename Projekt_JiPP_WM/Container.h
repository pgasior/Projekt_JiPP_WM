#ifndef CONTAINER_H
#define CONTAINER_H
#include <exception>

class too_big_exception : public std::exception
{
  virtual const char* what() const throw()
  {
	return "Probowano dodac wiecej niz 20 elementow";
  }
} ;
template <class typ>
class Container
{
public:
		virtual typ* push_back(typ) = 0;
		virtual int size() const = 0;
	protected:
		int _size;
	private:
};

#endif // CONTAINER_H
