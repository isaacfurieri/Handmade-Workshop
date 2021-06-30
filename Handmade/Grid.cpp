#include "Grid.h"
#include "Input.h"
#include "Shader.h"

//======================================================================================================
Grid::Grid(GLint size, GLfloat lineWidth)
{
	m_size = size;
	m_lineWidth = lineWidth;

	//The offset will add up and keep track of 
	//how many bytes are added to the VBOs
	GLuint offsetColor = 0;
	GLuint offsetVertex = 0;

	const int QUADRANTS = 4;
	const int BYTES_PER_VERTEX = 3 * sizeof(GLint);
	const int BYTES_PER_COLOR = 4 * sizeof(GLfloat);

	//Each quadrant in the grid will have an amount of lines and
	//each line has 2 vertices, each vertex has an XYZ component
	const int TOTAL_BYTES_VERTEX_VBO = (m_size + 1) * QUADRANTS * BYTES_PER_VERTEX * 2;
	const int TOTAL_BYTES_COLOR_VBO = (m_size + 1) * QUADRANTS * BYTES_PER_COLOR * 2;

	//We multiply by 2 to represent each line's vertex 
	//and add 4 for the two extra lines to close the grid
	m_buffer.Create("Grid", (m_size * QUADRANTS * 2) + 4);

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, (GLfloat*)nullptr, TOTAL_BYTES_VERTEX_VBO, Buffer::FILL_ONCE);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, (GLfloat*)nullptr, TOTAL_BYTES_COLOR_VBO, Buffer::FILL_ONCE);

	//==================================
	//Negative X lines
	//==================================

	for (int i = 0; i <= m_size; i++)
	{
		GLint vertices[] = { -m_size + i, 0,  m_size,      //first vertex
							 -m_size + i, 0, -m_size };    //second vertex

		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX * 2;
		offsetColor += BYTES_PER_COLOR * 2;
	}

	//==================================
	//Positive X lines
	//==================================

	for (int i = 1; i < m_size + 1; i++)
	{
		GLint vertices[] = { 0 + i, 0,  m_size,      //first vertex
							 0 + i, 0, -m_size };    //second vertex

		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX * 2;
		offsetColor += BYTES_PER_COLOR * 2;
	}

	//==================================
	//Negative Z lines
	//==================================

	for (int i = 0; i <= m_size; i++)
	{
		GLint vertices[] = { -m_size, 0, -m_size + i,        //first vertex
							  m_size, 0, -m_size + i };     //second vertex

		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX * 2;
		offsetColor += BYTES_PER_COLOR * 2;
	}

	//==================================
	//Positive Z lines
	//==================================

	for (int i = 1; i < m_size + 1; i++)
	{
		GLint vertices[] = { -m_size, 0, 0 + i,     //first vertex
							  m_size, 0, 0 + i };     //second vertex

		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_VERTEX * 2;
		offsetColor += BYTES_PER_COLOR * 2;
	}
}
//======================================================================================================
Grid::~Grid()
{
	m_buffer.Destroy();
}
//======================================================================================================
void Grid::SetSize(GLint size)
{
	m_size = size;
}
//======================================================================================================
void Grid::SetLineWidth(GLfloat lineWidth)
{
	m_lineWidth = lineWidth;
}
//======================================================================================================
void Grid::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	//The offset will add up and keep track of 
	//how many bytes are added to the VBOs
	GLuint offset = 0;

	//Loop through all elements in color VBO and fill with the RGB 
	//values. We multiply grid size by 4 to account for the quadrants 
	for (int i = 0; i < m_size * 4; i++)
	{
		GLfloat colors[] = { r, g, b, a, r, g, b, a };

		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offset);
		offset += sizeof(colors);
	}
}
//======================================================================================================
//Transform& Grid::GetTransform()
//{
//	return m_transform;
//}
//======================================================================================================
//void Grid::Update()
//{
//	glm::ivec2 mouseWheel = Input::Instance()->GetMouseWheel();
//	glm::ivec2 mouseMotion = Input::Instance()->GetMouseMotion();
//
//	//We accumulate the x and y euler rotation angles to be built into a quaternion later 
//	if (Input::Instance()->IsLeftButtonDown())
//	{
//		m_transform.Rotate(static_cast<GLfloat>(mouseMotion.y), 0, 0, Transform::Space::GLOBAL);
//		m_transform.Rotate(0, static_cast<GLfloat>(mouseMotion.x), 0, Transform::Space::LOCAL);
//		//m_eulerAngles.x += mouseMotion.y;
//		//m_eulerAngles.y += mouseMotion.x;
//	}
//}
//======================================================================================================
void Grid::Render(Shader& shader)
{
	Buffer::SetLineWidth(m_lineWidth);

	//m_transform.SetRotation(m_eulerAngles);

	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::INT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);

	shader.SendData("isTextured", false);
	shader.SendData("model", m_transform.GetMatrix());

	m_buffer.Render(Buffer::LINES);
}

//=======================================================================================================
//OLD code to generate a 2D Grid (taken from Grid2D.cpp)
//=======================================================================================================

//bool Grid2D::Create()
//{
//
//	//the offset will add up and keep track of 
//	//how many bytes are added to the VBOs
//	GLuint offsetColor = 0;
//	GLuint offsetVertex = 0;
//
//	//constants to help clarify different calculations below
//	const int QUADRANTS = 4;
//	const int BYTES_PER_VERTEX = 2 * sizeof(GLint);
//	const int BYTES_PER_COLOR = 4 * sizeof(GLfloat);
//
//	//pre-calculate the total amount of bytes needed for the VBOs  
//	//the vertex VBO has 2 vertices, each one with an XY component
//	//the color VBO also has 2 vertices, each with a RGBA component
//	const int TOTAL_BYTES_VERTEX_VBO = m_size * QUADRANTS * BYTES_PER_VERTEX * 2;
//	const int TOTAL_BYTES_COLOR_VBO = m_size * QUADRANTS * BYTES_PER_COLOR * 2;
//
//	//create VAO and VBOs which is based on the total amount of
//	//lines and quadrants and multiplied by 2 to represent each vertex
//	if (!m_buffer.CreateBuffers("GRID_2D", m_size * QUADRANTS * 2))
//	{
//		return false;
//	}
//
//	//bind all VBOs and shader attributes together with VAO
//	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XY, Buffer::INT);
//	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGBA, Buffer::FLOAT);
//
//	//create empty VBOs to be filled below 
//	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, (GLint*)nullptr, TOTAL_BYTES_VERTEX_VBO, Buffer::STATIC_FILL);
//	m_buffer.FillVBO(Buffer::COLOR_BUFFER, (GLfloat*)nullptr, TOTAL_BYTES_COLOR_VBO, Buffer::STATIC_FILL);
//
//	//first pre-calculate the pixels per unit based on screen setup
//	GLint pixelsPerUnit = Screen::Instance()->GetPixelsPerUnit();
//
//	//now we create the grid one quadrant at a time	and fill each vertex and
//	//color VBO with the line's vertex and color data accordingly. The offset
//	//will get updated each iteration and keep track of how many bytes into
//	//each VBO we already are in order to fill the VBOs in the right place
//
//	//**********************************
//	//create all negative X lines
//	//**********************************
//
//	for (int i = 0; i < m_size; i++)
//	{
//
//		GLint vertices[] = { (-m_size * pixelsPerUnit) + (i * pixelsPerUnit),
//							 (-m_size * pixelsPerUnit),                            //first vertex
//							 (-m_size * pixelsPerUnit) + (i * pixelsPerUnit),
//							   m_size * pixelsPerUnit };                           //second vertex
//
//		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
//
//		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
//		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);
//
//		offsetVertex += BYTES_PER_VERTEX * 2;
//		offsetColor += BYTES_PER_COLOR * 2;
//
//	}
//
//	//**********************************
//	//create all positive X lines
//	//**********************************
//
//	for (int i = 1; i < m_size + 1; i++)
//	{
//
//		GLint vertices[] = { 0 + (i * pixelsPerUnit), -m_size * pixelsPerUnit,     //first vertex
//							 0 + (i * pixelsPerUnit),  m_size * pixelsPerUnit };  //second vertex
//
//		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
//
//		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
//		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);
//
//		offsetVertex += BYTES_PER_VERTEX * 2;
//		offsetColor += BYTES_PER_COLOR * 2;
//
//	}
//
//	//**********************************
//	//create all negative Y lines
//	//**********************************
//
//	for (int i = 0; i < m_size; i++)
//	{
//
//		GLint vertices[] = { -m_size * pixelsPerUnit,
//							 (-m_size * pixelsPerUnit) + (i * pixelsPerUnit),      //first vertex
//							   m_size * pixelsPerUnit,
//							 (-m_size * pixelsPerUnit) + (i * pixelsPerUnit) };  //second vertex
//
//		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
//
//		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
//		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);
//
//		offsetVertex += BYTES_PER_VERTEX * 2;
//		offsetColor += BYTES_PER_COLOR * 2;
//
//	}
//
//	//**********************************
//	//create all positive Y lines
//	//**********************************
//
//	for (int i = 1; i < m_size + 1; i++)
//	{
//
//		GLint vertices[] = { -m_size * pixelsPerUnit, 0 + (i * pixelsPerUnit),      //first vertex
//							  m_size * pixelsPerUnit, 0 + (i * pixelsPerUnit) };  //second vertex
//
//		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
//
//		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
//		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);
//
//		offsetVertex += BYTES_PER_VERTEX * 2;
//		offsetColor += BYTES_PER_COLOR * 2;
//
//	}
//
//	return true;
//
//}