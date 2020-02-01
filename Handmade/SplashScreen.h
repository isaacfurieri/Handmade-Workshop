#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

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
| 'SplashScreen' source files last updated in February 2020							            |
#==============================================================================================*/

#include <string>
#include "glad.h"
#include "GameObject.h"
#include "Sprite.h"

class SplashScreen : public GameObject
{

public:

	enum Fade { FADE_IN, FADE_OUT };

public:

	SplashScreen(const std::string& filename);
	virtual ~SplashScreen() {}

public:

	virtual bool Create();
	virtual void Update(int deltaTime);
	virtual void Draw();
	virtual void Destroy(); 

private:

	Fade m_fade;
	GLfloat m_alpha;
	Sprite m_sprite;
	std::string m_filename;
	glm::ivec2 m_dimension;

};

#endif