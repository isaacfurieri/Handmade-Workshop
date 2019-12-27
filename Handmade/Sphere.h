/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone.It is by no
  means perfect and there is certainly room for improvement in some parts.As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP.Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  ----------------------------------------------------------------------------------------------

- This class encapsulates a 3D sphere that determines collisions that may occur with other spheres
  or boxes as well as line segments and planes in the game world. There is a scale variable that 
  reflects the scale value of the game object that contains this component. This is used in the 
  inner calculations to provide accurate results, so no matter how large the game object is, the 
  bounding sphere will follow along accordingly. Unlike the AABB classes' m_scale and m_dimension 
  variables, in the Sphere3D class they are scalar values instead of vectors. That's because the 
  sphere can only be scaled in one dimension so to speak, and will not be scaled in all axes, turning
  it into an ellipse.
  
- There are five IsColliding() functions, one for checking two spheres for collision, another two
  for checking if a sphere and a AABB or OBB collide, a fourth one for checking intersections with
  a line segment, a fifth one for checking for collisions with a plane. The first one uses its own
  radius and the radius of another sphere within a formula to calculate for collision. The sphere-box
  collision routines makes use of the AABB or OBB's IsColliding() routines, so that code is not
  duplicated. Likewise the sphere-line and sphere-plane collision functions makes use of the Line3D's
  IsColliding() and the Plane3D's IsColliding() routines resepctively.

- The Update() routine calculates the radius based on the dimension of the sphere and its scale
  value, which is then used to calculate for collision. These values are purely for collision
  detection and not used for rendering. The Draw() function uses the Debug Manager to draw a simple
  3D sphere, because the sphere will only ever be drawn for debug purposes anyway. The sphere will
  be rendered based on how the matrix is transformed in the calling game object code (from within
  its Draw() routine). This is why it's best that the Sphere3D component is rendered straight after
  the game object is rendered.

- There is a small snag and that has to do with the order of transformations in the game object's
  Draw() code. If the game object is translated and then scaled, the position value in the sphere's
  IsColliding() routine doesn't need to be scaled. If however the game object is scaled and then
  translated, the position value needs to have scale considered. This is because the position of
  the sphere will be in local space and on a different scaled axis to the rest of the game objects,
  so the positional measurements are different, causing inaccurate calculations. This means that
  when checking for collision inside either of the IsColliding() routines, the positional data will
  differ against the box or sphere object being checked against. By default this class assumes
  translating BEFORE scaling in the game object code. The dimension of the sphere however always
  needs to consider scaling.

- Another thing to consider in the game object code is that rotation may be applied to the game
  object and no matter how much it's rotated, the Sphere3D will always remain the same. That's
  because the centre position and radius are always the same no matter how much it's rotated.

*/

#ifndef SPHERE_H
#define SPHERE_H

#include "AABB.h"

class Sphere
{

public:

	Sphere();
	
public:

	float GetRadius() const;
    float GetRadiusScaled() const;
    const glm::vec3& GetPosition() const;

public:

	void SetScale(float scale);
    void SetRadius(float radius);

public:

	bool IsColliding(const AABB& secondBox) const;
	bool IsColliding(const Sphere& secondSphere) const;

public:

	void Update();
	void Draw();

private:

	float m_scale;
	float m_radius;
    float m_radiusScaled;
    
    glm::vec4 m_color;
    glm::vec3 m_position;

};

#endif