#include <iostream>
#include <SDL_image.h>
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//getter function that returns texture ID based on texture map index passed 
//------------------------------------------------------------------------------------------------------
GLuint TextureManager::GetTextureID(const std::string& mapIndex)
{

	return m_textureIDMap[mapIndex];

}
//------------------------------------------------------------------------------------------------------
//function that activates texture based on texture ID passed
//------------------------------------------------------------------------------------------------------
void TextureManager::Enable(GLuint textureID)
{

	glBindTexture(GL_TEXTURE_2D, textureID);

}
//------------------------------------------------------------------------------------------------------
//function that deactivates all textures by binding texture to NULL
//------------------------------------------------------------------------------------------------------
void TextureManager::Disable()
{

	glBindTexture(GL_TEXTURE_2D, 0);

}
//------------------------------------------------------------------------------------------------------
//function that loads a texture from a raw image file and stores the ID in a texture map
//------------------------------------------------------------------------------------------------------
bool TextureManager::LoadFromFile(const std::string& filename, const std::string& mapIndex)
{

	//variables to hold property values of raw image data
	unsigned char* pixels = 0;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;
	unsigned int format = 0;

	GLuint ID = 0;
	SDL_Surface* textureData = 0;

	//display text to state that file is being opened and read
	std::cout << "Opening and reading texture file : " << "\"" << filename << "\"" << std::endl;

	//load texture from file using SDL image load function
	textureData = IMG_Load(filename.c_str());

	//if texture loading failed, display error message 
	if (!textureData)
	{
		std::cout << "File could not be loaded." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
		return false;
	}

	else
	{

		//use SDL image pointer to aquire raw image data from image
		//and assign that data to the variables
		pixels = (unsigned char*)textureData->pixels;
		width = textureData->w;
		height = textureData->h;
		depth = textureData->format->BytesPerPixel;
		format = ((depth == 4) ? GL_RGBA : GL_RGB);

		//create an OpenGL texture ID and store it
		glGenTextures(1, &ID);

		//link the newly created ID with the texture data we 
		//are about to send to OpenGL  
		glBindTexture(GL_TEXTURE_2D, ID);

		//set parameters
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//send the raw image data to OpenGL, where it will be stored in OpenGL's texture database
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

		//free SDL image as its no longer needed
		SDL_FreeSurface(textureData);

		//unlink texture
		glBindTexture(GL_TEXTURE_2D, 0);

		//assign texture ID to map
		//now the ID is linked to the image data in OpenGL
		m_textureIDMap[mapIndex] = ID;

	}

	//display text to state that file has been opened and read
	std::cout << "File opened and read successfully." << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that unloads single or multiple textures from memory
//------------------------------------------------------------------------------------------------------
void TextureManager::UnloadFromMemory(RemoveType removeType, const std::string& mapIndex)
{

	//loop through entire texture map in order 
	//to remove a specific texture or all textures
	for (auto it = m_textureIDMap.begin(); it != m_textureIDMap.end(); it++)
	{

		//if a flag is passed to remove a specific texture
		//check if map index is the texture that needs to be removed
		//and remove it from both OpenGL and the map
		if (removeType == CUSTOM_TEXTURE)
		{
			if (it->first == mapIndex)
			{
				glDeleteTextures(1, &(it->second));
				m_textureIDMap.erase(it);
				break;
			}
		}

		//otherwise if a flag is passed to remove all textures
		//remove the texture from OpenGL
		else if (removeType == ALL_TEXTURES)
		{
			glDeleteTextures(1, &(it->second));
		}

	}

	//if all textures have been removed from OpenGL, clear the 
	//entire map in one go, because the IDs in the map still remain
	if (removeType == ALL_TEXTURES)
	{
		m_textureIDMap.clear();
	}

}
//------------------------------------------------------------------------------------------------------
//function that displays total size of texture ID map
//------------------------------------------------------------------------------------------------------
void TextureManager::Output()
{

	//clear the console window for a fresh display
	system("cls");
	
	//display total amount of texture IDs stored in map
	std::cout << "Size of Texture ID Map : " << m_textureIDMap.size() << std::endl;
	std::cout << "------------------------------" << std::endl;

	//loop through map and display each texture detailing its OpenGL ID and tag name
	for (auto it = m_textureIDMap.begin(); it != m_textureIDMap.end(); it++)
	{
		std::cout << it->second << " : " << it->first << std::endl;
	}

}