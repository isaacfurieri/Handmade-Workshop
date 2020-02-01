#ifndef SHADER_H
#define SHADER_H

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
| 'Shader' source files last updated in February 2020							       	        |
#==============================================================================================*/

#include <map>
#include <string>
#include "glad.h"
#include <glm.hpp>

class Shader
{

public:

	enum RenderType { POLYGON_MODE = GL_LINE, FULL_SHADE = GL_FILL };
	enum ShaderType { VERTEX_SHADER = GL_VERTEX_SHADER, 
		              FRAGMENT_SHADER = GL_FRAGMENT_SHADER };
	
public:

	static Shader* Instance();

public:

	GLint GetUniformID(const std::string& uniform);
	GLint GetAttributeID(const std::string& attribute);

public:

	static void SetLineWidth(GLfloat lineWidth);
	static void SetPointSize(GLfloat pointSize);
	static void SetRenderType(RenderType renderType);

public:

	void BindUniform(const std::string& uniform);
	void BindAttribute(const std::string& attribute);

public:

	bool SendUniformData(const std::string& uniform, GLint intData);
	bool SendUniformData(const std::string& uniform, GLuint uintData);
	bool SendUniformData(const std::string& uniform, GLfloat floatData);
	bool SendUniformData(const std::string& uniform, const glm::vec2& vec2Data);
	bool SendUniformData(const std::string& uniform, const glm::vec3& vec3Data);
	bool SendUniformData(const std::string& uniform, const glm::vec4& vec4Data);
	
	bool SendUniformData(const std::string& uniform, 
		                 const glm::mat3& matrix3x3, bool transposed = false);
	bool SendUniformData(const std::string& uniform, 
		                 const glm::mat4& matrix4x4, bool transposed = false);

public:

	bool CreateProgram();
	bool CreateShaders();

	bool CompileShader(const std::string& filename, ShaderType shaderType);
	void AttachShaders();
	bool LinkProgram();
	
	void DetachShaders();
	void DestroyShaders();
	void DestroyProgram();

private:

	Shader();
	Shader(const Shader&);
	Shader& operator=(Shader&);

private:

	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	std::map<std::string, GLuint> m_uniforms;
	std::map<std::string, GLuint> m_attributes;

};

#endif