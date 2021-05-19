#ifndef MODEL_H
#define MODEL_H

/*==============================================================================================#
|                                                                                               |
| All code has been written by Karsten Vermeulen as part of the 'Handmade' game engine, for the |
| purposes of educating other fellow programmers, programming students and anyone else wishing  |
| to learn about game development, C++ and OOP. The engine, class design and overall structure  |
| is by no means perfect and there is certainly room for improvement. Feel free to use, copy,   |
| break, update and do as you wish with this code - it is there, free, for all!                 |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|																								|
| If you like 'Handmade', and wish to show your support, if you have any questions about the    |
| project, or if you just want to reach out, please find me on the following channels:          |
|																						        |
| Web: http://www.karstenvermeulen.com														    |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'Model' source files last updated in December 2019					    			        |
#==============================================================================================*/

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

#endif