#pragma once

/*===================================================================#
| 'Quad' source files last updated on 29 June 2021                   |
#===================================================================*/

#include "Buffer.h"
#include "Object.h"
//#include "Material.h"
//#include "Texture.h"

//TODO - Add 'BoxCollider' component to the 'Quad' and 'Cuboid' classes

class Quad : public Object
{

public:

	Quad(GLfloat width = 1.0f, GLfloat height = 1.0f,
		GLfloat r = 0.5f, GLfloat g = 0.5f, GLfloat b = 0.5f, GLfloat a = 1.0f);
	virtual ~Quad();

	void SetDimension(const glm::vec2& dimension);
	void SetDimension(GLfloat width, GLfloat height);

	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	virtual void SendToShader() {}
	virtual void Update(GLfloat deltaTime) {}
	virtual void Render(Shader& shader);

private:

	Buffer m_buffer;
	//Texture m_texture;
	//Material m_material;

	glm::vec4 m_color;
	glm::vec2 m_dimension;

};