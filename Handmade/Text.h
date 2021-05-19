#ifndef TEXT_H
#define TEXT_H

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
| 'Text' source files last updated in December 2019					    			            |
#==============================================================================================*/

#include "Sprite.h"

//TODO - Refine class such that it follows newer design

class Text : public Sprite
{

public:

	Text();
	
public:

	void SetText(const std::string& text);
	void SetCharSpace(GLfloat charSpace);
	
public:

	bool Create(const std::string bufferID);

private:
	
	std::string m_text;
	GLfloat m_charSpace;

};

#endif