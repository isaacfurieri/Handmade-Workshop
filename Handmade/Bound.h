/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates bounding shapes that are used to determine collision. They act as 
  components that are designed to be placed inside a game object, in much the same way as how
  Unity uses their game objects and components. This is an abstract base class, from which all
  individual bounds should be derived and each one should override the Update() and Draw() functions.
  Externally these functions must be called from within the game object's Update() and Draw() 
  routines respectively. The main member variables here are m_position and m_color which are used
  to determine where the bound is in the game world and what color it is, respectively. The idea is
  that each individual game object will store their own position and send that data to the bound 
  from within its Update() routine. The bound will then use this data to calculate collision. 
  Only position is needed here because it is the base variable that is used for all derived bound
  classes, ie all bounds need to have some form of position no matter what. Position is only used
  for collision calculations, not for visuals. 

- Visually speaking, each bound should be rendered straight after the game object is rendered in 
  the main code. This will ensure that the bound follows suit as to how it should appear and will
  take all game object transformations into account. 

- The position variable is a float because this offers more flexibility, as integers are too 
  restrictive and the bound will represent 2D and 3D worlds, because both 2D and 3D bound classes will
  be derived from this bound base class. This is also why we need to use a Vector3D class so that 2D 
  and 3D bounds may be derived from this class.

- The SetPosition() function uses explicit x, y and z values instead of passing vector objects otherwise
  some form of templatizing the vectors would need to be done. We could have added a getter/setter combo
  for the position variable but that drops the const qualifier and causes const qualification errors 
  elsewhere in the derived bound class code. The code in the derived bound classes require that the 
  GetPosition() routine remains a constant function!

*/

#ifndef BOUND_H
#define BOUND_H

#include <glew.h>
#include <glm.hpp>

class Bound 
{

public :

	Bound()           {}
	virtual ~Bound()  {}

public :

	glm::vec3 GetPosition() const;

public :

	void SetPosition(GLfloat x, GLfloat y, GLfloat z = 0);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

public :

	virtual void Update() = 0;
	virtual void Draw()	  = 0;

protected :

	glm::vec4 m_color;
	glm::vec3 m_position;	

};

#endif