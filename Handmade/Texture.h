#pragma once

/*===================================================================#
| 'Texture' source files last updated on 24 June 2021                |
#===================================================================*/

#include <map>
#include <string>
#include "glad.h"

class Texture
{

public:

	Texture();

	const std::string& GetName() const;

	void SetTexture(const std::string& textureID);

	bool Load(const std::string& filename, const std::string& textureID);
	void Bind() const;

	void Unbind() const;
	void Unload();
	void Unload(const std::string& textureID);

private:

	static std::string s_rootFolder;
	static std::map<std::string, GLuint>* s_textureIDMap;

	GLuint m_ID;
	std::string m_name;

};