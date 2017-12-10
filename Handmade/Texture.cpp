#include <iostream>
#include <SDL_image.h>
#include "Texture.h"

//this allocated space remains in memory until the application ends
std::map<std::string, GLuint>* Texture::s_textureIDMap = new std::map<std::string, GLuint>;

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Texture::Texture()
{

	m_ID = 0;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns texture image ID based on index value passed
//------------------------------------------------------------------------------------------------------
void Texture::SetTexture(const std::string& textureID)
{

	std::cout << "Setting texture to : " << "\"" << textureID << "\"" << std::endl;

	//first check if texture ID exists in map and if not display
	//error message, otherwise go ahead and assign the texture ID

	auto it = s_textureIDMap->find(textureID);
	
	if (it == s_textureIDMap->end())
	{
		std::cout << "Texture ID not found. Please enter a valid ID." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
	}
	
	else
	{
		m_ID = it->second;
		std::cout << "Texture ID assigned successfully." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
	}

}
//------------------------------------------------------------------------------------------------------
//function that loads a texture from a raw image file and stores the ID in texture map
//------------------------------------------------------------------------------------------------------
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
	std::cout << "Opening and reading texture file : " << "\"" << filename << "\"" << std::endl;

	//first check if texture ID exists in map and if it does display error message
	//and halt loading because we don't want to replace the existing texture
	if (s_textureIDMap->find(textureID) != s_textureIDMap->end())
	{
		std::cout << "Texture already loaded in memory." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
		return false;
	}

	//load texture from file using SDL image load function
	textureData = IMG_Load(filename.c_str());

	//if texture loading failed, display error message 
	if (!textureData)
	{
		std::cout << "File could not be loaded." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
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
	std::cout << "File opened and read successfully." << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that binds texture ID for use in fragment shader
//------------------------------------------------------------------------------------------------------
void Texture::Bind()
{

	glBindTexture(GL_TEXTURE_2D, m_ID);

}
//------------------------------------------------------------------------------------------------------
//function that unbinds current texture 
//------------------------------------------------------------------------------------------------------
void Texture::UnBind()
{

	glBindTexture(GL_TEXTURE_2D, 0);

}
//------------------------------------------------------------------------------------------------------
//function that unloads all OpenGL texture IDs from memory
//------------------------------------------------------------------------------------------------------
void Texture::Unload()
{

	std::cout << "Unloading all textures from memory." << std::endl;

	//loop through entire texture map in order to remove all texture IDs
	for (auto it = s_textureIDMap->begin(); it != s_textureIDMap->end(); it++)
	{
		glDeleteTextures(1, &(it->second));
	}

	//clear the texture ID map
	s_textureIDMap->clear();

	std::cout << "---------------------------------------------------------------" << std::endl;

}
//------------------------------------------------------------------------------------------------------
//function that unloads a specific OpenGL texture ID from memory
//------------------------------------------------------------------------------------------------------
void Texture::Unload(const std::string& textureID)
{

	std::cout << "Unloading texture : " << "\"" << textureID << "\"" << std::endl;

	//check if texture ID exists in map and if not display error message
	//otherwise remove that specific texture ID and remove map element
	auto it = s_textureIDMap->find(textureID);

	if (it == s_textureIDMap->end())
	{
		std::cout << "Texture ID not found. Please enter a valid ID." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
	}

	else
	{
		glDeleteTextures(1, &(it->second));
		s_textureIDMap->erase(it);

		std::cout << "Texture unloaded successfully." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
	}

}
//------------------------------------------------------------------------------------------------------
//function that displays total size of texture ID map
//------------------------------------------------------------------------------------------------------
void Texture::Output()
{

	//clear the console window for a fresh display
	system("cls");

	//display total amount of texture IDs stored in map
	std::cout << "---------------------------------------------------------------" << std::endl;
	std::cout << "Size of Texture ID Map : " << s_textureIDMap->size() << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	//loop through map and display each texture detailing its OpenGL ID and tag name
	for (auto it = s_textureIDMap->begin(); it != s_textureIDMap->end(); it++)
	{
		std::cout << "\"" << it->first << "\" (ID " << it->second << ")" <<  std::endl;
	}

	std::cout << "---------------------------------------------------------------" << std::endl;

}