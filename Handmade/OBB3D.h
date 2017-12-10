/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates a 3D oriented bounding box that determines collisions that may occur with
  other oriented bounding boxes and boxes on the same axes, or AABBs. It also checks for collisions
  with sphere objects. There is a scale variable that reflects the scale value of the game object 
  that contains this component. This is used in the
  inner calculations to provide accurate results, so no matter how large the game object is, the
  bounding box will follow along accordingly. There is also a rotation object that is used to
  work out how the OBB's inner up, right and forward axis will be rotated. This rotation object is
  represented as a Quaternion object, to better handle 3D rotations. It is best to create the 
  quaternion rotation in the client code before sending it to the OBB class. 

- There are three IsColliding() functions, one for checking two OBB boxes for intersection, another
  to check for collisions between a OBB and AABB box, and a third to check for collisions between a
  OBB and a sphere. Both the OBB-OBB and OBB-AABB routines will use the inner private IsColliding()
  function that does the actual work. This is to prevent duplicate code, because checking OBB-OBB 
  and OBB-AABB use almost the same technique, as AABBs are merely OBBs without rotations. The private
  IsColliding() function is sent an array of two OBBs from the other two IsColliding() functions, 
  and will loop through these two boxes, and project all sixteen corners onto all six axes 
  (plus the extra edge axes), using the corners and the up, right and forward axes previously
  calculated. As soon as a separating axis is found, the function's inner main loop will break and
  return false immediately. The third IsColliding() function checks for intersection between a OBB 
  box and a sphere. For this it uses its half dimension in X, Y and Z, its rotated right, up and 
  forward axes, and its distance from the sphere to calculate for intersections.

- The PointOnBox() routine calculates the point on the box edge that is closest to the position
  passed into the function. This routine is used internally by the OBB-Sphere IsColliding()
  function to check if the box collides with a sphere. However, this function can also be used
  externally to calculate the point on the box edge closest to any other point. Separate floats
  are passed into the function instead of Vector3D objects, otherwise the routine would have to be
  templatized.

- The Update() routine calculates all eight corners of the bounding box which are then used to
  calculate for collision. In this function is where the rotation object is used, which sets the
  inner up, right and forward axis so that the corners of the bound are correctly determined. These
  corners will all be in world space and are used to project onto the axes and calculate collisions.
  The rotated axes are also used for projecting the corners onto. These values are purely for collision
  detection and not used for rendering. The Draw() function uses the Debug Manager to draw a simple
  3D box, because the OBB will only ever be drawn for debug purposes anyway. The box will be rendered
  based on how the matrix is transformed in the calling game object code (from within its Draw() 
  routine). This is why it's best that the OBB component is rendered straight after the game object
  is rendered.

- There is a small snag and that has to do with the order of transformations in the game object's
  Draw() code. If the game object is translated and then scaled, the position value in the OBB's
  Update() routine doesn't need to be scaled. If however the game object is scaled and then
  translated, the position value needs to have scale considered. This is because the position of
  the OBB will be in local space and on a different scaled axis to the rest of the game objects,
  so the positional measurements are different, causing inaccurate calculations. This means that
  when checking for collision inside either of the IsColliding() routines, the box corners and
  the position data will differ against the box object being checked against. By default this class
  assumes translating BEFORE scaling in the game object code. The dimension of the OBB however
  always needs to consider scaling.

- Another thing to consider in the game object code is that rotation may be applied to the game
  object and this rotation should be the same rotation as the rotation value sent to the OBB. This
  ensures that the visual rotation is exactly the same as the inner calculated rotation.

*/

#ifndef OBB_3D_H
#define OBB_3D_H

#include <glm.hpp>
#include "AABB3D.h"
#include "Bound.h"
#include "Quaternion.h"

class Sphere3D;

class OBB3D : public Bound
{

public:

	OBB3D();
	virtual ~OBB3D()  {}

public:

	void SetRotation(Quaternion rotation);
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

	bool IsColliding(const OBB3D* tempBoxes) const;

private:

	glm::vec3 m_scale;
	glm::vec3 m_dimension;
	glm::vec3 m_upAxis;
	glm::vec3 m_rightAxis;
	glm::vec3 m_forwardAxis;
	glm::vec3 m_corners[8];

	Quaternion m_rotation;

};

#endif