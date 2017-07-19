/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This buffer class is designed to contain all vertex, color, normal and texture coordinate data
  that is needed to render something on screen. It contains vector containers to store the actual
  data, four VBO buffer IDs to link to the OpenGL VBOs related to the data, and four shader 
  attribute IDs to link to the shader variables. The OpenGL VBO IDs will be used to bind the correct
  VBO and fill it with data before using it. The shader attribute IDs are needed to bind each vertex,
  color, normal and texture data with the correct shader variable when drawing. The VBO and shader
  attribute IDs are requested from the Buffer and Shader Manager respectively. This class can be
  used on its own or within another class like the Sprite or Model class to represent their data.
  
- Three enum data types have been created to make drawing and accessing VBOs easier. The DrawMode 
  enum is used for passing the rendering style to the DrawData() routine. The BufferType enum is
  for accessing and using the correct VBO, and the ComponentSize enum is an easy way to pass the
  vertex component size to the shader when linking the data.

- Four getter/setter combo functions have been created to return references of the four vector 
  containers that contain all the vertex, color, normal and texture coordinate data. This makes
  accessing and assigning the containers easier in the calling client code.

- The SetBufferID() and SetAttributeID() routines are used to assign the OpenGL VBO buffer IDs and
  shader attribute IDs respectively to the buffer object. These IDs are requested from the Buffer
  and Shader Manager respectively. The SetComponentSize() routine is there to set the vertex, 
  color, normal and texture coordinate data component size before sending data to the shader. For
  instance a vertex component could comprise of X and Y for 2D or X, Y and Z for 3D. Colors can be 
  RGB or RGBA. Using the ComponentSize enum type the component types have already been setup for 
  ease of use.

- The FillData() routine will fill the relevant VBOs with data via the Buffer Manager, and the
  DrawData() function enable the vertex, color, normal and texture coordinate OpenGL VBO buffers
  and shader attributes before using them to send data to the shaders to be rendered. 

- The Buffer class makes full use of the Buffer and Shader Manager classes, keeping all raw OpenGL
  code in the manager classes instead of in here. This class is intended to act as a link between 
  the Buffer and Shader Manager, the shaders and the client code. It's a helper tool to minimize 
  the load in the client code and will most likely reside inside the Model or Sprite classes. 
  (More on this later!!)

*/

#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>
#include <glew.h>

class Buffer
{

public:

	enum DrawMode      { LINES, LINE_LOOP, POINTS, TRIANGLES, TRIANGLE_FAN };
	enum BufferType    { VERTEX_BUFFER, COLOR_BUFFER, NORMAL_BUFFER, TEXTURE_BUFFER };
	enum ComponentSize { XY = 2, XYZ = 3, RGB = 3, RGBA = 4, UV = 2 };

public:

	Buffer();

public :

	std::vector<GLfloat>& Vertices();
	std::vector<GLfloat>& Colors();
	std::vector<GLfloat>& Normals();
	std::vector<GLfloat>& Textures();

public:

	void SetBufferID(BufferType bufferType, const std::string& mapIndex);
	void SetAttributeID(BufferType bufferType, const std::string& mapIndex);
	void SetComponentSize(BufferType bufferType, ComponentSize componentSize);

public :

	void FillData(BufferType bufferType);
	void DrawData(DrawMode drawMode);

private:

	GLuint m_vertexBufferID;
	GLuint m_colorBufferID;
	GLuint m_normalBufferID;
	GLuint m_textureBufferID;

	GLint m_vertexAttributeID;
	GLint m_colorAttributeID;
	GLint m_normalAttributeID;
	GLint m_textureAttributeID;

	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_colors;
	std::vector<GLfloat> m_normals;
	std::vector<GLfloat> m_textures;

	ComponentSize m_vertexComponentSize;
	ComponentSize m_colorComponentSize;
	ComponentSize m_normalComponentSize;
	ComponentSize m_textureComponentSize;

};

#endif