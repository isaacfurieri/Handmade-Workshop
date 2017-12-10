/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates text objects and derives from the Sprite base class. It will represent 
  a single character or a string of text to be used to display ASCII formatted text. These Text 
  objects use Bitmap Font Builder spritesheets that are specifically laid out so that the ASCII 
  values of the letters and numbers in them correspond to the texture index values of each of the 
  Text object's string characters. This means that a string of text can easily be "cut out" of the 
  spritesheet by using the text's ASCII values. Each character in the string text can be spaced
  out as well.

- There is a local version of Create() because the Text class will generate its own set of VBOs, 
  by first creating some empty ones. This is because we never know at the start how large the buffers
  should be as text is very dynamic. There will be multiple sprites for each word, ie one sprite for
  every letter in the text string. Whereas the Sprite and Animation classes only create a single 
  sprite object that is textured and colored, the Text class creates multiple sprites. 

- The SetText() function does most of the workload in that it fills all the VBOs with the vertices,
  colors and textures based on the current text string. This is ideally only called once to prevent
  cost, but if the text is constantly changing (like a score) then it needs to be called each time.

*/

#ifndef TEXT_H
#define TEXT_H

#include "Sprite.h"

class Text : public Sprite
{

public :

	Text();
	
public :

	void SetText(const std::string& text);
	void SetCharSpace(GLfloat charSpace);
	
public:

	bool Create(const std::string bufferID);

private :
	
	std::string m_text;
	GLfloat m_charSpace;

};

#endif