#pragma once

/*===================================================================#
| 'Text' source files last updated on 25 October 2021                |
#====================================================================#
| Class has gone through initial tests. No known issues found.       |
#===================================================================*/

#include <map>
#include <ft2build.h>
#include <freetype\freetype.h>
#include "Buffer.h"
#include "Object.h"

const GLuint TOTAL_ASCII_CHARACTERS = 128;

class Text : public Object
{

public:

	static bool Initialize();
	static void Shutdown();

	static bool Load(const std::string& tag,
		const std::string& filename, GLuint fontSize);
	static void Unload(const std::string& tag = "");

	static void SetRootFolder(const std::string& rootFolder);

	Text(const std::string& tag = "",
		const std::string& filename = "", GLuint fontSize = 10U);
	Text(const Text& copy);
	virtual ~Text();

	GLuint GetFontSize();
	GLuint GetTotalWidth();
	const std::string& GetString() const;

	void SetFont(const std::string& tag);
	void SetString(const std::string& string);
	void AppendString(const std::string& string);

	void SetColor(const glm::vec4& color);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	void IsFirstLetterCentered(bool flag);

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader);

private:

	struct Glyph
	{
		GLuint ID;       //OGL texture ID for each letter 
		GLint width;     //Width of the letter
		GLint height;    //Height of the letter 
		GLint bearingX;  //Distance from the y-axis origin
		GLint bearingY;  //Distance from the x-axis baseline 
		GLint advance;   //Offset to advance to next glyph
	};

	//Would love to call it 'Font' but that name is reserved
	typedef std::map<GLchar, Glyph> FontType;

	Buffer m_buffer;
	FontType m_font;

	glm::vec4 m_color;
	GLuint m_fontSize;
	GLuint m_totalWidth;

	std::string m_string;
	bool m_isFirstLetterCentered;

	static GLuint s_totalObjects;
	static std::string s_rootFolder;
	static FT_Library s_freetypeObject;
	static std::map<std::string, FontType> s_fonts;

};