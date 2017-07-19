/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates a game object that will exist in the game world and represent any type
  of object like a player, enemy, weapon, inventory item, etc. It is designed around the same 
  principle as Unity's game objects and will be instantiated in the client code at runtime from 
  within the game specific code. It consists of three main flags, m_isAlive, m_isActive and 
  m_isVisible, to signify if the object is exisiting in memory, being used in the game world and 
  hidden or not from the game world, respectively. Each game object also has a string tag to 
  identify it amongst other objects, and a priority value for 2D game worlds without a Z-axis, 
  so that game objects may be drawn in a specific order to give the illusion of depth. Each game
  object automatically has a matrix to represent its transformation in terms of position, rotation
  and scale. For more flexible rotations, a Quaternion component is also present. All game objects
  need to be instantiated as sub-classes of this abstract base class.

- There are a few static variables and functions which were added to allow global access to the
  game object's main properties, that belong to the game object. Of these is the model matrix, 
  because we only need one matrix to represent the object's transformation. This works similar to
  the way the old fixed function OpenGL controlled model matrices. The other variable is the ID
  that monitors the vertex shader's model matrix uniform, to which the model matrix is passed to.
  The static functions allow for the model matrix to be reset to the identity, transformed 
  accordingly and passed to the vertex shader. 
  There is also a PushMatrix() and PopMatrix() routine, which works similar to the old fixed 
  function OpenGL, that allows the global model matrix to be temporarily "bookmarked" so that
  temporary transformations may be applied (push) afterwhich we can revert back to the older 
  transformations (pop). This feature works nicely with parent and child transformations.		

- The getters and setters are split into normal ones and combo variants. The combo variants, 
  IsAlive(), IsActive() and IsVisible() return references to the respective variables because these
  flag variables may be used frequently and getting and setting them individually may become 
  inconvenient.

- Each game object has a Update() and Draw() function which will be overriden in the sub-class, 
  where the actual main functionality of that object will exist. Generally the Update() routine
  is there for the updating of all position, rotation and scale values, alongside others. The Draw()
  function is intended for all transformations to be applied to the internal model matrix, as well
  as components and other objects being drawn.

*/

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <string>
#include <vector>
#include "Quaternion.h"

class GameObject 
{

public:

	static void SetIdentity();
	static void PushMatrix();
	static void PopMatrix();
	static void ApplyMatrix();
	static void SetModelUniformID(std::string uniformID);
	static void MultiplyMatrix(Quaternion& quaternion);
	static void MultiplyMatrix(glm::mat4& transformation);

private:

	static GLuint s_modelUniformID;
	static std::vector<glm::mat4> s_modelMatrix;

public :

	GameObject();
	virtual ~GameObject() = 0 {}

public :

	bool& IsAlive();
	bool& IsActive();
	bool& IsVisible();

public :

	std::string GetTag();
	unsigned int GetPriority();
	void SetTag(std::string tag);
	void SetPriority(unsigned int priority);
	
public :

	virtual void Update() = 0;
	virtual bool Draw() = 0;

protected :

	bool m_isAlive;
	bool m_isActive;
	bool m_isVisible;

	std::string m_tag;
	unsigned int m_priority;

	glm::mat4 m_transform;
	Quaternion m_rotation;

};

#endif