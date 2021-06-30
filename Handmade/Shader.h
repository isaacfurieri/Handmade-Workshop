#pragma once

/*===================================================================#
| 'Shader' source files last updated on 23 June 2021                 |
#===================================================================*/

#include <map>
#include <string>
#include <glm.hpp>
#include "glad.h"

class Shader
{

public:

	enum class ShaderType
	{
		VERTEX_SHADER = GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};

	static Shader* Instance();

	GLint GetUniformID(const std::string& uniform);
	GLint GetAttributeID(const std::string& attribute);

	void BindUniform(const std::string& uniform);
	void BindAttribute(const std::string& attribute);

	bool SendData(const std::string& uniform, GLint intData);
	bool SendData(const std::string& uniform, GLuint uintData);
	bool SendData(const std::string& uniform, GLfloat floatData);
	bool SendData(const std::string& uniform, const glm::vec2& vec2Data);
	bool SendData(const std::string& uniform, const glm::vec3& vec3Data);
	bool SendData(const std::string& uniform, const glm::vec4& vec4Data);

	bool SendData(const std::string& uniform,
		const glm::mat3& matrix3x3, bool transposed = false);

	bool SendData(const std::string& uniform,
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