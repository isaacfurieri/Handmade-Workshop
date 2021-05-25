#include <iostream>
#include <SDL_image.h>
#include "Debug.h"
#include "Texture.h"

std::map<std::string, GLuint>* Texture::s_textureIDMap = new std::map<std::string, GLuint>;

//======================================================================================================-
void Texture::Output()
{
	//clear the console window for a fresh display
	Debug::ClearLog();

	//display total amount of texture IDs stored in map
	Debug::Log("===============================================================");
	Debug::Log("Size of Texture ID Map: " + std::to_string(s_textureIDMap->size()));
	Debug::Log("===============================================================");

	//loop through map and display each texture detailing its OpenGL ID and tag name
	for (auto it = s_textureIDMap->begin(); it != s_textureIDMap->end(); it++)
	{
		Debug::Log((GLfloat)it->second, it->first);
	}

	Debug::Log("===============================================================");
}
//======================================================================================================
Texture::Texture()
{
	m_ID = 0;
}
//======================================================================================================
void Texture::SetTexture(const std::string& textureID)
{
	Debug::Log("Setting texture to: '" + textureID + "'");

	//first check if texture ID exists in map and if not display
	//error message, otherwise go ahead and assign the texture ID

	auto it = s_textureIDMap->find(textureID);

	if (it == s_textureIDMap->end())
	{
		Debug::Log("Texture ID not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
	}

	else
	{
		m_ID = it->second;
		Debug::Log("Texture ID assigned successfully.", Debug::ErrorCode::SUCCESS);
		Debug::Log("===============================================================");
	}
}
//======================================================================================================
bool Texture::Load(const std::string& filename, const std::string& textureID)
{
	//variables to hold property values of raw image data
	unsigned char* pixels = 0;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;
	unsigned int format = 0;
	SDL_Surface* textureData = 0;

	//display text to state that file is being opened and read
	Debug::Log("Opening and reading texture file: '" + filename + "'");

	//first check if texture ID exists in map and if it does display error message
	//and halt loading because we don't want to replace the existing texture
	if (s_textureIDMap->find(textureID) != s_textureIDMap->end())
	{
		Debug::Log("Texture already loaded in memory.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
		return false;
	}

	//load texture from file using SDL image load function
	textureData = IMG_Load(filename.c_str());

	//if texture loading failed, display error message 
	if (!textureData)
	{
		Debug::Log("File could not be loaded.", Debug::ErrorCode::FAILURE);
		Debug::Log("===============================================================");
		return false;
	}

	//use SDL image pointer to aquire raw image data 
	//from image and assign that data to the variables
	pixels = (unsigned char*)textureData->pixels;
	width = textureData->w;
	height = textureData->h;
	depth = textureData->format->BytesPerPixel;
	format = ((depth == 4) ? GL_RGBA : GL_RGB);

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

	//display text to state that file has been opened and read
	Debug::Log("File opened and read successfully.", Debug::ErrorCode::SUCCESS);
	Debug::Log("===============================================================");

	return true;
}
//======================================================================================================
void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
//======================================================================================================
void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
//======================================================================================================
void Texture::Unload()
{
	Debug::Log("Unloading all textures from memory...");

	//loop through entire texture map in order to remove all texture IDs
	for (auto it = s_textureIDMap->begin(); it != s_textureIDMap->end(); it++)
	{
		glDeleteTextures(1, &(it->second));
	}

	//clear the texture ID map
	s_textureIDMap->clear();

	Debug::Log("Textures unloaded successfully.", Debug::ErrorCode::SUCCESS);
	Debug::Log("===============================================================");
}
//======================================================================================================
void Texture::Unload(const std::string& textureID)
{
	Debug::Log("Unloading texture: '" + textureID + "'");

	//check if texture ID exists in map and if not display error message
	//otherwise remove that specific texture ID and remove map element
	auto it = s_textureIDMap->find(textureID);

	if (it == s_textureIDMap->end())
	{
		Debug::Log("Texture ID not found. Please enter a valid ID.", Debug::ErrorCode::WARNING);
		Debug::Log("===============================================================");
	}

	else
	{
		glDeleteTextures(1, &(it->second));
		s_textureIDMap->erase(it);

		Debug::Log("Texture unloaded successfully.", Debug::ErrorCode::SUCCESS);
		Debug::Log("===============================================================");
	}
}