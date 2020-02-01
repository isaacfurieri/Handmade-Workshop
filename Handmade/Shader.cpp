#include <fstream>
#include <iostream>
#include <string>
#include "Debug.h"
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
//getter function that searches map for bound uniform IDs
//------------------------------------------------------------------------------------------------------
GLint Shader::GetUniformID(const std::string& uniform)
{

	//first check if uniform ID exists in the map
	auto it = m_uniforms.find(uniform);

	//if ID was NOT found then return a -1 
	//error code otherwise return the ID

	if (it == m_uniforms.end())
	{
		Debug::Log("Shader uniform '" + uniform + "' not bound.", Debug::WARNING);
		Debug::Log("===============================================================");
		return -1;
	}

	else
	{
		return it->second;
	}

}
//------------------------------------------------------------------------------------------------------
//getter function that searches map for bound vertex attribute IDs
//------------------------------------------------------------------------------------------------------
GLint Shader::GetAttributeID(const std::string& attribute)
{

	//first check if attribute ID exists in the map
	auto it = m_attributes.find(attribute);

	//if ID was NOT found then return a -1 
	//error code otherwise return the ID

	if (it == m_attributes.end())
	{
		Debug::Log("Shader attribute '" + attribute + "' not bound.", Debug::WARNING);
		Debug::Log("===============================================================");
		return -1;
	}

	else
	{
		return it->second;
	}

}
//------------------------------------------------------------------------------------------------------
//setter function that sets thickness of primitive line for rendering
//------------------------------------------------------------------------------------------------------
void Shader::SetLineWidth(GLfloat lineWidth)
{

	glLineWidth(lineWidth);

}
//------------------------------------------------------------------------------------------------------
//setter function that sets size of primitive vertex for rendering
//------------------------------------------------------------------------------------------------------
void Shader::SetPointSize(GLfloat pointSize)
{

	glPointSize(pointSize);

}
//------------------------------------------------------------------------------------------------------
//setter function that toggles shading of geometry between polygons and full shading
//------------------------------------------------------------------------------------------------------
void Shader::SetRenderType(RenderType renderType)
{

	glPolygonMode(GL_FRONT_AND_BACK, renderType == POLYGON_MODE ? GL_LINE : GL_FILL);

}
//------------------------------------------------------------------------------------------------------
//function that searches in the shader for passed uniform and adds it to map if found
//------------------------------------------------------------------------------------------------------
void Shader::BindUniform(const std::string& uniform)
{

	//first check if uniform ID is already in the map
	auto it = m_uniforms.find(uniform);

	//if ID was NOT found then search for it in the shader and if the 
	//returned value is -1 it means the uniform is missing or inactive
	//Otherwise store the newly acquired ID in the map for future use

	if (it == m_uniforms.end())
	{

		GLint ID = glGetUniformLocation(m_shaderProgramID, uniform.c_str());

		if (ID == -1)
		{
			Debug::Log("Shader uniform '" + uniform + "' not found or inactive.", Debug::WARNING);
			Debug::Log("===============================================================");
		}

		else
		{
			m_uniforms[uniform] = ID;
			Debug::Log("Shader uniform '" + uniform + "' bound to program.", Debug::SUCCESS);
			Debug::Log("===============================================================");
		}

	}

	else
	{
		Debug::Log("Shader uniform '" + uniform + "' already bound to program.", Debug::WARNING);
		Debug::Log("===============================================================");
	}

}
//------------------------------------------------------------------------------------------------------
//function that searches in the shader for passed attribute and adds it to map if found
//------------------------------------------------------------------------------------------------------
void Shader::BindAttribute(const std::string& attribute)
{

	//first check if attribute ID is already in the map
	auto it = m_attributes.find(attribute);

	//if ID was NOT found then search for it in the shader and if the 
	//returned value is -1 it means the attribute is missing or inactive
	//Otherwise store the newly acquired ID in the map for future use

	if (it == m_attributes.end())
	{

		GLint ID = glGetAttribLocation(m_shaderProgramID, attribute.c_str());

		if (ID == -1)
		{
			Debug::Log("Shader attribute '" + attribute + "' not found or inactive.", Debug::WARNING);
			Debug::Log("===============================================================");
		}

		else
		{
			m_attributes[attribute] = ID;
			Debug::Log("Shader attribute '" + attribute + "' bound to program.", Debug::SUCCESS);
			Debug::Log("===============================================================");
		}

	}

	else
	{
		Debug::Log("Shader attribute '" + attribute + "' already bound to program.", Debug::WARNING);
		Debug::Log("===============================================================");
	}

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
//function that sends uniform data to shader (INT)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, GLint intData)
{

	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniform1i(ID, intData);
		return true;
	}

	return false;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (UNSIGNED INT)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, GLuint uintData)
{

	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniform1ui(ID, uintData);
		return true;
	}

	return false;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (FLOAT)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, GLfloat floatData)
{

	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniform1f(ID, floatData);
		return true;
	}

	return false;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (VEC2)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, const glm::vec2& vec2Data)
{

	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniform2fv(ID, 1, &vec2Data.x);
		return true;
	}

	return false;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (VEC3)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, const glm::vec3& vec3Data)
{

	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniform3fv(ID, 1, &vec3Data.x);
		return true;
	}

	return false;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (VEC4)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, const glm::vec4& vec4Data)
{

	GLint ID = GetUniformID(uniform);

	if (ID > -1)
	{
		glUniform4fv(ID, 1, &vec4Data.x);
		return true;
	}

	return false;

}
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (3x3 MATRIX)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, 
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
//------------------------------------------------------------------------------------------------------
//function that sends uniform data to shader (4x4 MATRIX)
//------------------------------------------------------------------------------------------------------
bool Shader::SendUniformData(const std::string& uniform, 
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
		Debug::Log("Shader program could not be created.", Debug::FAILURE);
		Debug::Log("===============================================================");
		Debug::PauseLog();
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
		Debug::Log("Vertex shader could not be created.", Debug::FAILURE);
		Debug::Log("===============================================================");
		Debug::PauseLog();
		return false;
	}
	
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (m_fragmentShaderID == 0)
	{
		Debug::Log("Fragment shader could not be created.", Debug::FAILURE);
		Debug::Log("===============================================================");
		Debug::PauseLog();
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that reads in the shader source code and compiles it
//------------------------------------------------------------------------------------------------------
bool Shader::CompileShader(const std::string& filename, ShaderType shaderType)
{

	//variables for file handling and reading of source code text
	std::fstream file;
	std::string lineText;
	std::string finalString;

	//display text to state that file is being opened and read
	std::string shaderString = (shaderType == VERTEX_SHADER) ? "vertex" : "fragment";
	Debug::Log("Opening and reading " + shaderString + " shader file: '" + filename + "'");

	//open shader file
	file.open(filename);

	//if file has an error opening output error message
	if (!file)
	{
		Debug::Log("Shader file could not be loaded.", Debug::FAILURE);
		Debug::Log("===============================================================");
		return false;
	}

	//based on which shader needs to be compiled point to specific 
	//shader ID so that when compiling later there is no duplicate code
	GLint tempShaderID = 0;
		
	switch (shaderType)
	{
		case VERTEX_SHADER: tempShaderID = m_vertexShaderID; break;
		case FRAGMENT_SHADER: tempShaderID = m_fragmentShaderID; break;
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
	Debug::Log("Compiling shader file...");

	//bind shader object with the shader source code
	glShaderSource(tempShaderID, 1, &finalCode, nullptr);

	//compile the source code using the shader object
	glCompileShader(tempShaderID);

	//request compilation error code for error checking
	GLint compileResult;
	glGetShaderiv(tempShaderID, GL_COMPILE_STATUS, &compileResult);

	//if compilation went well, display a friendly message
	if (compileResult == GL_TRUE)
	{
		Debug::Log("Shader file compiled successfully.", Debug::SUCCESS);
		Debug::Log("===============================================================");
	}

	//otherwise request error string and store in an 
	//array of a set size and display the error on screen
	else
	{
		GLchar error[1000];
		GLsizei length = 1000;

		Debug::Log("Shader file could not be compiled. See error list below.", Debug::FAILURE);
		Debug::Log("---------------------------------------------------------------");

		glGetShaderInfoLog(tempShaderID, 1000, &length, error);
		Debug::Log(error, Debug::FAILURE);
		Debug::Log("===============================================================");

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

		Debug::Log("Shader program could not be linked. See error list below.", Debug::FAILURE);
		Debug::Log("---------------------------------------------------------------");

		glGetProgramInfoLog(m_shaderProgramID, 1000, &length, error);
		Debug::Log(error, Debug::FAILURE);
		Debug::Log("===============================================================");

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