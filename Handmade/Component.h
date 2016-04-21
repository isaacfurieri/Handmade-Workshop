/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2016

  -----------------------------------------------------------------------------------------------

- The components act as a middlepoint between the managers and the client code objects. The managers
  could be directly accessed, but the components act as a organized way of linking all the data.

-

*/

#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{

public :

	Component() {}
	virtual ~Component() = 0 {}

};

#endif