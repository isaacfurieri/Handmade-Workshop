/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates a 3D plane that determines collisions that may occur with a sphere.
  Other collision objects will be added in at a later stage. The plane is infinitely long, so
  therefore it has no starting or ending point, unlike the Line Segment. Similarily it also has
  no length or scale values, it simply exists and stretches to infinity in length and width from
  its centre position. There is however a rotation object that determines the rotational orientation
  of the plane surface. The plane points could easily just be fed in to the class as simple world space
  coordinates in order to create the plane, but with rotational orientation, there is more flexibility
  and the plane can update itself each time it is moved or rotated in the client code, instead of
  always feeding the raw point data each time. The rotation object is represented as a Quaternion 
  object, to better handle 3D rotations. It is best to create the quaternion rotation in the client
  code before sending it to the Plane3D class. There is also a m_size variable that is used for visual
  purposes only, and is used to determine the width and depth values for when the 3D cube that represents
  this plane is drawn.

- Three enum values exist to be used when determining what side of the plane a particular point is on.
  By default when looking at the plane as a horizontal flat surface, everything above it is the positive
  side and everything below is negative. The plane's normal also points in the direction of the positive
  side.

- The IsColliding() routine checks if the plane intersects with a sphere object. For this it uses
  its distance from the origin and the sphere's position to check for collision. The SideOfPlane()
  routine determines what side of the plane the position passed into the function is on. This function
  makes use of the enum values declared within the class declaration.

- The Update() routine calculates the normal of the plane, and it is in this function where the 
  rotation object is used, which sets the inner right and forward axis accordingly, so that the normal
  can be determined using the cross product of the two. This function also works out the distance the 
  plane is from the origin, using a dot product formula. The normal and distance values are used purely
  for collision detection and not used for rendering. The Draw() function uses the Debug Manager to draw
  a simple 3D cube without any height, because the plane will only ever be drawn for debug purposes 
  anyway. Unlike the Plane2D class, this plane will be rendered based on how the matrix is transformed
  in the calling game object code (from within its Draw() routine). It does not use any pre-calculated
  world space plane points to render, but instead a basic 3D cube which requires that the transformations
  are set in the client code accordingly.

- One thing to consider in the Draw() routine is that it uses the size variable to render the cube. By 
  definition a plane is infinitely long and infinitly wide, but for visual purposes it may be difficult
  to see how the plane is oriented or positioned, therefore making it a certain size might help. Another 
  issue is that because the height is set to 0, the top and bottom cube faces will touch, causing a
  wierd pixel clashing to occur which makes a "flashing" appearance. To rectify this, the height is set
  to a tiny amount just larger than 0. <TBA>

*/

#ifndef PLANE_3D_H
#define PLANE_3D_H

#include <glm.hpp>
#include "Bound.h"
#include "Quaternion.h"

class Sphere3D;

class Plane3D : public Bound
{

public:

	enum PlaneSide { POSITIVE_SIDE, NEGATIVE_SIDE, ON_PLANE };

public:

	Plane3D();
	virtual ~Plane3D() {}

public:

	void SetSize(float size);
	void SetRotation(Quaternion rotation);

public:

	bool IsColliding(const Sphere3D& secondSphere) const;
	PlaneSide SideOfPlane(float positionX, float positionY, float positionZ) const;

public:

	virtual void Update();
	virtual void Draw();

private:

	float m_size;
	float m_sideOfPlane;
	float m_distanceFromOrigin;

	Quaternion m_rotation;
	glm::vec3 m_normal;
	
};

#endif