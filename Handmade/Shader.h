#pragma once

/*===================================================================#
| 'Shader' source files last updated on 6 July 2021                  |
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

	GLuint GetUniformID(const std::string& uniform) const;
	GLuint GetAttributeID(const std::string& attribute) const;

	void BindUniform(const std::string& uniform);
	void BindAttribute(const std::string& attribute);

	void SendData(const std::string& uniform, GLint intData) const;
	void SendData(const std::string& uniform, GLuint uintData) const;
	void SendData(const std::string& uniform, GLfloat floatData) const;
	void SendData(const std::string& uniform, const glm::vec2& vec2Data) const;
	void SendData(const std::string& uniform, const glm::vec3& vec3Data) const;
	void SendData(const std::string& uniform, const glm::vec4& vec4Data) const;

	void SendData(const std::string& uniform,
		const glm::mat3& matrix3x3, bool transposed = false) const;

	void SendData(const std::string& uniform,
		const glm::mat4& matrix4x4, bool transposed = false) const;

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