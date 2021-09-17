#pragma once

/*===================================================================#
| 'Text' source files last updated on 17 September 2021              |
#===================================================================*/

#include <map>
#include <string>
#include <ft2build.h>
#include <freetype\freetype.h>
#include "glad.h"
#include "Buffer.h"
#include "Object.h"

const GLuint TOTAL_ASCII_CHARACTERS = 128;

struct Glyph
{
	GLuint ID;       //texture freetypeTextureID for each letter 
	GLint width;     //width of the letter
	GLint height;    //height of the letter 
	GLint bearingX;  //distance from the y-axis origin
	GLint bearingY;  //distance from the x-axis baseline 
	GLint advance;   //offset to advance to next glyph
};

class Text : public Object
{

public:

	static bool Initialize();
	static void Shutdown();

	Text();
	virtual ~Text() {}

	bool LoadFont(const std::string& filename, int fontSize);
	void UnloadFont();

	GLuint GetFontSize();
	GLuint GetTotalWidth();
	const std::string& GetText() const;

	void SetText(const std::string& text);
	void AppendText(const std::string& text);

	void SetColor(const glm::vec4& color);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	void IsFirstLetterCentered(bool flag);

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader);

private:

	static FT_Library s_freetypeObject;

	Buffer m_buffer;
	GLuint m_fontSize;
	GLuint m_totalWidth;
	FT_Face m_freetypeFace;

	std::string m_text;
	bool m_isFirstLetterCentered;
	std::map<GLchar, Glyph> m_glyphs;

};