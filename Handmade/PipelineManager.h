/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This is a Singleton Manager class that controls the main shader program and all of its shader
  objects. It can create and destroy multiple vertex, fragment and geometry shaders and manage
  their components accordingly. Shaders can be attached and detatched at any time to allow for
  multiple shaders to be used in the client code. The manager class has an ID for the main shader
  program and three maps of IDs, each for the vertex, fragment and geometry shaders.

- The getters and setters allow access to the different shader variables. There is a getter that
  allows us to get the ID of a specific vertex attribute. 
  
- There are also various functions that allow us to pass uniform or vertex attribute data to the
  shaders. Simply pass the functions the name of the shader variable and the data to pass and the
  manager will pass that data through. 
  
- The main functions in the class allow for the main shader program to be created and initialised
  as well as allowing various shaders to be created, compiled, linked, attached, destroyed etc.
  For each main function there is a correponding opposing routine, ie Initialize() and its
  counterpart ShutDown(). However, there is no Unlink() routine for the Link() function. To
  use different shaders with the current shader program, simply detach the shaders and attach the
  new shaders before linking them. The shaders need to be attached before they are linked with
  the main program.

- An Output() routine is there for debug purposes only and will print to the console how many
  shader IDs are currently stored in the various shader ID maps.

- TODO : Before passing data to the shaders, first check that the shader variable exists!

*/

#ifndef PIPELINE_MANAGER_H
#define PIPELINE_MANAGER_H

#include <string>
#include "glad.h"
#include <glm.hpp>
#include "Singleton.h"

class PipelineManager
{

public:

	enum RenderType { POLYGON_MODE, FULL_SHADE };
	enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER };
	
public:

	friend class Singleton<PipelineManager>;

public:

	void SetRenderType(RenderType renderType);
	GLuint GetShaderAttribute(const std::string& vertAttrib);
	
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

	bool SendAttributeData(const std::string& attribute, GLfloat floatData);
	bool SendAttributeData(const std::string& attribute, const glm::vec2& vec2Data);
	bool SendAttributeData(const std::string& attribute, const glm::vec3& vec3Data);
	bool SendAttributeData(const std::string& attribute, const glm::vec4& vec4Data);

public:

	bool CreateProgram();
	bool CreateShaders();

	bool CompileShader(ShaderType shaderType, const std::string& filename);
	void AttachShaders();
	bool LinkProgram();
	
	void DetachShaders();
	void DestroyShaders();
	void DestroyProgram();

private:

	PipelineManager();
	PipelineManager(const PipelineManager&);
	PipelineManager& operator=(PipelineManager&);

private:

	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

};

typedef Singleton<PipelineManager> ThePipeline;

#endif