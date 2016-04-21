/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2015

  -----------------------------------------------------------------------------------------------

- This class encapsulates all physics elements of a game object. It is intended to be used as a
  component of a game object which determines how that object should move or rotate based on the
  physical proerties of the object. Generally speaking this class' main aim is to calculate the 
  acceleration, which will be used to either displace or rotate the object correctly. The main
  property variables of the class are of type double or Vector3D<double>, because this offers
  higher precision, which is essential in physics calculations, and the Vec3 objects are used by
  default to avoid a separate 2D and 3D physics class. The measurements make use of the metric 
  system, therefore everything should be measured in grams, meters, seconds, etc.

- The gravitational constant has been altered temporarly because it is already such a small value
  and works better with an added value of 1. (Temporary!!)

- There are two static functions which calculate two types of forces. The GravityForce() routine
  calculates the attraction force between two objects based on their masses and distance from each
  other. The TorqueForce() function calculates the rotational torque force of an object based on
  the object's centre of mass and force contact point. This routine produces a vector which is used
  to determine the rotational axis as well as the torque magnitude. Both functions are static 
  because they are helper routines that need not belong to any physics object instance.

- The various getter/setter functions, which enable interfacing the physics properties, are rolled 
  into one to make setting and getting easier. Most properties use this combo method, except for 
  mass, which only needs to be set as it never changes in the physics class. The combo functionality
  is useful in situations where only one component needs to be set, for example Velocity().Y = 10.
  With these functions in mind, forces can now be easily added to and removed from the object. The
  actual F=ma calculations can be done in the client code and then added to the physics class later.

- The Update() function is the heart of the physics class. It calculates the acceleration for both 
  the movement and rotation of the object and applies that to both velocities to determine the
  displacement and angular rotation of the object. Both displacement and rotational calculations
  are made even though an object may only move or only rotate or both.

*/

#ifndef PHYSICS_H
#define PHYSICS_H

#include "Vector3D.h"

const double GRAVITY = 1.0000000000667;

class Physics
{

public :

	static Vector3D<double> GravityForce(double mass_1, double mass_2, Vector3D<double> distance);
	static Vector3D<double> TorqueForce(Vector3D<double> force, 
		                                Vector3D<double> contactPosition, 
										Vector3D<double> centreOfMass);

public :

	Physics();

public :

	double& Angle();
	double& AngVelocity();

public :

	Vector3D<double>& Force();
	Vector3D<double>& Torque();
	Vector3D<double>& Position();
	Vector3D<double>& Velocity();

public :

	void SetMass(double mass);
	void SetAngMass(double mass);

public :

	void Update();

private :

	double m_mass;
	double m_angle;
	double m_angMass;  	
	double m_angVelocity;
	double m_angAcceleration;

	Vector3D<double> m_force;
	Vector3D<double> m_torque;
	Vector3D<double> m_position;
	Vector3D<double> m_velocity;
	Vector3D<double> m_acceleration;

};

#endif