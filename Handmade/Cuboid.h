#pragma once

/*===================================================================#
| 'Cuboid' source files last updated on 7 July 2021                  |
#===================================================================*/

#include "Buffer.h"
#include "Object.h"
//#include "Material.h"
//#include "Texture.h"

//TODO - Add 'BoxCollider' component to the 'Quad' and 'Cuboid' classes

class Cuboid : public Object
{

public:

	Cuboid(GLfloat width = 1.0f, GLfloat height = 1.0f, GLfloat depth = 1.0f,
		GLfloat r = 0.5f, GLfloat g = 0.5f, GLfloat b = 0.5f, GLfloat a = 1.0f);
	virtual ~Cuboid();

	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	void SetDimension(const glm::vec3& dimension);
	void SetDimension(GLfloat width, GLfloat height, GLfloat depth);

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader) {}

private:

	Buffer m_buffer;
	//Texture m_texture;
	//Material m_material;

	glm::vec4 m_color;
	glm::vec3 m_dimension;

};