/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This class represents a 3D model that can be loaded from an OBJ and MTL file and then rendered
  on screen. Any 3rd party 3D modelling application can be used to produce a OBJ/MTL file combo,
  which will be read in by the class and all values stored accordingly. The OBJ file should store
  all the raw model vertex, texture coordinate and normal data, which will be read in, filtered 
  and stored in the class' properties variables. The MTL file should have all the lighting and
  material data needed for the model which will also be stored and used correctly. The model's 
  accompanying texture needs to be separately loaded and assigned to the model's texture ID.
 
- There is a struct that encapsulates a material grouping for all the material data read in from
  the MTL file. There may be many materials needed, so essentially the Model class will store
  a map of these materials. There are some additional structs that still need to be implemented
  accordingly <TBA>

- The setter functions will set the specific properties of the model. The SetShaderAttribute()
  function is there to be able to link the shader attribute variables with the model data via the
  internal Buffer object. The SetBufferID() function is able to link the model's internal buffer
  with the correct vertex, color and texture VBO. The SetTextureID() routine is used to assign an 
  OpenGL texture ID to the model object. This ID is requested from the Texture Manager.

- All the raw model data loading occurs in the LoadFromFile() routine, where each line of text
  in the OBJ and MTL files are read and filtered. Based on what tokens precede the lines of text,
  the function will convert and store all the values accordingly. The raw data after being sorted
  is then stored in the internal buffer's data vectors before being sent to the respective VBOs
  to be filled. Unlike the Sprite class, all vertex data is loaded and filled once when the model
  is loaded. Therefore in the client code the model's VBOs need to be set before the LoadFromFile()
  function is called.

- There is a private ParseString() routine that takes in a long string of text and breaks it down
  into smaller chunks based on what token is needed to separate the text chunks. This function is
  used internally in the LoadFromFile() routine in order to break down text strings read in from 
  the OBJ and MTL files in order to store all values accordingly. This function is never used 
  externally.

- The Model class implementation is slightly different to the Sprite class counterpart. There are
  a few changes that still need to be made later on!

- This class will be updated soon!

*/

#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <string>
#include <vector>
#include <glew.h>
#include <glm.hpp>
#include "Buffer.h"
#include "Color.h"

//------------------------------------------------------------------------------------------------------
//struct to store all material data for the model
//------------------------------------------------------------------------------------------------------

struct Material
{

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 emission;

	GLuint illum;
	GLfloat shininess;
	
	Material()
	{
		shininess = 0.0f;
		illum = 0;
	}

};

//------------------------------------------------------------------------------------------------------
//struct to store index values for each triangle face
//------------------------------------------------------------------------------------------------------

struct Face
{
	glm::vec3 vertexArray[3];
};

//------------------------------------------------------------------------------------------------------
//struct to store all data for a group of vertices
//------------------------------------------------------------------------------------------------------
struct Group
{

	std::string materialName;
	std::vector<Face> faces;

	Group()
	{
		materialName = "";
	}

};

//------------------------------------------------------------------------------------------------------
//Model class declaration begins here
//------------------------------------------------------------------------------------------------------

class Model
{

public:

	Model();

public:

	void SetColor(Color& color);
	void SetTextureID(const std::string& mapIndex);
	void SetBufferID(const std::string& vertexID, const std::string& colorID,
		             const std::string& textureID, const std::string& normalID);
	void SetShaderAttribute(const std::string& vertexAttr, const std::string& colorAttr,
		                    const std::string& textureAttr, const std::string& normalAttr);

public:

	bool LoadFromFile(const std::string& OBJfilename, const std::string& MTLfilename);
	void Draw();

private:

	Color m_color;
	Buffer m_buffer;
	GLuint m_textureID;

	std::map<std::string, Material*> m_materials;

};

#endif