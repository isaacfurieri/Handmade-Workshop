#include "Input.h"
#include "Quad.h"

//======================================================================================================
Quad::Quad(GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_dimension = glm::vec2(width, height);

	glm::vec2 halfDimension = m_dimension * 0.5f;

	GLfloat vertices[] = { -halfDimension.x,  halfDimension.y, 0.0f,
							halfDimension.x,  halfDimension.y, 0.0f,
							halfDimension.x, -halfDimension.y, 0.0f,
						   -halfDimension.x, -halfDimension.y, 0.0f };

	GLfloat colors[] = { r, g, b, a,
						 r, g, b, a,
						 r, g, b, a,
						 r, g, b, a };

	GLfloat UVs[] = { 0.0f, 1.0f,
					  1.0f, 1.0f,
					  1.0f, 0.0f,
					  0.0f, 0.0f };

	GLfloat normals[] = { 0.0f, 0.0f, 1.0f,
						  0.0f, 0.0f, 1.0f,
						  0.0f, 0.0f, 1.0f,
						  0.0f, 0.0f, 1.0f };

	GLuint indices[] = { 0, 1, 3,
						 3, 1, 2 };

	//TODO - Find a way to only create one single 
	//buffer to be shared amongst subsequent quads
	m_buffer.Create("Quad", 6, true);

	m_buffer.LinkEBO();
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FILL_ONCE);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::FILL_ONCE);
	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::FILL_ONCE);
	m_buffer.FillVBO(Buffer::NORMAL_BUFFER, normals, sizeof(normals), Buffer::FILL_ONCE);
	m_buffer.FillEBO(indices, sizeof(indices), Buffer::FILL_ONCE);
}
//======================================================================================================
Quad::~Quad()
{
	m_buffer.Destroy();
}
//======================================================================================================
void Quad::SetDimension(const glm::vec2& dimension)
{
	SetDimension(dimension.x, dimension.y);
}
//======================================================================================================
void Quad::SetDimension(GLfloat width, GLfloat height)
{
	glm::vec2 halfDimension = glm::vec2(width * 0.5f, height * 0.5f);

	GLfloat vertices[] = { -halfDimension.x,  halfDimension.y, 0.0f,
							halfDimension.x,  halfDimension.y, 0.0f,
							halfDimension.x, -halfDimension.y, 0.0f,
						   -halfDimension.x, -halfDimension.y, 0.0f };

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FILL_MANY);
}
//======================================================================================================
void Quad::SetTextureScale(GLfloat width, GLfloat height)
{
	GLfloat UVs[] = { 0.0f, 0.0f,
					  width, 0.0f,
					  width, height,
					  0.0f, height };

	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::FILL_MANY);
}
//======================================================================================================
void Quad::SetColor(const glm::vec4& color)
{
	SetColor(color.r, color.g, color.b, color.a);
}
//======================================================================================================
void Quad::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	GLfloat colors[] = { r, g, b, a,
						 r, g, b, a,
						 r, g, b, a,
						 r, g, b, a };

	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::FILL_MANY);
}
//======================================================================================================
void Quad::Render(Shader& shader)
{
	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("textureIn"), Buffer::TEXTURE_BUFFER, Buffer::UV, Buffer::FLOAT);
	//m_buffer.LinkVBO(shader.GetAttributeID("normalIn"), Buffer::NORMAL_BUFFER, Buffer::XYZ, Buffer::FLOAT);

	//m_normalMatrix = glm::inverse(glm::mat3(m_transform.GetMatrix()));
	//shader.SendData("normal", m_normalMatrix);

	shader.SendData("model", m_transform.GetMatrix());
	shader.SendData("isTextured", static_cast<GLuint>(m_isTextured));

	//shader.SendData("isText", false);
	shader.SendData("isTextured", false);

	m_buffer.Render(Buffer::TRIANGLES);
}