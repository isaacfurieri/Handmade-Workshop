/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2016

  -----------------------------------------------------------------------------------------------

- This class encapsulates text objects and derives from the Sprite base class. It will represent 
  a single character or a string of text to be used to display ASCII formatted text. These Text 
  objects use Bitmap Font Builder spritesheets that are specifically laid out so that the ASCII 
  values of the letters and numbers in them correspond to the texture index values of each of the 
  Text object's string characters. This means that a string of text can easily be "cut out" of the 
  spritesheet by using the text's ASCII values. Each character in the string text can be spaced
  out as well.

- The setter functions will set the specific properties of the Text object. The SetShaderUniform()
  function is there to be able to link the shader modelview uniform variable with the global 
  modelview matrix that will be sent to the shader in the Draw() function for each letter in the 
  text string. This is because for each letter, there is a translation to the left. No matter how
  the text is transformed in the client code, the letters always read from left to right.

- Because the texture index value is calculated differently here than in the Sprite base class, the
  Draw() function is overriden.

*/

#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "Sprite.h"
#include "Transform.h"

class Text : public Sprite
{

public :

	Text();
	virtual ~Text() {}

public :

	void SetText(const std::string& text);
	void SetCharSpace(GLfloat charSpace);
	void SetShaderUniform(const std::string& uniform);
	
public :

	virtual void Draw();

private :
	
	GLfloat m_charSpace;

	std::string m_text;
	std::string m_uniform;

	Transform m_translation;
		
};

#endif