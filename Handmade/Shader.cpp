#include <fstream>
#include <iostream>
#include <string>
#include "Shader.h"

//------------------------------------------------------------------------------------------------------
//static function that will create an instance of this Screen object and return its address
//------------------------------------------------------------------------------------------------------
Shader* Shader::Instance()
{

	static Shader* shaderObject = new Shader();
	return shaderObject;

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Shader::Shader()
{

	m_shaderProgramID = 0;
	m_vertexShaderID = 0;
	m_fragmentShaderID = 0;
	
}
//------------------------------------------------------------------------------------------------------
//setter function that toggles shading of geometry between polygons and full shading
//------------------------------------------------------------------------------------------------------
void Shader::SetRenderType(RenderType renderType)
{

	glPolygonMode(GL_FRONT_AND_BACK, renderType == POLYGON_MODE ? GL_LINE : GL_FILL);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns shader vertex attribute ID
//------------------------------------------------------------------------------------------------------
GLuint Shader::GetShaderAttribute(const std::string& vertAttrib)
{

	return glGetAttribLocation(m_shaderProgramID, vertAttrib.c_str());

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (INT)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, GLint intData)
{

	glUniform1i(glGetUniformLocation(m_shaderProgramID, uniform.c_str()), intData);
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (UNSIGNED INT)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, GLuint uintData)
{

	glUniform1ui(glGetUniformLocation(m_shaderProgramID, uniform.c_str()), uintData);
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (FLOAT)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, GLfloat floatData)
{

	glUniform1f(glGetUniformLocation(m_shaderProgramID, uniform.c_str()), floatData);
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (VEC2)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, const glm::vec2& vec2Data)
{

	glUniform2fv(glGetUniformLocation(m_shaderProgramID, uniform.c_str()), 1, &vec2Data.x);
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (VEC3)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, const glm::vec3& vec3Data)
{

	glUniform3fv(glGetUniformLocation(m_shaderProgramID, uniform.c_str()), 1, &vec3Data.x);
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (VEC4)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, const glm::vec4& vec4Data)
{

	glUniform4fv(glGetUniformLocation(m_shaderProgramID, uniform.c_str()), 1, &vec4Data.x);
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (3x3 MATRIX)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, 
	                                  const glm::mat3& matrix3x3, bool transposed)
{

	glUniformMatrix3fv(glGetUniformLocation(m_shaderProgramID, uniform.c_str()), 1, 
		               (GLboolean)transposed, &matrix3x3[0][0]);
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (4x4 MATRIX)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, 
	                                  const glm::mat4& matrix4x4, bool transposed)
{

	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramID, uniform.c_str()), 1, 
		               (GLboolean)transposed, &matrix4x4[0][0]);
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sends attribute data to vertex shader (FLOAT)
//------------------------------------------------------------------------------------------------------
bool Shader::SendAttributeData(const std::string& attribute, GLfloat floatData)
{

	glVertexAttrib1f(glGetUniformLocation(m_shaderProgramID, attribute.c_str()), floatData);
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sends attribute data to vertex shader (VEC2)
//------------------------------------------------------------------------------------------------------
bool Shader::SendAttributeData(const std::string& attribute, const glm::vec2& vec2Data)
{

	glVertexAttrib2f(glGetUniformLocation(m_shaderProgramID, attribute.c_str()), vec2Data.x, vec2Data.y);
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sends attribute data to vertex shader (VEC3)
//------------------------------------------------------------------------------------------------------
bool Shader::SendAttributeData(const std::string& attribute, const glm::vec3& vec3Data)
{

	glVertexAttrib3f(glGetUniformLocation(m_shaderProgramID, attribute.c_str()), 
		             vec3Data.x, vec3Data.y, vec3Data.z);
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sends attribute data to vertex shader (VEC4)
//------------------------------------------------------------------------------------------------------
bool Shader::SendAttributeData(const std::string& attribute, const glm::vec4& vec4Data)
{

	glVertexAttrib4f(glGetUniformLocation(m_shaderProgramID, attribute.c_str()), 
		             vec4Data.x, vec4Data.y, vec4Data.z, vec4Data.w);
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that creates the main shader program
//------------------------------------------------------------------------------------------------------
bool Shader::CreateProgram()
{

	//create main shader program object
	m_shaderProgramID = glCreateProgram();

	//if an error occurred creating the shader 
	//program display an error message and return false
	if (m_shaderProgramID == 0)
	{
		std::cout << "Shader program could not be created." << std::endl;
		return false;
	}

	return true;
	
}
//------------------------------------------------------------------------------------------------------
//function that creates a vertex and fragment shader object
//------------------------------------------------------------------------------------------------------
bool Shader::CreateShaders()
{
		
	//create a OpenGL shader ID for the vertex and fragment shader
	//if an error occured while creating either shader display
	//an error message and return false back to the calling code

	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	
	if (m_vertexShaderID == 0)
	{
		std::cout << "Vertex shader could not be created." << std::endl;
		return false;
	}
	
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (m_fragmentShaderID == 0)
	{
		std::cout << "Fragment shader could not be created." << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that reads in the shader source code and compiles it
//------------------------------------------------------------------------------------------------------
bool Shader::CompileShader(ShaderType shaderType, const std::string& filename)
{

	//variables for file handling, source code 
	//text reading and storing and temp shader ID storage
	std::fstream file;
	std::string lineText = "";
	std::string finalString = "";
	GLint tempShaderID;
	GLint compileResult;

	//display text to state that file is being opened and read
	std::cout << "Opening and reading "
		      << (shaderType == VERTEX_SHADER ? "vertex" : "fragment") << " shader file : "
		      << "\"" << filename << "\"" << std::endl;

	//open shader file
	file.open(filename);

	//if file has an error opening output error message
	if (!file)
	{
		std::cout << "Shader file could not be loaded." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
		return false;
	}

	//based on which shader needs to be compiled point to specific 
	//shader ID so that when compiling later there is no duplicate code
	switch (shaderType)
	{
		case VERTEX_SHADER   : tempShaderID = m_vertexShaderID; break;
		case FRAGMENT_SHADER : tempShaderID = m_fragmentShaderID; break;
	}

	//read through the entire file and add each line of code into a big string
	//the newline character needs to be added to the end of each code line
	while (!file.eof())
	{
		getline(file, lineText);
		finalString += lineText + "\n";
	}

	//close the file 
	file.close();

	//convert final code string into a char array 
	//because OpenGL requires this format for compilation 
	const GLchar* finalCode = (const GLchar*)(finalString.c_str());

	//debug output of long shader source code
	std::cout << "Compiling shader file..." << std::endl;

	//bind shader object with the shader source code
	glShaderSource(tempShaderID, 1, &finalCode, NULL);

	//compile the source code using the shader object
	glCompileShader(tempShaderID);

	//request compilation error code for error checking
	glGetShaderiv(tempShaderID, GL_COMPILE_STATUS, &compileResult);

	//if compilation went well, display a friendly message
	if (compileResult == GL_TRUE)
	{
		std::cout << "Shader file compiled successfully." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
	}

	//otherwise request error string and store in an 
	//array of a set size and display the error on screen
	else
	{
		GLchar error[1000];
		GLsizei length = 1000;

		std::cout << "Shader file could not be compiled. See error list below." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;

		glGetShaderInfoLog(tempShaderID, 1000, &length, error);
		std::cout << error << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;

		return false;

	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that attaches the vertex and fragment shader object to the main shader program 
//------------------------------------------------------------------------------------------------------
void Shader::AttachShaders()
{

	glAttachShader(m_shaderProgramID, m_vertexShaderID);
	glAttachShader(m_shaderProgramID, m_fragmentShaderID);

}
//------------------------------------------------------------------------------------------------------
//function that links entire program together
//------------------------------------------------------------------------------------------------------
bool Shader::LinkProgram()
{

	//variable to store link error code
	GLint linkResult = 0;

	//link entire shader program with all its shader objects
	glLinkProgram(m_shaderProgramID);

	//activate main shader program
	glUseProgram(m_shaderProgramID);

	//request linking error code for error checking
	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &linkResult);

	//there is no check here for link success because when linking is performed 
	//multiple times, that will display too many messages on the console screen

	//if linking failed, request error string and store 
	//in an array of a set size, and display the error on screen
	if (linkResult == GL_FALSE)
	{
		GLchar error[1000];
		GLsizei length = 1000;

		std::cout << "Shader program could not be linked. See error list below." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;

		glGetProgramInfoLog(m_shaderProgramID, 1000, &length, error);
		std::cout << error << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;

		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that detaches the vertex and fragment shader object from the main shader program
//------------------------------------------------------------------------------------------------------
void Shader::DetachShaders()
{

	glDetachShader(m_shaderProgramID, m_vertexShaderID);
	glDetachShader(m_shaderProgramID, m_fragmentShaderID);

}
//------------------------------------------------------------------------------------------------------
//function that unloads the vertex and fragment shader IDs from memory
//------------------------------------------------------------------------------------------------------
void Shader::DestroyShaders()
{

	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);

}
//------------------------------------------------------------------------------------------------------
//function that destroys shader program 
//------------------------------------------------------------------------------------------------------
void Shader::DestroyProgram()
{

	glDeleteProgram(m_shaderProgramID);

}