#include "Input.h"
#include "Quad.h"

//======================================================================================================
Quad::Quad(GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_color = glm::vec4(r, g, b, a);
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

	m_buffer.Create("Quad", 6, true);

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FILL_ONCE);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::FILL_ONCE);
	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::FILL_ONCE);
	//m_buffer.FillVBO(Buffer::NORMAL_BUFFER, normals, sizeof(normals), Buffer::FILL_ONCE);
	m_buffer.FillEBO(indices, sizeof(indices), Buffer::FILL_ONCE);

	m_buffer.LinkEBO();

	//m_texture.Load("Compass.png");
	//m_material.SetMaterial("Chrome");
}
//======================================================================================================
Quad::~Quad()
{
	m_buffer.Destroy();
	//m_texture.Unload();
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
void Quad::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	GLfloat colors[] = { r, g, b, a,
						 r, g, b, a,
						 r, g, b, a,
						 r, g, b, a };

	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::FILL_MANY);
}
//======================================================================================================
//void Quad::Update()
//{
//	/*glm::ivec2 mouseWheel, mouseMotion;
//	Input::Instance()->GetMouseWheel(mouseWheel.x, mouseWheel.y);
//	Input::Instance()->GetMouseMotion(mouseMotion.x, mouseMotion.y);
//
//	if (Input::Instance()->IsLeftButtonClicked())
//	{
//		m_transform.Rotate(static_cast<GLfloat>(mouseMotion.y), 0, 0, Transform::Space::GLOBAL);
//		m_transform.Rotate(0, static_cast<GLfloat>(mouseMotion.x), 0, Transform::Space::LOCAL);
//	}
//
//	static GLfloat zoomDistance = 0.0f;
//	zoomDistance += static_cast<GLfloat>(mouseWheel.y);
//	zoomDistance = glm::clamp(zoomDistance, -5.0f, 1.0f);
//	m_transform.SetPosition(0.0f, 0.0f, zoomDistance);*/
//}
//======================================================================================================
void Quad::Render(Shader& shader)
{
	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("textureIn"), Buffer::TEXTURE_BUFFER, Buffer::UV, Buffer::FLOAT);
	//m_buffer.LinkVBO(shader.GetAttributeID("normalIn"), Buffer::NORMAL_BUFFER, Buffer::XYZ, Buffer::FLOAT);

	//m_normalMatrix = glm::inverse(glm::mat3(m_transform.GetMatrix()));

	//m_material.SendToShader(shader);

	//shader.SendData("normal", m_normalMatrix);
	shader.SendData("model", m_transform.GetMatrix());
	//shader.SendData("isTextured", static_cast<GLuint>(m_isTextured));

	//shader.SendData("isText", false);
	shader.SendData("isTextured", false);

	//m_texture.Bind();
	m_buffer.Render(Buffer::TRIANGLES);
	//m_texture.Unbind();
}