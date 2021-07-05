#pragma once

/*===================================================================#
| 'Texture' source files last updated on 5 July 2021                 |
#===================================================================*/

#include <map>
#include <string>
#include "glad.h"

class Texture
{

public:

	enum WrapSetting
	{
		REPEAT = GL_REPEAT,
		REPEAT_MIRROR = GL_MIRRORED_REPEAT,
		CLAMP = GL_CLAMP_TO_EDGE
	};

	enum FilterType
	{
		MAG = GL_TEXTURE_MAG_FILTER,
		MIN = GL_TEXTURE_MIN_FILTER,
		//ANI = GL_TEXTURE_MAX_ANISOTROPY  //TODO - Find out why this is not recognized
	};

	enum FilterSetting
	{
		NEAREST = GL_NEAREST,
		BILINEAR = GL_LINEAR,
		TRILINEAR = GL_LINEAR_MIPMAP_LINEAR,
		ANISOTROPIC_4 = 4,
		ANISOTROPIC_8 = 8,
		ANISOTROPIC_16 = 16
	};

	enum TextureUnit
	{
		TEXTURE_1 = GL_TEXTURE0,
		TEXTURE_2 = GL_TEXTURE1,
		TEXTURE_3 = GL_TEXTURE2,
		TEXTURE_4 = GL_TEXTURE3
	};

	//static bool GetTexture(const std::string& textureID, Texture& texture);

	Texture();

	const std::string& GetName() const;

	void SetWrapping(WrapSetting wrapSetting);
	void SetTexture(const std::string& textureID);
	void SetFilter(FilterType filterType, FilterSetting filterSetting);

	bool Load(const std::string& filename, const std::string& textureID);
	
	void Bind() const;
	void Bind(TextureUnit textureUnit);

	void Unbind() const;
	void Unload();
	void Unload(const std::string& textureID);

private:

	static std::string s_rootFolder;
	static std::map<std::string, GLuint>* s_textureIDMap;
	
	//TODO - We want to store textures as objects and not IDs
	//static std::map<std::string, Texture>* s_textureMap;

	GLuint m_ID;
	std::string m_name;

};