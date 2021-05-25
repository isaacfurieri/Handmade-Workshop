#include "Cuboid.h"
#include "Shader.h"

//======================================================================================================
Cuboid::Cuboid(GLfloat width, GLfloat height, GLfloat depth, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_color = glm::vec4(r, g, b, a);
	m_dimension = glm::vec3(width, height, depth);
}
//======================================================================================================
void Cuboid::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	GLfloat colors[] = { r, g, b, a, r, g, b, a,
						 r, g, b, a, r, g, b, a,       //front face 
						 r, g, b, a, r, g, b, a,
						 r, g, b, a, r, g, b, a,       //back face 
						 r, g, b, a, r, g, b, a,
						 r, g, b, a, r, g, b, a,       //left face 
						 r, g, b, a, r, g, b, a,
						 r, g, b, a, r, g, b, a,       //right face 
						 r, g, b, a, r, g, b, a,
						 r, g, b, a, r, g, b, a,       //top face 
						 r, g, b, a, r, g, b, a,
						 r, g, b, a, r, g, b, a };   //bottom face 

	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);
}
//======================================================================================================
void Cuboid::SetDimension(GLfloat width, GLfloat height, GLfloat depth)
{
	//we need to halve the dimensions of the cuboid so 
	//that all vertices span out from the centre point
	glm::vec3 halfDimension = glm::vec3(width * 0.5f, height * 0.5f, depth * 0.5f);

	//data that represents vertices for cuboid 
	GLfloat vertices[] = { -halfDimension.x,  halfDimension.y,  halfDimension.z,
							halfDimension.x,  halfDimension.y,  halfDimension.z,
							halfDimension.x, -halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y,  halfDimension.z,       //front face

						   -halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x, -halfDimension.y, -halfDimension.z,
						   -halfDimension.x, -halfDimension.y, -halfDimension.z,       //back face

						   -halfDimension.x,  halfDimension.y, -halfDimension.z,
						   -halfDimension.x,  halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y, -halfDimension.z,       //left face

							halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y,  halfDimension.z,
							halfDimension.x, -halfDimension.y,  halfDimension.z,
							halfDimension.x, -halfDimension.y, -halfDimension.z,       //right face

						   -halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y,  halfDimension.z,
						   -halfDimension.x,  halfDimension.y,  halfDimension.z,       //top face

						   -halfDimension.x, -halfDimension.y, -halfDimension.z,
							halfDimension.x, -halfDimension.y, -halfDimension.z,
							halfDimension.x, -halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y,  halfDimension.z };    //bottom face

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
}
//======================================================================================================
bool Cuboid::Create()
{
	//create VAO and VBOs and based on the maximum amount of vertices needed
	//A cube needs 36 vertices for the 6 faces (2x triangles) it consists of
	if (!m_buffer.CreateBuffers("CUBOID", 36, true))
	{
		return false;
	}

	//bind all VBOs and shader attributes together with VAO
	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGBA, Buffer::FLOAT);

	//we need to halve the dimensions of the cuboid so 
	//that all vertices span out from the centre point
	glm::vec3 halfDimension = m_dimension * 0.5f;

	//data that represents vertices for cuboid 
	GLfloat vertices[] = { -halfDimension.x,  halfDimension.y,  halfDimension.z,
							halfDimension.x,  halfDimension.y,  halfDimension.z,
							halfDimension.x, -halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y,  halfDimension.z,       //front face

						   -halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x, -halfDimension.y, -halfDimension.z,
						   -halfDimension.x, -halfDimension.y, -halfDimension.z,       //back face

						   -halfDimension.x,  halfDimension.y, -halfDimension.z,
						   -halfDimension.x,  halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y, -halfDimension.z,       //left face

							halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y,  halfDimension.z,
							halfDimension.x, -halfDimension.y,  halfDimension.z,
							halfDimension.x, -halfDimension.y, -halfDimension.z,       //right face

						   -halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y,  halfDimension.z,
						   -halfDimension.x,  halfDimension.y,  halfDimension.z,       //top face

						   -halfDimension.x, -halfDimension.y, -halfDimension.z,
							halfDimension.x, -halfDimension.y, -halfDimension.z,
							halfDimension.x, -halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y,  halfDimension.z };    //bottom face


	//data that represents colors for Cuboid
	GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,		  //front face 

						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,		  //back face 

						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,		  //left face 

						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,		  //right face 

						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,		  //top face 

						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a };      //bottom face 

	//data that represents normals for cuboid 
	GLfloat normals[] = { 0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
						  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,	          //front face		 
						  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,
						  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,		      //back face
						 -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
						 -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,		      //left face
						  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
						  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,		      //right face
						  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
						  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,		      //top face
						  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
						  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f };   	      //bottom face

	//data that represents indices for vertex and color data for Cuboid
	GLuint indices[] = { 0,  1,  3,  3,  1,  2,       //front face
						 4,  5,  7,  7,  5,  6,       //back face 
						 8,  9, 11, 11,  9, 10,       //left face
						12, 13, 15, 15, 13, 14,       //right face
						16, 17, 19, 19, 17, 18,       //top face
						20, 21, 23, 23, 21, 22 };    //bottom face

	//create VBOs and fill them with the vertex and color data 
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);
	m_buffer.FillEBO(indices, sizeof(indices), Buffer::STATIC_FILL);
}
//======================================================================================================
void Cuboid::Draw()
{
	SendToShader(false, false);
	m_buffer.Draw(Buffer::TRIANGLES);
}
//======================================================================================================
void Cuboid::Destroy()
{
	m_buffer.DestroyBuffers("CUBOID");
}