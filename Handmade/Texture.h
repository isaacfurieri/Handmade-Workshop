/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates a texture manager of sorts, without using the dreaded Singleton design 
  pattern! It will load images from disk and store them as OpenGL integer IDs in a map, with a 
  string reference to that texture. The images are loaded using SDL's image loading function and
  generated through OpenGL to produce an ID that is needed to use that image. Currently the images
  supported are BMP, PNG, JPG, GIF, TGA. <TBA>. To access a particular image inside the map the
  string reference is needed to sift through the map and find the texture. Textures can also be
  unloaded from memory individually or in bulk. The map that stores all the texture ID is on the
  heap and statically referenced so that there is only 1 single "catalogue" of texture IDs.

- Textures are meant to be loaded once only and stored in the given map. If that same texture is
  required by another object, instead of loading it again, we simply use SetTexture() to set an
  existing texture to the object. This models around the Flyweight pattern a little bit. When 
  textures are loaded or set, the m_ID variable is assigned the ID of that texture.

- The Bind() and Unbind() routines will bind the current texture ID with the shaders so that 
  when rendering the objects the bound texture is used

- To use this class, an object in the client code will need to create a Texture instance within 
  itself, using the Component model. Ideally game objects will contain Texture objects and use 
  them accordingly. 

*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <map>
#include <string>
#include "glad.h"

class Texture
{

public:

	Texture();

public:

	void SetTexture(const std::string& textureID);

public:

	bool Load(const std::string& filename, const std::string& textureID);
	void Bind();

public:

	void UnBind();
	void Unload();
	void Unload(const std::string& textureID);

public:

	void Output();

private:

	static std::map<std::string, GLuint>* s_textureIDMap;

private:

	GLuint m_ID;

};

#endif