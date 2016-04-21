/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : November 2015

  -----------------------------------------------------------------------------------------------

- This class encapsulates a vertex buffer object (VBO) manager which will create buffer objects 
  and store them as OpenGL integer IDs in various maps, with a string reference to that buffer. 
  The VBOs are created through OpenGL to produce an ID that is needed to use that buffer. Currently
  four different VBOs are supported which are vertex, color, normal and texture buffers. Each buffer
  type has its own map associated with it. To access a particular VBO inside the map the VBO type 
  and string reference is needed to sift through the correct map and find the buffer. VBOs can 
  also be unloaded from memory individually or in bulk. This class is a Singleton.

- Two enum types have been created, one to be used when removing buffers from the map, and the 
  other for specifying which type of buffer to work with. The first enum allows either one single
  specific buffer to be removed, or the entire map of buffers to be cleared. The second enum allows
  for the programmer to work with one of the four supported VBO types.

- To use this class, a Buffer object needs to be created inside the game client code. Then that 
  buffer object will be able to link to a specific VBO buffer ID from within the Buffer Manager. 
  The GetBufferID() function is used to request the OpenGL ID and link the VBO buffer data with the
  buffer object.

- The main routines are designed to create and destroy OpenGL buffer IDs, as well as fill them with
  data. The Fill() function can be called once from the client code, if the buffer will remain 
  unchanged, or multiple times if the buffer data is dynamic. The Enable() and Disable() routines
  activate and de-activate buffers respectively, and this needs to be done before a specific VBO
  can be used.

- An Output() routine is there for debug purposes only and will print to the console how many buffer
  IDs are currently stored in each of the four supported maps.

*/

#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include <map>
#include <string>
#include <vector>
#include <OpenGL.h>
#include "Singleton.h"

class BufferManager
{

public :

	enum RemoveType { CUSTOM_BUFFER, ALL_BUFFERS };
	enum BufferType { VERTEX_BUFFER, COLOR_BUFFER, NORMAL_BUFFER, TEXTURE_BUFFER };
	
public:

	friend class Singleton<BufferManager>;

public :

	GLuint GetBufferID(BufferType bufferType, const std::string& mapIndex);
	
public :

	void Enable(GLuint bufferID);
	void Disable();

public:

	void Create(BufferType bufferType, const std::string& mapIndex);
	void Fill(GLuint bufferID, std::vector<GLfloat>& data);
	void Destroy(BufferType bufferType, RemoveType removeType, const std::string& mapIndex = "");

public:

	void Output();

private:

	BufferManager() {}
	BufferManager(const BufferManager&);
	BufferManager& operator=(const BufferManager&);

private:

	std::map<std::string, GLuint> m_vertexBufferIDMap;
	std::map<std::string, GLuint> m_colorBufferIDMap;
	std::map<std::string, GLuint> m_normalBufferIDMap;
	std::map<std::string, GLuint> m_textureBufferIDMap;

};

typedef Singleton<BufferManager> TheBuffer;

#endif