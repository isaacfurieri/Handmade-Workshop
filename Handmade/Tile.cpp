#include <gtc\matrix_transform.hpp>      
#include "Input.h"
#include "Shader.h"
#include "Tile.h"

//======================================================================================================
Tile::Tile(GLfloat width, GLfloat height, GLuint spriteSheetCol, GLuint spriteSheetRow)
{
	m_tileIndex = 0;
	m_color = glm::vec4(1.0f);
	m_animationVelocity = 0.1f;
	m_spriteSheetCol = spriteSheetCol;
	m_spriteSheetRow = spriteSheetRow;
	m_dimension = glm::vec2(width, height);

	m_isAnimated = false;
	m_isAnimationDead = false;
	m_isAnimationLooping = false;
	m_isAnimationLoopFinal = false;

	GLuint offsetUV = 0;
	GLuint offsetVert = 0;
	GLuint offsetColor = 0;
	GLuint offsetIndex = 0;

	const int TOTAL_DIMENSION = m_spriteSheetCol * m_spriteSheetRow;
	const int BYTES_PER_TILE_UV = Buffer::ComponentSize::UV * CORNERS * sizeof(GLfloat);
	const int BYTES_PER_TILE_COLOR = Buffer::ComponentSize::RGBA * CORNERS * sizeof(GLfloat);
	const int BYTES_PER_TILE_VERTEX = Buffer::ComponentSize::XYZ * CORNERS * sizeof(GLfloat);
	const int BYTES_PER_TILE_INDEX = Buffer::ComponentSize::XYZ * (CORNERS - 1) * sizeof(GLuint);

	const int TOTAL_BYTES_VBO_VERT = TOTAL_DIMENSION * BYTES_PER_TILE_VERTEX;
	const int TOTAL_BYTES_VBO_COLOR = TOTAL_DIMENSION * BYTES_PER_TILE_COLOR;
	const int TOTAL_BYTES_VBO_UV = TOTAL_DIMENSION * BYTES_PER_TILE_UV;
	const int TOTAL_BYTES_EBO = TOTAL_DIMENSION * BYTES_PER_TILE_INDEX;

	m_buffer.Create("Tile", TOTAL_DIMENSION * VERTICES_PER_TILE, true);
	m_buffer.LinkEBO();

	glm::vec2 halfDimension = m_dimension * 0.5f;

	//Calculate the width and height of each 'cel' relative to the entire texture 
	//This gives us a normalized dimension value for each 'cel' in the sprite sheet
	glm::vec2 celDimension(1.0f / m_spriteSheetCol, 1.0f / m_spriteSheetRow);

	GLuint count = 0;

	//Loop through the entire sprite sheet and generate 
	//vertices, color, and UV coordinates for each tile 
	for (GLuint row = 0; row < m_spriteSheetRow; row++)
	{
		for (GLuint col = 0; col < m_spriteSheetCol; col++)
		{
			GLfloat vertices[] = { -halfDimension.x,  halfDimension.y, 0.0f,
									halfDimension.x,  halfDimension.y, 0.0f,
									halfDimension.x, -halfDimension.y, 0.0f,
								   -halfDimension.x, -halfDimension.y, 0.0f };

			m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVert);
			offsetVert += BYTES_PER_TILE_VERTEX;

			GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a,
								 m_color.r, m_color.g, m_color.b, m_color.a,
								 m_color.r, m_color.g, m_color.b, m_color.a,
								 m_color.r, m_color.g, m_color.b, m_color.a };

			m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);
			offsetColor += BYTES_PER_TILE_COLOR;

			//Take the desired 'cel' to 'cut out' and multiply it by the cel's dimension value
			//This gives us a normalized texture coordinate value that is our 'starting point' 
			glm::vec2 UVOrigin(col * celDimension.x, row * celDimension.y);

			GLfloat UVs[] = { UVOrigin.s,                  UVOrigin.t,
							  UVOrigin.s + celDimension.x, UVOrigin.t,
							  UVOrigin.s + celDimension.x, UVOrigin.t + celDimension.y,
							  UVOrigin.s,                  UVOrigin.t + celDimension.y };

			m_buffer.AppendVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), offsetUV);
			offsetUV += BYTES_PER_TILE_UV;

			GLuint indices[] = { 0 + (count * 4), 1 + (count * 4), 3 + (count * 4),
								 3 + (count * 4), 1 + (count * 4), 2 + (count * 4) };

			m_buffer.AppendEBO(indices, sizeof(indices), offsetIndex);
			offsetIndex += BYTES_PER_TILE_INDEX;
			count++;
		}
	}
}
//======================================================================================================
Tile::~Tile()
{
	m_buffer.Destroy();
}
//======================================================================================================
bool Tile::IsAnimationDead() const
{
	return m_isAnimationDead;
}
//======================================================================================================
bool Tile::IsAnimationLooping() const
{
	return m_isAnimationLooping;
}
//======================================================================================================
void Tile::IsAnimated(bool flag)
{
	m_isAnimated = flag;
}
//======================================================================================================
void Tile::IsAnimationLooping(bool flag)
{
	m_isAnimationLooping = flag;
}
//======================================================================================================
void Tile::SetTileIndex(GLuint tileIndex)
{
	m_tileIndex = tileIndex;
}
//======================================================================================================
void Tile::SetTileIndex(GLuint column, GLuint row)
{
	//Because everything is zero-based, we must decrement
	m_tileIndex = ((row - 1) * m_spriteSheetCol) + column;
	m_tileIndex--;
}
//======================================================================================================
void Tile::SetAnimationVelocity(GLfloat velocity)
{
	m_animationVelocity = velocity;
}
//======================================================================================================
void Tile::SetDimension(const glm::vec3& dimension)
{
	m_dimension = dimension;
}
//======================================================================================================
void Tile::SetDimension(GLfloat width, GLfloat height)
{
	GLfloat halfWidth = width * 0.5f;
	GLfloat halfHeight = height * 0.5f;

	GLfloat vertices[] = { -halfWidth,  halfHeight, 0.0f,
							halfWidth,  halfHeight, 0.0f,
							halfWidth, -halfHeight, 0.0f,
						   -halfWidth, -halfHeight, 0.0f };

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FILL_MANY);
}
//======================================================================================================
void Tile::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	GLuint offsetColor = 0;

	for (int i = 0; i < (m_spriteSheetCol * m_spriteSheetRow); i++)
	{
		GLfloat colors[] = { r, g, b, a,
							 r, g, b, a,
							 r, g, b, a,
							 r, g, b, a };

		m_buffer.FillVBO(Buffer::VERTEX_BUFFER, colors, sizeof(colors), Buffer::FILL_MANY);
		offsetColor += sizeof(colors);
	}
}
//======================================================================================================
void Tile::Render(Shader& shader)
{
	//Store size of each EBO partition for each tile
	const GLuint BYTES_PER_TILE_INDEX = VERTICES_PER_TILE * sizeof(GLuint);

	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);
	m_buffer.LinkVBO(shader.GetAttributeID("textureIn"), Buffer::TEXTURE_BUFFER, Buffer::UV, Buffer::FLOAT);
	//m_buffer.LinkVBO(shader.GetAttributeID("normalIn"), Buffer::NORMAL_BUFFER, Buffer::XYZ, Buffer::FLOAT);

	//This will render each individual 'cel' making it look like an animation
	if (m_isAnimated)
	{
		//Use fake 60FPS 'delta time'
		static GLfloat timeElapsed = 0.0f;
		timeElapsed += 0.16f;

		//If animation is set to cycle endlessly then set the kill and final flags
		//to false so that no other final checks are made and that the animation loops
		if (m_isAnimationLooping)
		{
			m_isAnimationDead = false;
			m_isAnimationLoopFinal = false;
		}

		//Otherwise if animation is set to cycle once and the last image
		//cel has been reached then flag this as the final animation loop
		else if (!m_isAnimationLooping &&
			m_tileIndex == (m_spriteSheetCol * m_spriteSheetRow - 1))
		{
			m_isAnimationLoopFinal = true;
		}

		//If this is the final animation, flag to kill entire animation
		//because even though the animation is marked final, a few more 
		//frames will be called with the last image cel set, so only
		//mark it dead when the first image cel comes around again
		if (m_isAnimationLoopFinal && m_tileIndex == 0)
		{
			m_isAnimationDead = true;
		}

		//We need to be able to pick the correct portion
		//of the EBO to use to render the correct tile
		m_tileIndex = (GLuint)(timeElapsed * m_animationVelocity) %
			(m_spriteSheetCol * m_spriteSheetRow);
	}

	m_buffer.Render(Buffer::TRIANGLES, (m_tileIndex * BYTES_PER_TILE_INDEX), VERTICES_PER_TILE);
}
//======================================================================================================
void Tile::SendToShader(Shader& shader)
{
	shader.SendData("isTextured", 1);
	shader.SendData("model", m_transform.GetMatrix());
}