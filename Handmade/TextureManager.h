/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : November 2015

  -----------------------------------------------------------------------------------------------

- This class encapsulates a texture manager which will load images from disk and store them as 
  OpenGL integer IDs in a map, with a string reference to that texture. The images are loaded 
  using SDL's image loading function and generated through OpenGL to produce an ID that is needed
  to use that image. Currently the images supported are BMP, PNG, JPG, GIF, TGA. <TBA>. To access a 
  particular image inside the map the string reference is needed to sift through the map and find 
  the texture. Textures can also be unloaded from memory individually or in bulk. This class is a 
  Singleton.

- Two enum types have been created to be used when removing texture images from the map. Either
  one single specific texture can be removed, or the entire map of textures can be cleared.

- To use this class, an object in the client code will need to link to a specific texture ID
  from within the Texture Manager. The GetTextureID() function is used to request the OpenGL ID
  and link the texture data with the external object. 

- The Enable() and Disable() routines activate and de-activate a specific texture respectively, 
  and this needs to be done before a specific texture can be used.

- An Output() routine is there for debug purposes only and will print to the console how many texture 
  IDs are currently stored in the map.

*/

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <string>
#include <OpenGL.h>
#include "Singleton.h"

class TextureManager
{

public:

	enum RemoveType { CUSTOM_TEXTURE, ALL_TEXTURES };

public :

	friend class Singleton<TextureManager>;

public:

	GLuint GetTextureID(const std::string& mapIndex);

public:

	void Enable(GLuint textureID);
	void Disable();

public:

	bool LoadFromFile(const std::string& filename, const std::string& mapIndex);
	void UnloadFromMemory(RemoveType removeType, const std::string& mapIndex = "");

public:

	void Output();

private :

	TextureManager()  {}
	TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);

private :

	std::map<std::string, GLuint> m_textureIDMap;
	
};

typedef Singleton<TextureManager> TheTexture;

#endif