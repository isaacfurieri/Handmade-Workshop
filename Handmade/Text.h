#pragma once

/*===================================================================#
| 'Text' source files last updated on 19 May 2021                    |
#===================================================================*/

#include "Sprite.h"

//TODO - Refine class such that it follows newer design

class Text : public Sprite
{

public:

	Text();

	void SetText(const std::string& text);
	void SetCharSpace(GLfloat charSpace);

	bool Create(const std::string bufferID);

private:

	std::string m_text;
	GLfloat m_charSpace;

};