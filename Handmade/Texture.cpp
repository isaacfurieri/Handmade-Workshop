#include <iostream>
#include <SDL_image.h>
#include "Texture.h"
#include "Utility.h"

std::map<std::string, GLuint>* Texture::s_textureIDMap = new std::map<std::string, GLuint>;

//std::map<std::string, Texture>*
//Texture::s_textureMap = new std::map<std::string, Texture>;

//======================================================================================================
//bool Texture::GetTexture(const std::string& textureID, Texture& texture)
//{
//	//First check if texture object exists in map and if not then
//	//display a warning message, otherwise go ahead and assign the
//	//texture object. We return a bool flag for success/failure and 
//	//use passed texture reference to store the found texture object
//
//	auto it = s_textureMap->find(textureID);
//
//	if (it == s_textureMap->end())
//	{
//		Debug::Log("Texture object '" + textureID + "' not found.", Debug::WARNING);
//		Debug::Log("===============================================================");
//		return false;
//	}
//
//	texture = it->second;
//	return true;
//}
//======================================================================================================
Texture::Texture()
{
	m_ID = 0;
}
//======================================================================================================
const std::string& Texture::GetName() const
{
	return m_name;
}
//======================================================================================================
void Texture::SetWrapping(WrapSetting wrapSetting)
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapSetting);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapSetting);
	glBindTexture(GL_TEXTURE_2D, 0);
}
//======================================================================================================
void Texture::SetTexture(const std::string& textureID)
{
	//Debug::Log("Setting texture to: '" + textureID + "'");

	//first check if texture ID exists in map and if not display
	//error message, otherwise go ahead and assign the texture ID

	auto it = s_textureIDMap->find(textureID);

	if (it == s_textureIDMap->end())
	{
		//Debug::Log("Texture ID not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
		//Debug::Log("===============================================================");
	}

	else
	{
		m_ID = it->second;
		//Debug::Log("Texture ID assigned successfully.", Debug::ErrorCode::SUCCESS);
		//Debug::Log("===============================================================");
	}
}
//======================================================================================================
void Texture::SetFilter(FilterType filterType, FilterSetting filterSetting)
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexParameteri(GL_TEXTURE_2D, filterType, filterSetting);
	glBindTexture(GL_TEXTURE_2D, 0);
}
//======================================================================================================
bool Texture::Load(const std::string& filename, const std::string& textureID)
{
	//display text to state that file is being opened and read
	//Debug::Log("Opening and reading texture file: '" + filename + "'");

	//first check if texture ID exists in map and if it does display error message
	//and halt loading because we don't want to replace the existing texture
	if (s_textureIDMap->find(textureID) != s_textureIDMap->end())
	{
		//Debug::Log("Texture already loaded in memory.", Debug::ErrorCode::WARNING);
		//Debug::Log("===============================================================");
		return false;
	}

	//load texture from file using SDL image load function
	SDL_Surface* textureData = IMG_Load(filename.c_str());

	//if texture loading failed, display error message 
	if (!textureData)
	{
		//Debug::Log("File could not be loaded.", Debug::ErrorCode::FAILURE);
		//Debug::Log("===============================================================");
		return false;
	}

	//Use SDL image pointer to extract raw image data 
	//and assign that to local variables for use below
	GLsizei width = textureData->w;
	GLsizei height = textureData->h;
	Uint8* pixels = (Uint8*)textureData->pixels;
	Uint8 depth = textureData->format->BytesPerPixel;
	GLint format = ((depth == 4) ? GL_RGBA : GL_RGB);

	//create an OpenGL texture ID and store it
	glGenTextures(1, &m_ID);

	//link newly created ID with the texture
	//data we are about to send to OpenGL  
	glBindTexture(GL_TEXTURE_2D, m_ID);

	//set magnification and minification filters 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//set texture wrap filters 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//send the raw image data to OpenGL, where it will be stored in OpenGL's texture database
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	//automatically generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	//free SDL image as its no longer needed
	SDL_FreeSurface(textureData);

	//unlink texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//assign texture ID to map now the ID
	//is linked to the image data in OpenGL
	(*s_textureIDMap)[textureID] = m_ID;
	//s_textureMap->insert(std::pair<std::string, Texture>(textureID, *this));

	//display text to state that file has been opened and read
	//Debug::Log("File opened and read successfully.", Debug::ErrorCode::SUCCESS);
	//Debug::Log("===============================================================");

	return true;
}
//======================================================================================================
void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
//======================================================================================================
void Texture::Bind(TextureUnit textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
//======================================================================================================
void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
//======================================================================================================
void Texture::Unload()
{
	//Debug::Log("Unloading all textures from memory...");

	//loop through entire texture map in order to remove all texture IDs
	for (auto it = s_textureIDMap->begin(); it != s_textureIDMap->end(); it++)
	{
		glDeleteTextures(1, &(it->second));
	}

	//clear the texture ID map
	s_textureIDMap->clear();

	//Debug::Log("Textures unloaded successfully.", Debug::ErrorCode::SUCCESS);
	//Debug::Log("===============================================================");
}
//======================================================================================================
void Texture::Unload(const std::string& textureID)
{
	//Debug::Log("Unloading texture: '" + textureID + "'");

	//check if texture ID exists in map and if not display error message
	//otherwise remove that specific texture ID and remove map element
	auto it = s_textureIDMap->find(textureID);

	if (it == s_textureIDMap->end())
	{
		//Debug::Log("Texture ID not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
		//Debug::Log("===============================================================");
	}

	else
	{
		glDeleteTextures(1, &(it->second));
		s_textureIDMap->erase(it);

		//Debug::Log("Texture unloaded successfully.", Debug::ErrorCode::SUCCESS);
		//Debug::Log("===============================================================");
	}
}