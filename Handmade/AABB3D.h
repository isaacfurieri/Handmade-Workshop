/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates a 3D axis-aligned bounding box that determines collisions that may occur
  with other boxes on the same axes, oriented bounding boxes and spheres. There is a scale variable
  that reflects the scale value of the game object that contains this component. This is used in the
  inner calculations to provide accurate results, so no matter how large the game object is, the
  bounding box will follow along accordingly. 

- The GetScale() and GetDimension() routines are there mainly for being called from within the OBB
  class' IsColliding() function, more specifically, the one that checks for AABB and OBB collision.
  Other than for that reason they don't really serve any other purpose.

- There are three IsColliding() functions, one for checking two AABB boxes for intersection, and
  for this the routine uses a minimum and maximum X, Y and Z value within a formula to calculate for
  collision. The other IsColliding() function checks for intersection between a AABB box and a
  sphere. For this it uses its half dimension in X, Y and Z, and its distance from the sphere to
  calculate for intersections. The last IsColliding() routine checks for AABB and OBB intersections.
  For this it makes use of the OBB's IsColliding() routine, so that code is not duplicated.

- The PointOnBox() routine calculates the point on the box edge that is closest to the position
  passed into the function. This routine is used internally by the AABB-Sphere IsColliding()
  function to check if the box collides with a sphere. However, this function can also be used
  externally to calculate the point on the box edge closest to any other point. Separate floats
  are passed into the function instead of Vector3D objects, otherwise the routine would have to be
  templatized.

- The Update() routine calculates the min, max and half dimension values of the bounding box which
  are then used to calculate for collision. The position and dimension of the bound are used to
  calculate these min and max values, and they exist in world space. These values are purely for
  collision detection and not used for rendering. The Draw() function uses the Debug Manager to
  draw a simple 3D box, because the AABB will only ever be drawn for debug purposes anyway. The
  box will be rendered based on how the matrix is transformed in the calling game object code
  (from within its Draw() routine). This is why it's best that the AABB component is rendered
  straight after the game object is rendered.

- There is a small snag and that has to do with the order of transformations in the game object's
  Draw() code. If the game object is translated and then scaled, the position value in the AABB's
  Update() routine doesn't need to be scaled. If however the game object is scaled and then
  translated, the position value needs to have scale considered. This is because the position of
  the AABB will be in local space and on a different scaled axis to the rest of the game objects,
  so the positional measurements are different, causing inaccurate calculations. This means that
  when checking for collision inside either of the IsColliding() routines, the min, max and position
  data will differ against the box or sphere object being checked against. By default this class
  assumes translating BEFORE scaling in the game object code. The dimension of the AABB however
  always needs to consider scaling.

- Another thing to consider in the game object code is that rotation may be applied to the game
  object but then the modelview matrix needs to be reset before rendering the bound, so that the
  AABB doesn't follow suit and rotate as well. AABBs are not designed for rotations, because they
  need to remain on the normal axis, as they are axis aligned. Rather consider using OBBs instead.

*/

#ifndef AABB_3D_H
#define AABB_3D_H

#include <glm.hpp>
#include "Bound.h"

class OBB3D;
class Sphere3D;

class AABB3D : public Bound
{

public :

	AABB3D();
	virtual ~AABB3D()  {}

public:

	glm::vec3 GetScale()     const;
	glm::vec3 GetDimension() const;

public:

	void SetScale(float x, float y, float z);
	void SetDimension(float width, float height, float depth);

public:

	bool IsColliding(const OBB3D& secondBox) const;
	bool IsColliding(const AABB3D& secondBox) const;
	bool IsColliding(const Sphere3D& secondSphere) const;
	glm::vec3 PointOnBox(float positionX, float positionY, float positionZ) const;

public:

	virtual void Update();
	virtual void Draw();

private:

	glm::vec3 m_min;
	glm::vec3 m_max;
	glm::vec3 m_scale;
	glm::vec3 m_dimension;
	glm::vec3 m_halfDimension;

};

#endif