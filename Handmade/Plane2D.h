/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : April 2016

  -----------------------------------------------------------------------------------------------

- This class encapsulates a 2D plane that determines collisions that may occur with a sphere.
  Other collision objects will be added in at a later stage. The plane is infinitely long, so
  therefore it has no starting or ending point, unlike the Line Segment. Similarily it also has
  no length or scale values, it simply exists and stretches to infinity in both directions from
  its centre position. There is however a rotation object that determines the rotational orientation
  of the plane line. The plane points could easily just be fed in to the class as simple world space
  coordinates in order to create the plane, but with rotational orientation, there is more flexibility
  and the plane can update itself each time it is moved or rotated in the client code, instead of 
  always feeding the raw point data each time. The rotation object is represented as a Transform 
  object, as passing individual Euler angles will cause issues, and in 2D the only actual rotation
  used is one around the Z axis. It is best to create the transform rotation object in the client code
  before sending it to the Plane2D class. Even though the bound represents a 2D object, all member
  variables are floats because that provides more accuracy when calculating the bounds, and will 
  provide better collision precision even if it's just a minute amount.

- Three enum values exist to be used when determining what side of the plane a particular point is on.
  By default when looking at the plane as a horizontal line, everything above it is the positive side
  and everything below is negative. The plane's normal also points in the direction of the positive 
  side.

- The IsColliding() routine checks if the plane intersects with a sphere object. For this it uses 
  its distance from the origin and the sphere's position to check for collision. The SideOfPlane()
  routine determines what side of the plane the position passed into the function is on. This function
  makes use of the enum values declared within the class declaration.

- The Update() routine firstly calculates two of the plane points which are only used for rendering
  purposes in the Draw() function. In this function is where the rotation object is used, which sets
  the inner right axis so that the two plane points are correctly determined, based on the plane's
  centre position. This function also works out the plane's normal, which is nothing more than a 
  vector perpendicular to the rotated axis, and the distance the plane is from the origin, using a
  dot product formula. The normal and distance values are used purely for collision detection and not
  used for rendering. The Draw() function uses the Debug Manager to draw a simple 2D line segment, 
  because the plane will only ever be drawn for debug purposes anyway. The plane will NOT be rendered
  based on how the matrix is transformed in the calling game object code (from within its Draw() 
  routine). Unlike other bounds, the plane is rendered using its pre-calculated plane points which are
  already in world space, therefore if transformations are made in the calling code they will created
  inaccurate rendering. Therefore when rendering the plane, make sure transformations are reset 
  beforehand.

- One thing to consider in the Draw() routine is that it uses two defined points to render a straight
  line. By definition a plane is infinitely long, but for visual purposes two end points are needed
  to render something. The points are calculated so that they stretch far out from the centre position,
  in order for the plane to appear infinitely long.

*/

#ifndef PLANE_2D_H
#define PLANE_2D_H

#include "Bound.h"
#include "Transform.h"
#include "Vector2D.h"

class Sphere2D;

class Plane2D : public Bound
{

public:

	enum PlaneSide { POSITIVE_SIDE, NEGATIVE_SIDE, ON_PLANE };

public:

	Plane2D();
	virtual ~Plane2D() {}

public:

	void SetRotation(Transform rotation);

public:

	bool IsColliding(const Sphere2D& secondSphere) const;
	PlaneSide SideOfPlane(float positionX, float positionY) const;

public:

	virtual void Update();
	virtual void Draw();

private:

	float m_sideOfPlane;
	float m_distanceFromOrigin;
	
	Transform m_rotation;

	Vector2D<float> m_normal;
	Vector2D<float> m_point_1;
	Vector2D<float> m_point_2;

};

#endif