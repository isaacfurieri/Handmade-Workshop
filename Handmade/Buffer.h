#ifndef BUFFER_H
#define BUFFER_H

/*==============================================================================================#
|                                                                                               |
| All code has been written by Karsten Vermeulen as part of the 'Handmade' game engine, for the |
| purposes of educating other fellow programmers, programming students and anyone else wishing  |
| to learn about game development, C++ and OOP. The engine, class design and overall structure  |
| is by no means perfect and there is certainly room for improvement. Feel free to use, copy,   |
| break, update and do as you wish with this code - it is there, free, for all!                 |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|																								|
| If you like 'Handmade', and wish to show your support, if you have any questions about the    |
| project, or if you just want to reach out, please find me on the following channels:          |
|																						        |
| Web: http://www.karstenvermeulen.com														    |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'Buffer' source files last updated in December 2019									        |
#==============================================================================================*/

#include <map>
#include <string>
#include <vector>
#include "glad.h"

struct BufferID
{
	bool hasEBO;
	GLuint vaoID;
	GLuint vboID[4];
	GLuint eboID;
	GLsizei totalVertices;
};

class Buffer
{

public:

	enum DataType       { FLOAT, U_INT };
	enum FillType       { STATIC_FILL, DYNAMIC_FILL };
	enum ComponentSize  { XY = 2, XYZ = 3, RGB = 3, RGBA = 4, UV = 2 };
	enum DrawMode       { LINES, LINE_LOOP, POINTS, TRIANGLES, TRIANGLE_FAN };
	enum VBOType        { VERTEX_BUFFER, COLOR_BUFFER, NORMAL_BUFFER, TEXTURE_BUFFER };

public:

	Buffer();

public:

	void SetLineWidth(GLfloat lineWidth);
	void SetPointSize(GLfloat pointSize);
	void SetBuffers(const std::string& bufferID);

public:

	bool CreateBuffers(const std::string& bufferID, GLsizei totalVertices = 0, bool hasEBO = false);

	void BindEBO();
	void BindVBO(VBOType vboType, const std::string& vertAttrib,
		         ComponentSize componentSize, DataType dataType);

	void FillEBO(const GLuint* data, GLsizeiptr size, FillType fillType = STATIC_FILL);
	void FillVBO(VBOType vboType, const GLuint* data, GLsizeiptr size, FillType fillType = STATIC_FILL);
	void FillVBO(VBOType vboType, const GLfloat* data, GLsizeiptr size, FillType fillType = STATIC_FILL);

	void AppendEBO(const GLuint* data, GLsizeiptr size, GLuint offset);
	void AppendVBO(VBOType vboType, const GLuint* data, GLsizeiptr size, GLuint offset);
	void AppendVBO(VBOType vboType, const GLfloat* data, GLsizeiptr size, GLuint offset);

	void Draw(DrawMode drawMode);

	void DestroyBuffers();
	void DestroyBuffers(const std::string& bufferID);

public:

	void Output();

private:

	static std::map<std::string, BufferID>* s_bufferIDMap;

private:

	BufferID m_ID;

};

#endif