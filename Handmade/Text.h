/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates text objects and derives from the Sprite base class. It will represent 
  a single character or a string of text to be used to display ASCII formatted text. These Text 
  objects use Bitmap Font Builder spritesheets that are specifically laid out so that the ASCII 
  values of the letters and numbers in them correspond to the texture index values of each of the 
  Text object's string characters. This means that a string of text can easily be "cut out" of the 
  spritesheet by using the text's ASCII values. Each character in the string text can be spaced
  out as well.

- Because the texture index value is calculated differently here than in the Sprite base class, the
  Draw() function is overriden. Furthermore the Text class loops through all letters in the text
  string, therefore an inner loop is used in the Draw() routine.

- There is a local version of CreateVertices() because the Text class will generate its own set of
  vertices, as there will be multiple sprites for each word, ie one sprite for every letter in the
  text string. Whereas the Sprite and Animation classes only create a single sprite object that is
  textured and colored, the Text class creates multiple sprites. The CreateVertices() function will
  be called multiple times from within the Draw() routine, once for each character in the string 
  text. 

*/

#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "Sprite.h"

class Text : public Sprite
{

public :

	Text();
	virtual ~Text() {}

public :

	void SetText(const std::string& text);
	void SetCharSpace(float charSpace);
	
public :

	virtual void Draw();

private :

	void CreateVertices(int characterIndex);
	
private :
	
	std::string m_text;
	float m_charSpace;

};

#endif