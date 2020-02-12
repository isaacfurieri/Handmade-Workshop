#ifndef ELEMENT_H
#define ELEMENT_H

/*==============================================================================================#
|                                                                                               |
| All code has been written by Karsten Vermeulen as part of the 'Handmade' game engine, for the |
| purposes of educating other fellow programmers, programming students and anyone else wishing  |
| to learn about game development, C++ and OOP. The engine, class design and overall structure  |
| is by no means perfect and there is certainly room for improvement. Feel free to use, copy,   |
| break, update and do as you wish with this code - it is there, free, for all!                 |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|																								|
| If you like 'Handmade', and wish to show your support, if you have any questions about the    |
| project, or if you just want to reach out, please find me on the following channels:          |
|																						        |
| Web: http://www.karstenvermeulen.com														    |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'Element' source files last updated in February 2020								            |
#==============================================================================================*/

#include "Buffer.h"
#include "GameObject.h"

class Element : public GameObject
{

public:

	Element() {}

public:

	virtual bool Create();
	virtual void Update(int deltaTime) {}
	virtual void Draw()                {}
	
	void DrawVertex(GLfloat x, GLfloat y, GLfloat z,
		            GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f,
		            GLfloat pointSize = 10.0f);

	void DrawVector(GLfloat x, GLfloat y, GLfloat z,
					GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f,
					GLfloat lineWidth = 2.0f);

	void DrawLineSegment(GLfloat x1, GLfloat y1, GLfloat z1,
						 GLfloat x2, GLfloat y2, GLfloat z2,
						 GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f,
						 GLfloat lineWidth = 2.0f);

	virtual void Destroy();

private:

	Buffer m_buffer;

};

#endif