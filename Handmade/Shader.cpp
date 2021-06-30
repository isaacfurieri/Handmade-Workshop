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
GLint Shader::GetUniformID(const std::string& uniform)
{
	auto it = m_uniforms.find(uniform);

	if (it == m_uniforms.end())
	{
		Utility::Log(FILE, "Shader uniform '" + uniform + "' not bound", Utility::WARNING);
		return -1;
	}

	else
	{
		return it->second;
	}
}
//======================================================================================================
GLint Shader::GetAttributeID(const std::string& attribute)
{
	auto it = m_attributes.find(attribute);

	if (it == m_attributes.end())
	{
		Utility::Log(FILE, "Vertex attribute '" + attribute + "' not bound", Utility::WARNING);
		return -1;
	}

	else
	{
		return it->second;
	}
}
//======================================================================================================
void Shader::BindUniform(const std::string& uniform)
{
	auto it = m_uniforms.find(uniform);

	if (it == m_uniforms.end())
	{

		GLint ID = glGetUniformLocation(m_shaderProgramID, uniform.c_str());

		if (ID == -1)
		{
			Utility::Log(FILE, "Shader uniform '" + uniform + "' not bound", Utility::WARNING);
		}

		else
		{
			m_uniforms[uniform] = ID;
			Utility::Log(FILE, "Shader uniform '" + uniform + "' bound", Utility::DEFAULT);
		}

	}

	else
	{
		Utility::Log(FILE, "Shader uniform '" + uniform + "' already bound", Utility::WARNING);
	}
}
//======================================================================================================
void Shader::BindAttribute(const std::string& attribute)
{
	auto it = m_attributes.find(attribute);

	if (it == m_attributes.end())
	{

		GLint ID = glGetAttribLocation(m_shaderProgramID, attribute.c_str());

		if (ID == -1)
		{
			Utility::Log(FILE, "Vertex attribute '" + attribute + "' not bound",
				Utility::WARNING);
		}

		else
		{
			m_attributes[attribute] = ID;
			Utility::Log(FILE, "Vertex attribute '" + attribute + "' bound",
				Utility::DEFAULT);
		}

	}

	else
	{
		Utility::Log(FILE, "Vertex attribute '" + attribute + "' already bound",
			Utility::WARNING);
	}
}
//======================================================================================================
bool Shader::SendData(const std::string& uniform, GLint intData)
{
	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniform1i(ID, intData);
		return true;
	}

	return false;
}
//======================================================================================================
bool Shader::SendData(const std::string& uniform, GLuint uintData)
{
	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniform1ui(ID, uintData);
		return true;
	}

	return false;
}
//======================================================================================================
bool Shader::SendData(const std::string& uniform, GLfloat floatData)
{
	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniform1f(ID, floatData);
		return true;
	}

	return false;
}
//======================================================================================================
bool Shader::SendData(const std::string& uniform, const glm::vec2& vec2Data)
{
	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniform2fv(ID, 1, &vec2Data.x);
		return true;
	}

	return false;
}
//======================================================================================================
bool Shader::SendData(const std::string& uniform, const glm::vec3& vec3Data)
{
	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniform3fv(ID, 1, &vec3Data.x);
		return true;
	}

	return false;
}
//======================================================================================================
bool Shader::SendData(const std::string& uniform, const glm::vec4& vec4Data)
{
	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniform4fv(ID, 1, &vec4Data.x);
		return true;
	}

	return false;
}
//======================================================================================================
bool Shader::SendData(const std::string& uniform,
	const glm::mat3& matrix3x3, bool transposed)
{
	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniformMatrix3fv(ID, 1, transposed, &matrix3x3[0][0]);
		return true;
	}

	return false;
}
//======================================================================================================
bool Shader::SendData(const std::string& uniform,
	const glm::mat4& matrix4x4, bool transposed)
{
	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniformMatrix4fv(ID, 1, transposed, &matrix4x4[0][0]);
		return true;
	}

	return false;
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