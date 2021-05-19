#pragma once

/*===================================================================#
| 'Texture' source files last updated on 19 May 2021                 |
#===================================================================*/

#include <map>
#include <string>
#include "glad.h"

//TODO - Refine class such that it follows newer design

class Texture
{

public:

	static void Output();

	Texture();

	void SetTexture(const std::string& textureID);

	bool Load(const std::string& filename, const std::string& textureID);
	void Bind();

	void UnBind();
	void Unload();
	void Unload(const std::string& textureID);

private:

	static std::map<std::string, GLuint>* s_textureIDMap;

	GLuint m_ID;

};