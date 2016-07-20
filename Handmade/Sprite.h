/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : July 2016

  -----------------------------------------------------------------------------------------------

- This class encapsulates sprite objects and uses a texture ID value to represent the actual 
  sprite image. The image can be a single image, or a spritesheet of multiple images, which is
  great for animations. The main aim of this class is to be able to assign single images or a 
  specific spritesheet cell image to be used. The Sprite class is a base class from which the 
  Animation and Text classes derive from. 

- The enumerated type is there to set the sprite type to either static or dynamic. The static
  type is a sprite that gets set and created once and stays the same thereafter. The other type
  is for sprites that will change in terms of vertices, colors and textures. The Animation and 
  Text subclasses are generally dynamic as their texture values will no doubt change all the time.
  The m_isSpriteCreated flag variable is there to be set if a static sprite has been created 
  already.

- One of the most important member variables is the texture index variable. It is the index value
  of the actual sprite cell of a sprite sheet, if the texture image has multiple images within. 
  If the texture image is singular, the texture index is 0 by default. The texture index is zero 
  based and is a whole number value counting from top left and going right and down the spritesheet. 
  It is calculated differently in the base class to the subsequent sub-classes. If for any reason
  incorrect texture index values are used, for example if an incorrect texture cell is set, going
  beyond its maximum value, the textures are capable of wrapping, and will begin again at the
  beginning.

- There is one getter/setter combo function that returns a reference to the sprite's color property.
  The reason it's a reference is because this makes it easier in the client code to quickly set the 
  color's alpha value or separate color component, ie the R, G, B and A values. To get and set the
  sprite's color variable separately will mean creating color objects externally and sending them
  to the sprite, which may appear to be a little inconvenient.

- The setter functions will set the specific properties of the sprite. The SetShaderAttribute()
  function is there to be able to link the shader attribute variables with the sprite data via the
  internal Buffer object. The SetBufferID() function is able to link the sprite's internal buffer
  with the correct vertex, color and texture VBO. The SetTextureID() routine is used to assign an 
  OpenGL texture ID to the sprite object. This ID is requested from the Texture Manager. The
  SetBufferID() and SetShaderAttribute() routines do not consider the normal buffer or normal
  shader attribute respectively, because 2D sprites need not worry over lighting (Temporary!!)

- The Draw() function is different in all the classes, therefore it will be virtually overriden 
  based on what object type is being used. The base class and the sub-classes all calculate the 
  texture index differently.

- The CreateSprite(), CreateColors(), and CreateTexCoords() routines all belong to the Sprite 
  class but are accessible in the sub-classes. They all perform the same functionality for all 
  classes, therefore they only need to be inside the base class. The CreateSprite() routine might
  seem overkill and could easily be integrated inside the Draw() function, but then the deriving
  subclasses would have to duplicate code.

*/

#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "Buffer.h"
#include "Color.h"
#include "OpenGL.h"
#include "Vector2D.h"

class Sprite
{

public :

	enum SpriteType { STATIC, DYNAMIC };

public :

	Sprite();           
	virtual ~Sprite() {}

public :

	Color& SpriteColor();

public :

	void SetSpriteType(SpriteType spritetype);
	void SetTextureCell(GLint column, GLint row);
	void SetTextureDimension(GLint column, GLint row);
	void SetTextureID(const std::string& mapIndex);
	void SetSpriteDimension(GLfloat width, GLfloat height); 
	void SetBufferID(const std::string& vertexID, const std::string& colorID, 
		             const std::string& textureID);
	void SetShaderAttribute(const std::string& vertexAttr, const std::string& colorAttr, 
		                    const std::string& textureAttr);
	
public :

	virtual void Draw();

protected :

	void FillBuffers();
	void ClearBufferData();

protected :

	void CreateSprite();
	void CreateColors();
	void CreateVertices();
	void CreateTexCoords();
	
protected :

	bool m_isSpriteCreated;

	GLuint m_textureID;
	GLint m_textureIndex;

	Color m_color;
	Buffer m_buffer;
	SpriteType m_spriteType;

	Vector2D<GLint> m_textureCell;
	Vector2D<GLint> m_textureDimension;
	Vector2D<GLfloat> m_spriteDimension;
	
};

#endif