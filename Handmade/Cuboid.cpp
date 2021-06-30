#include "Cuboid.h"
#include "Input.h"

//======================================================================================================
Cuboid::Cuboid(GLfloat width, GLfloat height, GLfloat depth,
	GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_color = glm::vec4(r, g, b, a);
	m_dimension = glm::vec3(width, height, depth);

	glm::vec3 halfDimension = m_dimension * 0.5f;

	GLfloat vertices[] = { -halfDimension.x,  halfDimension.y,  halfDimension.z,
							halfDimension.x,  halfDimension.y,  halfDimension.z,
							halfDimension.x, -halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y,  halfDimension.z,       //Front face

							halfDimension.x,  halfDimension.y, -halfDimension.z,
						   -halfDimension.x,  halfDimension.y, -halfDimension.z,
						   -halfDimension.x, -halfDimension.y, -halfDimension.z,
							halfDimension.x, -halfDimension.y, -halfDimension.z,       //Back face

						   -halfDimension.x,  halfDimension.y, -halfDimension.z,
						   -halfDimension.x,  halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y, -halfDimension.z,       //Left face

							halfDimension.x,  halfDimension.y,  halfDimension.z,
							halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x, -halfDimension.y, -halfDimension.z,
							halfDimension.x, -halfDimension.y,  halfDimension.z,       //Right face

						   -halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y,  halfDimension.z,
						   -halfDimension.x,  halfDimension.y,  halfDimension.z,       //Top face

						   -halfDimension.x, -halfDimension.y,  halfDimension.z,
							halfDimension.x, -halfDimension.y,  halfDimension.z,
							halfDimension.x, -halfDimension.y, -halfDimension.z,
						   -halfDimension.x, -halfDimension.y, -halfDimension.z };    //Bottom face


	GLfloat colors[] = { r, g, b, a, r, g, b, a,
						 r, g, b, a, r, g, b, a,     //Front face 

						 r, g, b, a, r, g, b, a,
						 r, g, b, a, r, g, b, a,     //Back face

						 r, g, b, a, r, g, b, a,
						 r, g, b, a, r, g, b, a,     //Left face

						 r, g, b, a, r, g, b, a,
						 r, g, b, a, r, g, b, a,     //Right face

						 r, g, b, a, r, g, b, a,
						 r, g, b, a, r, g, b, a,     //Top face

						 r, g, b, a, r, g, b, a,
						 r, g, b, a, r, g, b, a };   //Bottom face


	GLfloat UVs[] = { 0.0f, 1.0f, 1.0f, 1.0f,
					  1.0f, 0.0f, 0.0f, 0.0f,      //Front face 

					  0.0f, 1.0f, 1.0f, 1.0f,
					  1.0f, 0.0f, 0.0f, 0.0f,	   //Back face

					  0.0f, 1.0f, 1.0f, 1.0f,
					  1.0f, 0.0f, 0.0f, 0.0f,	   //Left face

					  0.0f, 1.0f, 1.0f, 1.0f,
					  1.0f, 0.0f, 0.0f, 0.0f,	   //Right face

					  0.0f, 1.0f, 1.0f, 1.0f,
					  1.0f, 0.0f, 0.0f, 0.0f,	   //Top face

					  0.0f, 1.0f, 1.0f, 1.0f,
					  1.0f, 0.0f, 0.0f, 0.0f };    //Bottom face


	GLfloat normals[] = { 0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  
		                  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,      //Front face 

						   0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  
		                   0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,	    //Back face

						  -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, 
		                  -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,	    //Left face

						   1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  
		                   1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,	    //Right face

						   0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  
		                   0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,	    //Top face

						   0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  
		                   0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f };   //Bottom face


	GLuint indices[] = { 0,  1,  3,  3,  1,  2,      //Front face
						 4,  5,  7,  7,  5,  6,      //Back face 
						 8,  9, 11, 11,  9, 10,      //Left face
						12, 13, 15, 15, 13, 14,      //Right face
						16, 17, 19, 19, 17, 18,      //Top face
						20, 21, 23, 23, 21, 22 };    //Bottom face

	m_buffer.Create("Cuboid", 36, true);

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FILL_MANY);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::FILL_MANY);
	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::FILL_ONCE);
	m_buffer.FillVBO(Buffer::NORMAL_BUFFER, normals, sizeof(normals), Buffer::FILL_ONCE);
	m_buffer.FillEBO(indices, sizeof(indices), Buffer::FILL_ONCE);

	m_buffer.LinkEBO();

	//m_texture.Load("Crate_1.png");
	//m_material.SetMaterial("Chrome");
}
//======================================================================================================
Cuboid::~Cuboid()
{
	m_buffer.Destroy();
	//m_texture.Unload();
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
						 r, g, b, a, r, g, b, a };     //bottom face 

	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::FILL_MANY);
}
//======================================================================================================
void Cuboid::SetDimension(const glm::vec3& dimension)
{
	SetDimension(dimension.x, dimension.y, dimension.z);
}
//======================================================================================================
void Cuboid::SetDimension(GLfloat width, GLfloat height, GLfloat depth)
{
	m_dimension = glm::vec3(width, height, depth);
	glm::vec3 halfDimension = m_dimension * 0.5f;

	GLfloat vertices[] = { -halfDimension.x,  halfDimension.y,  halfDimension.z,
							halfDimension.x,  halfDimension.y,  halfDimension.z,
							halfDimension.x, -halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y,  halfDimension.z,       //Front face

						   -halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x, -halfDimension.y, -halfDimension.z,
						   -halfDimension.x, -halfDimension.y, -halfDimension.z,       //Back face

						   -halfDimension.x,  halfDimension.y, -halfDimension.z,
						   -halfDimension.x,  halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y, -halfDimension.z,       //Left face

							halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y,  halfDimension.z,
							halfDimension.x, -halfDimension.y,  halfDimension.z,
							halfDimension.x, -halfDimension.y, -halfDimension.z,       //Right face

						   -halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y, -halfDimension.z,
							halfDimension.x,  halfDimension.y,  halfDimension.z,
						   -halfDimension.x,  halfDimension.y,  halfDimension.z,       //Top face

						   -halfDimension.x, -halfDimension.y, -halfDimension.z,
							halfDimension.x, -halfDimension.y, -halfDimension.z,
							halfDimension.x, -halfDimension.y,  halfDimension.z,
						   -halfDimension.x, -halfDimension.y,  halfDimension.z };    //Bottom face

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FILL_MANY);
}
//======================================================================================================
//void Cuboid::Update(GLfloat deltaTime)
//{
//	glm::ivec2 mouseWheel = Input::Instance()->GetMouseWheel();
//	glm::ivec2 mouseMotion = Input::Instance()->GetMouseMotion();
//
//	if (Input::Instance()->IsLeftButtonDown())
//	{
//		m_transform.Rotate(static_cast<GLfloat>(mouseMotion.y), 0, 0, Transform::Space::GLOBAL);
//		m_transform.Rotate(0, static_cast<GLfloat>(mouseMotion.x), 0, Transform::Space::LOCAL);
//	}
//
//	/*static GLfloat zoomDistance = 0.0f;
//	zoomDistance += static_cast<GLfloat>(mouseWheel.y);
//	zoomDistance = glm::clamp(zoomDistance, -5.0f, 1.0f);
//	m_transform.SetPosition(0.0f, 0.0f, zoomDistance);*/
//}
//======================================================================================================
void Cuboid::Render(Shader& shader)
{
	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("textureIn"), Buffer::TEXTURE_BUFFER, Buffer::UV, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("normalIn"), Buffer::NORMAL_BUFFER, Buffer::XYZ, Buffer::FLOAT);

	//m_material.SendToShader(shader);

	m_normalMatrix = glm::inverse(glm::mat3(m_transform.GetMatrix()));

	shader.SendData("normal", m_normalMatrix);
	shader.SendData("model", m_transform.GetMatrix());
	shader.SendData("isTextured", static_cast<GLuint>(m_isTextured));

	//m_texture.Bind();
	m_buffer.Render(Buffer::TRIANGLES);
	//m_texture.Unbind();
}