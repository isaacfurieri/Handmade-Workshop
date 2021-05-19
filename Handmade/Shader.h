#pragma once

/*===================================================================#
| 'Shader' source files last updated on 19 May 2021                  |
#===================================================================*/

#include <map>
#include <string>
#include "glad.h"
#include <glm.hpp>

//TODO - Research shader compilation & linking error checks (OpenGL cookbook)
//TODO - Refine class such that it follows the newer design

class Shader
{

public:

	enum RenderType
	{
		POLYGON_MODE = GL_LINE,
		FULL_SHADE = GL_FILL
	};

	enum ShaderType
	{
		VERTEX_SHADER = GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};

	static Shader* Instance();

	GLint GetUniformID(const std::string& uniform);
	GLint GetAttributeID(const std::string& attribute);

	static void SetLineWidth(GLfloat lineWidth);
	static void SetPointSize(GLfloat pointSize);
	static void SetRenderType(RenderType renderType);

	void BindUniform(const std::string& uniform);
	void BindAttribute(const std::string& attribute);

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

	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	std::map<std::string, GLuint> m_uniforms;
	std::map<std::string, GLuint> m_attributes;

};