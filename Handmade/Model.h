/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This class represents a 3D model that can be loaded from an OBJ and MTL file and then rendered
  on screen. Any 3rd party 3D modelling application can be used to produce a OBJ/MTL file combo,
  which will be read in by the class and all values stored accordingly. The OBJ file should store
  all the raw model vertex, texture coordinate and normal data, which will be read in, filtered
  and stored in the class' properties variables. The MTL file should have all the lighting and
  material data needed for the model which will also be stored and used correctly. The model's
  accompanying texture needs to be separately loaded and assigned to the model's texture ID.

- The setter functions will set the specific properties of the model. The SetBuffer() function 
  is able to link the model's internal buffer with the correct vertex, color and texture VBO.
  The SetTexture() routine is used to assign an OpenGL texture ID to the model object. This ID
  is requested from the Texture class.

- All the raw model data loading occurs in the LoadModel() routine, where each line of text
  in the OBJ and MTL files are read and filtered. Based on what tokens precede the lines of text,
  the function will convert and store all the values accordingly. The raw data after being sorted
  is then stored in the internal buffer's data vectors before being sent to the respective VBOs
  to be filled. 

- The Model class implementation is slightly different to the Sprite class counterpart. There are
  a few changes that still need to be made later on!

- PLEASE NOTE : Current support for MTL files is temporarily halted and this model class ONLY
  loads in the OBJ files. More on this later! There are many improvements still being done to this
  class...

*/

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "glad.h"
#include <glm.hpp>
#include "Buffer.h"
#include "Material.h"
#include "Texture.h"

//struct to store all three components of a vertex group, which is
//the grouping of verts, UVs and norms for each point in a triangle
struct Groups
{
	glm::vec3 vertex;
	glm::vec2 texture;
	glm::vec3 normal;
};

class Model
{

public:

	void SetShininess(GLfloat shininess);

	void SetBuffer(const std::string bufferID);
	void SetTexture(const std::string textureID);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

public:

	bool LoadModel(const std::string& filename, const std::string bufferID);
	bool LoadTexture(const std::string& filename, const std::string textureID);
	void UnloadModel(const std::string bufferID);
	void UnloadTexture(const std::string textureID);

public:

	void Draw();

private:

	std::vector<GLuint> m_indices;
	std::vector<Groups> m_groups;

	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_colors;
	std::vector<GLfloat> m_normals;
	std::vector<GLfloat> m_textures;

	Buffer m_buffer;
	Texture m_texture;
	Material m_material;

};

#endif