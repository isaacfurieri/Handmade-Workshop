#include "Shader.h"
#include "Text.h"
#include "Utility.h"

FT_Library Text::s_freetypeObject = nullptr;

//================================================================================================
bool Text::Initialize()
{
	if (FT_Init_FreeType(&s_freetypeObject))
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error initializing the FreeType library", Utility::Severity::Failure);
		return false;
	}

	return true;
}
//================================================================================================
bool Text::LoadFont(const std::string& filename, int fontSize)
{
	if (FT_New_Face(s_freetypeObject, filename.c_str(), 0, &m_freetypeFace))
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error loading font file \"" + (filename)+"\"."
			"Possible causes could be a corrupt or missing file. It could also be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);

		return false;
	}

	FT_Set_Pixel_Sizes(m_freetypeFace, fontSize, fontSize);

	//This is needed so that we don't follow the standard 4-byte alignment
	//because the freetype glyph textures only use 1 byte of color data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Generate a glyph for all 128 ASCII characters
	for (int i = 0; i < TOTAL_ASCII_CHARACTERS; i++)
	{
		if (FT_Load_Char(m_freetypeFace, i, FT_LOAD_RENDER))
		{
			Utility::Log(Utility::Destination::OutputWindow,
				"Error creating glyph", Utility::Severity::Warning);
			continue;
		}

		//TODO - Find a way to move this to the lower levels
		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RED,
			m_freetypeFace->glyph->bitmap.width,
			m_freetypeFace->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			m_freetypeFace->glyph->bitmap.buffer);

		glBindTexture(GL_TEXTURE_2D, 0);

		Glyph glyph = { textureID,
						static_cast<GLint>(m_freetypeFace->glyph->bitmap.width),
						static_cast<GLint>(m_freetypeFace->glyph->bitmap.rows),
						static_cast<GLint>(m_freetypeFace->glyph->bitmap_left),
						static_cast<GLint>(m_freetypeFace->glyph->bitmap_top),
						static_cast<GLint>(m_freetypeFace->glyph->advance.x) };

		m_glyphs[i] = glyph;
	}

	FT_Done_Face(m_freetypeFace);
	m_fontSize = fontSize;
	return true;
}
//================================================================================================
void Text::UnloadFont()
{
	for (const auto& glyph : m_glyphs)
	{
		glDeleteTextures(1, &glyph.second.ID);
	}

	m_glyphs.clear();
}
//================================================================================================
void Text::Shutdown()
{
	FT_Done_FreeType(s_freetypeObject);
}
//================================================================================================
Text::Text()
{
	m_fontSize = 0;
	m_totalWidth = 0;
	m_freetypeFace = nullptr;

	static GLuint totalTextObjects = 0;

	m_buffer.Create("Text_" + std::to_string(totalTextObjects++), 6, true);
	m_buffer.LinkEBO();
}
//================================================================================================
GLuint Text::GetFontSize()
{
	return m_fontSize;
}
//================================================================================================
GLuint Text::GetTotalWidth()
{
	m_totalWidth = 0;

	for (const auto& character : m_text)
	{
		m_totalWidth += m_glyphs[character].advance / 64.0f;
	}

	return m_totalWidth;
}
//================================================================================================
const std::string& Text::GetText() const
{
	return m_text;
}
//================================================================================================
void Text::SetText(const std::string& text)
{
	m_text = text;
}
//================================================================================================
void Text::AppendText(const std::string& text)
{
	m_text += text;
}
//================================================================================================
void Text::SetColor(const glm::vec4& color)
{
	SetColor(color.r, color.g, color.b, color.a);
}
//================================================================================================
void Text::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	GLfloat colors[] = { r, g, b, a,
						 r, g, b, a,
						 r, g, b, a,
						 r, g, b, a };

	m_buffer.FillVBO(Buffer::VBO::ColorBuffer, colors, sizeof(colors), Buffer::Fill::Ongoing);
}
//================================================================================================
void Text::Render(Shader& shader)
{
	GLfloat textOrigin = 0.0f;

	for (const auto& character : m_text)
	{
		Glyph letter = m_glyphs[character];

		GLfloat vertices[] = { textOrigin + letter.bearingX, letter.bearingY, 0.0f,
			textOrigin + letter.bearingX + letter.width, letter.bearingY, 0.0f,
			textOrigin + letter.bearingX + letter.width, letter.bearingY - letter.height, 0.0f,
			textOrigin + letter.bearingX, letter.bearingY - letter.height, 0.0f };

		GLfloat UVs[] = { 0.0f, 0.0f,
						  1.0f, 0.0f,
						  1.0f, 1.0f,
						  0.0f, 1.0f };

		GLuint indices[] = { 0, 1, 3,
							 3, 1, 2 };

		m_buffer.FillEBO(indices, sizeof(indices));
		m_buffer.FillVBO(Buffer::VBO::VertexBuffer, vertices, sizeof(vertices), Buffer::Fill::Ongoing);
		m_buffer.FillVBO(Buffer::VBO::TextureBuffer, UVs, sizeof(UVs), Buffer::Fill::Ongoing);

		//TODO - Find a way to do this only once
		m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"),
			Buffer::VBO::VertexBuffer, Buffer::ComponentSize::XYZ, Buffer::DataType::FloatData);
		m_buffer.LinkVBO(shader.GetAttributeID("colorIn"),
			Buffer::VBO::ColorBuffer, Buffer::ComponentSize::RGBA, Buffer::DataType::FloatData);
		m_buffer.LinkVBO(shader.GetAttributeID("textureIn"),
			Buffer::VBO::TextureBuffer, Buffer::ComponentSize::UV, Buffer::DataType::FloatData);

		glBindTexture(GL_TEXTURE_2D, letter.ID);

		m_buffer.Render(Buffer::RenderMode::Triangles);

		glBindTexture(GL_TEXTURE_2D, 0);

		//We have to divide by 64 because the value is a product of 64
		textOrigin += letter.advance / 64.0f;
	}
}
//================================================================================================
void Text::SendToShader(Shader& shader)
{
	shader.SendData("model", m_transform.GetMatrix());
}