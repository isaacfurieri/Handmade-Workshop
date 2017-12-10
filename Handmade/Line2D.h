/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates a 2D line segment that determines collisions that may occur with a sphere.
  Other collision objects will be added in at a later stage. The line segment has a starting
  point, which is its position, and an ending point. The length of the line is determined by its
  length variable. There is also a scale variable and a rotation object that both determine the
  scaling size and rotational orientation respectively of the line. The start and end point could
  easily just be fed in to the class as simple world space coordinates, but with rotational
  orientation, there is more flexibility and the line can update itself each time it is moved, 
  rotated or scaled in the client code, instead of always feeding the raw start and end point data
  each time. The rotation object is represented as a Transform object, as passing individual Euler
  angles will cause issues, and in 2D the only actual rotation used is one around the Z axis. It is
  best to create the transform rotation object in the client code before sending it to the Line2D 
  class. Even though the bound represents a 2D object, all member variables are floats because that
  provides more accuracy when calculating the bounds, and will provide better collision precision 
  even if it's just a minute amount. 

- The IsColliding() routine checks if the line segment intersects with a sphere object. For this 
  it uses its distance from the sphere to check for collision. 

- The PointOnLine() routine calculates the point on the line segment that is closest to the 
  position passed into the function. This routine is used internally by the IsColliding()
  function to check if the line segment collides with a sphere. However, this function can also be 
  used externally to calculate the point on the line segment closest to any other point. Separate 
  floats are passed into the function instead of Vector2D objects, otherwise the routine would have
  to be templatized.

- The Update() routine calculates the starting and ending points of the line segment which are then
  used to calculate for collision. In this function is where the rotation object is used, which sets
  the inner right axis so that the end point of the line is correctly determined. The start point
  is the line segment's position. These points will all be in world space and are used in the 
  PointOnLine() routine to calculate the closest point on the line segment to the position specified.
  These values are used for both collision detection as well as for rendering, unlike the other bounds
  that use their calculated values ONLY for collision. The Draw() function uses the Debug Manager to
  draw a simple 2D line segment, because the line will only ever be drawn for debug purposes anyway.
  The line segment will NOT be rendered based on how the matrix is transformed in the calling game
  object code (from within its Draw() routine). Unlike other bounds, the line segment is rendered 
  using its pre-calculated start and end points which are already in world space, therefore if 
  transformations are made in the calling code they will created inaccurate rendering. Therefore when
  rendering the line, make sure transformations are reset beforehand.  

*/

#ifndef LINE_2D_H
#define LINE_2D_H

#include <glm.hpp>
#include "Bound.h"

class Sphere2D;

class Line2D : public Bound
{

public:

	Line2D();
	virtual ~Line2D() {}

public:

	void SetScale(float scale);
	void SetLength(float length);
	void SetRotation(glm::mat4& rotation);

public:

	bool IsColliding(const Sphere2D& secondSphere) const;
	glm::vec2 PointOnLine(float positionX, float positionY) const;

public:

	virtual void Update();
	virtual void Draw();

private:

	float m_scale;
	float m_length;
	
	glm::vec2 m_startPoint;
	glm::vec2 m_endPoint;
	glm::mat4 m_rotation;

};

#endif
