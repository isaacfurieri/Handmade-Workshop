/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

  -----------------------------------------------------------------------------------------------

- This is a Singleton Manager class that controls the main shader program and all of its shader 
  objects. It can create and destroy multiple vertex, fragment and geometry shaders and manage
  their components accordingly. Shaders can be attached and detatched at any time to allow for
  multiple shaders to be used in the client code. The manager class has an ID for the main shader
  program and three maps of IDs, each for the vertex, fragment and geometry shaders.

- Two enum types have been created. The RemoveType enum is used when removing shader IDs from the
  map. Either one single specific shader ID can be removed, or the entire map of shaders can be 
  cleared. The ShaderType enum is there for letting the manager class know what type of shader it 
  will de dealing with.

- The getters and setters allow access to the different shader variables. There are two getter 
  routines for aquiring the IDs of the uniform and attribute variables from inside the shaders. 
  There are also a few setter functions that allow data to be sent to the shader uniform and 
  attribute variables. Some of these routines are overloaded so that different types of data can
  be sent to the shaders. 
  
- The main functions in the class allow for the main shader program to be created and initialised
  as well as allowing various shaders to be created, compiled, linked, attached, destroyed etc.
  For each main function there is a correponding opposing routine, ie Initialize() and its 
  counterpart ShutDown(). However, there is no Unlink() routine for the Link() function. To 
  use different shaders with the current shader program, simply detach the shaders and attach the
  new shaders before linking them. The shaders need to be attached before they are linked with
  the main program. 

- An Output() routine is there for debug purposes only and will print to the console how many 
  shader IDs are currently stored in the various shader ID maps.

*/

#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <map>
#include <string>
#include <glew.h>
#include <glm.hpp>
#include "Singleton.h"

class ShaderManager
{

public :

	enum RemoveType { CUSTOM_SHADER, ALL_SHADERS };
	enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };

public:

	friend class Singleton<ShaderManager>;

public:

	GLuint GetShaderProgram();
	GLint GetUniformID(const std::string& name);
	GLint GetAttributeID(const std::string& name);
	
	void SetUniformData(GLint attributeID, GLint data);
	void SetUniformData(GLint attributeID, GLfloat data);
	void SetUniformData(GLint attributeID, glm::vec3& data);
	void SetUniformMatrix(GLint attributeID, GLfloat* matrix);
	void SetAttribute(GLint attributeID, GLint componentSize);

public:

	void EnableAttribute(GLint attributeID);
	void DisableAttribute(GLint attributeID);

public:

	bool Initialize();
	bool Create(ShaderType shaderType, const std::string& mapIndex);
	void Attach(ShaderType shaderType, const std::string& mapIndex);

public :

	bool Compile(ShaderType shaderType, const std::string& filename, const std::string& mapIndex);
	bool Link();
	
public:

	void Detach(ShaderType shaderType, const std::string& mapIndex);
	void Destroy(ShaderType shaderType, RemoveType removeType, const std::string& mapIndex = "");
	void ShutDown();

public :

	void Output();

private:

	ShaderManager();
	ShaderManager(const ShaderManager&);
	ShaderManager& operator=(const ShaderManager&);

private:

	GLint m_shaderProgramID;

	std::map<std::string, GLuint> m_vertexShaderIDMap;
	std::map<std::string, GLuint> m_fragmentShaderIDMap;
	std::map<std::string, GLuint> m_geometryShaderIDMap;

};

typedef Singleton<ShaderManager> TheShader;

#endif