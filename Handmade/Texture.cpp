#include <assert.h>
#include <iostream>
#include <SDL_image.h>
#include "Texture.h"
#include "Utility.h"

std::map<std::string, Texture> Texture::s_textures;
std::string Texture::s_rootFolder = "Assets/Textures/";

//======================================================================================================
Texture::Texture()
{
	m_ID = 0;
}
//======================================================================================================
const std::string& Texture::GetTag() const
{
	return m_tag;
}
//======================================================================================================
void Texture::SetWrapping(WrapSetting wrapSetting)
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapSetting));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapSetting));
	glBindTexture(GL_TEXTURE_2D, 0);
}
//======================================================================================================
void Texture::SetTexture(const std::string& tag)
{
	auto it = s_textures.find(tag);
	assert(it != s_textures.end());
	*this = it->second;
}
//======================================================================================================
void Texture::SetFilter(FilterType filterType, FilterSetting filterSetting)
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexParameteri(GL_TEXTURE_2D, 
		static_cast<GLenum>(filterType), static_cast<GLint>(filterSetting));
	glBindTexture(GL_TEXTURE_2D, 0);
}
//======================================================================================================
bool Texture::Load(const std::string& filename, const std::string& tag)
{
	if (filename.empty())
	{
		return false;
	}

	auto it = s_textures.find(tag);

	//This means that the texture already exists in the 
	//map and we don't want to replace the existing texture
	assert(it == s_textures.end());

	//TODO - Find a way to load the image the right way up, 
	//else we have to add conversion to flip the raw pixel data
	SDL_Surface* textureData = IMG_Load((s_rootFolder + filename).c_str());

	if (!textureData)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error loading texture file \"" + (s_rootFolder + filename) + "\"."
			"Possible causes could be a corrupt or missing file. It could also be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
		return false;
	}

	//This is all the raw image data 
	auto width = textureData->w;
	auto height = textureData->h;
	auto pixels = reinterpret_cast<Uint8*>(textureData->pixels);
	auto depth = textureData->format->BytesPerPixel;
	auto format = ((depth == 4) ? GL_RGBA : GL_RGB);

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(textureData);

	glBindTexture(GL_TEXTURE_2D, 0);

	s_textures[tag] = *this;
	return true;
}
//======================================================================================================
void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
//======================================================================================================
void Texture::Bind(TextureUnit textureUnit) const
{
	glActiveTexture(static_cast<GLenum>(textureUnit));
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
//======================================================================================================
void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
//======================================================================================================
void Texture::Unload() const
{
	for (auto& texture : s_textures)
	{
		glDeleteTextures(1, &texture.second.m_ID);
	}

	s_textures.clear();
}
//======================================================================================================
void Texture::Unload(const std::string& tag) const
{
	auto it = s_textures.find(tag);
	assert(it != s_textures.end());
	glDeleteTextures(1, &(it->second.m_ID));
	s_textures.erase(it);
}