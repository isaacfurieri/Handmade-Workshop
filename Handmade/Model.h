#pragma once

/*===================================================================#
| 'Model' source files last updated on 19 May 2021                   |
#===================================================================*/

#include <string>
#include <vector>
#include "glad.h"
#include <glm.hpp>
#include "Buffer.h"
#include "Material.h"
#include "Texture.h"

//TODO - Refine class such that it follows newer design

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