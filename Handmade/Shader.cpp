#include <assert.h>
#include <fstream>
#include "Shader.h"
#include "Utility.h"

//======================================================================================================
Shader* Shader::Instance()
{
	static Shader* shader = new Shader;
	return shader;
}
//======================================================================================================
Shader::Shader()
{
	m_shaderProgramID = 0;
	m_vertexShaderID = 0;
	m_fragmentShaderID = 0;
}
//======================================================================================================
GLuint Shader::GetUniformID(const std::string& uniform) const
{
	auto it = m_uniforms.find(uniform);
	assert(it != m_uniforms.end());
	return it->second;

	/*{
		Utility::Log(FILE, "Shader uniform '" + uniform + "' not bound", Utility::WARNING);
		return -1;
	}*/
}
//======================================================================================================
GLuint Shader::GetAttributeID(const std::string& attribute) const
{
	auto it = m_attributes.find(attribute);
	assert(it != m_attributes.end());
	return it->second;

	/*{
		Utility::Log(FILE, "Vertex attribute '" + attribute + "' not bound", Utility::WARNING);
		return -1;
	}*/
}
//======================================================================================================
void Shader::BindUniform(const std::string& uniform)
{
	auto it = m_uniforms.find(uniform);

	if (it == m_uniforms.end())
	{
		GLint ID = glGetUniformLocation(m_shaderProgramID, uniform.c_str());

		//Unbound shader uniforms are either 
		//not present in the shader or unused
		assert(ID != -1);

		m_uniforms[uniform] = ID;

		/*{
			Utility::Log(FILE, "Shader uniform '" + uniform + "' not bound", Utility::WARNING);
		}*/
	}

	/*else
	{
		Utility::Log(FILE, "Shader uniform '" + uniform + "' already bound", Utility::WARNING);
	}*/
}
//======================================================================================================
void Shader::BindAttribute(const std::string& attribute)
{
	auto it = m_attributes.find(attribute);

	if (it == m_attributes.end())
	{
		GLint ID = glGetAttribLocation(m_shaderProgramID, attribute.c_str());

		//Unbound shader attributes are either 
		//not present in the shader or unused
		assert(ID != -1);

		m_attributes[attribute] = ID;
		/*{
			Utility::Log(FILE, "Vertex attribute '" + attribute + "' not bound",
				Utility::WARNING);
		}*/
	}
}
//======================================================================================================
void Shader::SendData(const std::string& uniform, GLint intData) const
{
	glUniform1i(GetUniformID(uniform), intData);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform, GLuint uintData) const
{
	glUniform1ui(GetUniformID(uniform), uintData);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform, GLfloat floatData) const
{
	glUniform1f(GetUniformID(uniform), floatData);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform, const glm::vec2& vec2Data) const
{
	glUniform2fv(GetUniformID(uniform), 1, &vec2Data.x);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform, const glm::vec3& vec3Data) const
{
	glUniform3fv(GetUniformID(uniform), 1, &vec3Data.x);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform, const glm::vec4& vec4Data) const
{
	glUniform4fv(GetUniformID(uniform), 1, &vec4Data.x);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform,
	const glm::mat3& matrix3x3, bool transposed) const
{
	glUniformMatrix3fv(GetUniformID(uniform), 1, transposed, &matrix3x3[0][0]);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform,
	const glm::mat4& matrix4x4, bool transposed) const
{
	glUniformMatrix4fv(GetUniformID(uniform), 1, transposed, &matrix4x4[0][0]);
}
//======================================================================================================
bool Shader::CreateProgram()
{
	m_shaderProgramID = glCreateProgram();

	if (m_shaderProgramID == 0)
	{
		Utility::Log(FILE, "Error creating shader program", Utility::FAILURE);
		Utility::Log(MESSAGE_BOX, "Error creating shader program", Utility::FAILURE);
		return false;
	}

	return true;
}
//======================================================================================================
bool Shader::CreateShaders()
{
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (m_vertexShaderID == 0)
	{
		Utility::Log(FILE, "Error creating vertex shader object", Utility::FAILURE);
		Utility::Log(MESSAGE_BOX, "Error creating vertex shader object", Utility::FAILURE);
		return false;
	}

	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (m_fragmentShaderID == 0)
	{
		Utility::Log(FILE, "Error creating fragment shader object", Utility::FAILURE);
		Utility::Log(MESSAGE_BOX, "Error creating fragment shader object", Utility::FAILURE);
		return false;
	}

	return true;
}
//======================================================================================================
bool Shader::CompileShader(const std::string& filename, ShaderType shaderType)
{
	std::string sourceCode;

	if (!Utility::LoadShaderFile(filename, sourceCode))
	{
		Utility::Log(FILE, "Error opening shader file '" + filename + "'", Utility::FAILURE);
		Utility::Log(MESSAGE_BOX, "Error opening shader file '" + filename + "'", Utility::FAILURE);
		return false;
	}

	GLint tempShaderID = 0;

	switch (shaderType)
	{
	case ShaderType::VERTEX_SHADER: tempShaderID = m_vertexShaderID; break;
	case ShaderType::FRAGMENT_SHADER: tempShaderID = m_fragmentShaderID; break;
	}

	const GLchar* finalCode = (const GLchar*)(sourceCode.c_str());

	glShaderSource(tempShaderID, 1, &finalCode, nullptr);
	glCompileShader(tempShaderID);

	GLint compileResult;
	glGetShaderiv(tempShaderID, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_FALSE)
	{
		GLchar error[1000];
		GLsizei length = 1000;
		glGetShaderInfoLog(tempShaderID, 1000, &length, error);

		Utility::Log(FILE, error, Utility::FAILURE);
		Utility::Log(MESSAGE_BOX, error, Utility::FAILURE);
		return false;
	}

	else
	{
		Utility::Log(FILE, "Shader file '" + filename + "' successfully compiled.",
			Utility::DEFAULT);
	}

	return true;
}
//======================================================================================================
void Shader::AttachShaders()
{
	glAttachShader(m_shaderProgramID, m_vertexShaderID);
	glAttachShader(m_shaderProgramID, m_fragmentShaderID);
}
//======================================================================================================
bool Shader::LinkProgram()
{
	GLint linkResult = 0;
	glLinkProgram(m_shaderProgramID);
	glUseProgram(m_shaderProgramID);
	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_FALSE)
	{
		GLchar error[1000];
		GLsizei length = 1000;
		glGetProgramInfoLog(m_shaderProgramID, 1000, &length, error);

		Utility::Log(FILE, error, Utility::FAILURE);
		Utility::Log(MESSAGE_BOX, error, Utility::FAILURE);
		return false;
	}

	return true;
}
//======================================================================================================
void Shader::DetachShaders()
{
	glDetachShader(m_shaderProgramID, m_vertexShaderID);
	glDetachShader(m_shaderProgramID, m_fragmentShaderID);
}
//======================================================================================================
void Shader::DestroyShaders()
{
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}
//======================================================================================================
void Shader::DestroyProgram()
{
	glDeleteProgram(m_shaderProgramID);
}