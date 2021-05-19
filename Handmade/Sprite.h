/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

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
  The m_isSpriteSampled flag variable is there to be set if a static sprite has been created 
  already.

- The setter functions will set the specific properties of the sprite. The SetBuffer() function 
  is able to link the sprite's internal buffer with the correct vertex, color and texture VBO. The
  SetTexture() routine is used to assign an OpenGL texture ID to the sprite object. This ID is 
  requested from the Texture class. The Create() routine will create and bind all the neccessary
  VBO buffers except for the normal VBO because 2D sprites need not worry over lighting (For now!)

- The Draw() function is different in all the classes, therefore it is overloaded in each sub-class.
  I decided not to use virtual functions here because that is an unneccessary expense. Presumably
  the user will always know what type of sprite they wish to create. The base class and the 
  sub-classes all calculate the texture index differently.

*/

//TODO - Add 'Tile' class
//TODO - Remove 'Sprite' and 'Animation' classes  
//TODO - Add functionality to process sprite sheets(static/animated)

#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "glad.h"
#include <glm.hpp>
#include "Buffer.h"
#include "Texture.h"

class Sprite
{

public :

	enum SpriteType { STATIC, DYNAMIC };

public :

	Sprite();           

public :

	void SetSpriteType(SpriteType spritetype);

	void SetBuffer(const std::string& bufferID);
	void SetTexture(const std::string& textureID);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	void SetTextureCell(GLuint column, GLuint row);
	void SetTextureDimension(GLuint column, GLuint row);
	
public:

	bool Create(const std::string bufferID);
	void Destroy(const std::string bufferID);
	bool LoadTexture(const std::string& filename, const std::string textureID);
	void UnloadTexture(const std::string textureID);

public :

	void Update();
	void Draw();

protected :

	bool m_isSpriteSampled;

	glm::vec2 m_textureCell;
	glm::vec2 m_textureDimension;

	Buffer m_buffer;
	Texture m_texture;
	SpriteType m_spriteType;

};

#endif