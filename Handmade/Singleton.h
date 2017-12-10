/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This is a Singleton template class. It will instantiate another class of any type and allow 
  access to it via the Instance() member function. The constructor, copy constructor and 
  assignment operator all need to be private so that this class cannot be individually 
  instantiated.

*/

#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton
{

public:

	static T* Instance();	

private:

	Singleton() {}
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

};

//------------------------------------------------------------------------------------------------------
//template function that will create an instance of any type and return its address
//------------------------------------------------------------------------------------------------------
template <class T> T* Singleton<T>::Instance()
{

	static T* singletonObject = new T();
	return singletonObject;

}

#endif