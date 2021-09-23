#pragma once

/*===================================================================#
| 'Shader' source files last updated on 20 July 2021                 |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include <map>
#include <string>
#include <glm.hpp>
#include "glad.h"

class Shader
{

public:

	Shader();
	~Shader();

	GLuint GetUniformID(const std::string& uniform) const;
	GLuint GetAttributeID(const std::string& attribute) const;

	bool Create(const std::string& vertexShaderFilename,
		const std::string& fragmentShaderFilename);

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

	void Use();
	void Destroy();

private:

	bool LinkProgram();
	bool CompileShaders(const std::string& filename);

	static GLint s_vertexShaderID;
	static GLint s_fragmentShaderID;

	GLuint m_shaderProgramID;
	std::map<std::string, GLuint> m_uniforms;
	std::map<std::string, GLuint> m_attributes;

};