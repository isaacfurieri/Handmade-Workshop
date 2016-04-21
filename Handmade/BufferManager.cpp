#include <iostream>
#include "BufferManager.h"

//------------------------------------------------------------------------------------------------------
//getter function that returns buffer ID based on VBO map index passed 
//------------------------------------------------------------------------------------------------------
GLuint BufferManager::GetBufferID(BufferType bufferType, const std::string& mapIndex)
{

	//first check if map index is a valid value
	//if not return a flag to indicate it's invalid
	//this prevents invalid map entries being created
	if (mapIndex == "")
	{
		return -1;
	}

	//otherwise return buffer ID based on buffer type and map index passed 
	switch (bufferType)
	{
		case VERTEX_BUFFER  : return m_vertexBufferIDMap[mapIndex]; break;
		case COLOR_BUFFER   : return m_colorBufferIDMap[mapIndex]; break;
		case NORMAL_BUFFER  : return m_normalBufferIDMap[mapIndex]; break;
		case TEXTURE_BUFFER : return m_textureBufferIDMap[mapIndex]; break;
	}

	return -1;

}
//------------------------------------------------------------------------------------------------------
//function that activates VBO based on buffer ID passed
//------------------------------------------------------------------------------------------------------
void BufferManager::Enable(GLuint bufferID)
{

	glBindBuffer(GL_ARRAY_BUFFER, bufferID); 

}
//------------------------------------------------------------------------------------------------------
//function that deactivates all buffers by binding buffer to NULL
//------------------------------------------------------------------------------------------------------
void BufferManager::Disable()
{

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
//------------------------------------------------------------------------------------------------------
//function that creates a specific VBO and stores the ID in a VBO map
//------------------------------------------------------------------------------------------------------
void BufferManager::Create(BufferType bufferType, const std::string& mapIndex)
{

	//temp ID that will store generated ID number
	GLuint ID = 0;

	//create a VBO and store the ID in temp variable
	//here we don't check for -1 errors because this way 
	//of creating OpenGL objects uses unsigned int variables
	glGenBuffers(1, &ID);

	//store VBO ID in specific map based on VBO enum type passed
	switch (bufferType)
	{
		case VERTEX_BUFFER  : m_vertexBufferIDMap[mapIndex] = ID; break;
		case COLOR_BUFFER   : m_colorBufferIDMap[mapIndex] = ID; break;
		case NORMAL_BUFFER  : m_normalBufferIDMap[mapIndex] = ID; break;
		case TEXTURE_BUFFER : m_textureBufferIDMap[mapIndex] = ID; break;
	}

}
//------------------------------------------------------------------------------------------------------
//function that binds and fills a VBO with data based on buffer ID and data passed
//------------------------------------------------------------------------------------------------------
void BufferManager::Fill(GLuint bufferID, std::vector<GLfloat>& data)
{

	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data[0], GL_DYNAMIC_DRAW);

}
//------------------------------------------------------------------------------------------------------
//function that unloads single or multiple buffers from memory
//------------------------------------------------------------------------------------------------------
void BufferManager::Destroy(BufferType bufferType, RemoveType removeType, const std::string& mapIndex)
{

	//temp pointer which will reference specific buffer ID map
	std::map<std::string, GLuint>* tempMap = 0; 

	//assign whichever buffer ID map needs to be removed from 
	//to temp pointer so that when looping through the map later, 
	//the pointer is used instead of looping through four different maps
	switch (bufferType)
	{
		case VERTEX_BUFFER  : tempMap = &m_vertexBufferIDMap; break;
		case COLOR_BUFFER   : tempMap = &m_colorBufferIDMap; break;
		case NORMAL_BUFFER  : tempMap = &m_normalBufferIDMap; break;
		case TEXTURE_BUFFER : tempMap = &m_textureBufferIDMap; break;
	}

	//loop through entire VBO map in order 
	//to remove a specific buffer or all buffers
	for (auto it = tempMap->begin(); it != tempMap->end(); it++)
	{

		//if a flag is passed to remove a specific buffer
		//check if map index is the buffer that needs to be removed
		//and remove it from both OpenGL and the map
		if (removeType == CUSTOM_BUFFER)
		{
			if (it->first == mapIndex)
			{
				glDeleteBuffers(1, &(it->second));
				tempMap->erase(it);
				break;
			}
		}

		//otherwise if a flag is passed to remove all buffers
		//remove the buffer from OpenGL
		else if (removeType == ALL_BUFFERS)
		{
			glDeleteBuffers(1, &(it->second));
		}

	}

	//if all buffers have been removed from OpenGL, clear the 
	//entire map in one go, because the IDs in the map still remain
	if (removeType == ALL_BUFFERS)
	{
		tempMap->clear();
	}

}
//------------------------------------------------------------------------------------------------------
//function that displays total size of all VBO ID maps
//------------------------------------------------------------------------------------------------------
void BufferManager::Output()
{

	system("cls");
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Total size of all VBO maps : " << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Size of Vertex Buffer Map  : " << m_vertexBufferIDMap.size() << std::endl;
	std::cout << "Size of Color Buffer Map   : " << m_colorBufferIDMap.size() << std::endl;
	std::cout << "Size of Normal Buffer Map  : " << m_normalBufferIDMap.size() << std::endl;
	std::cout << "Size of Texture Buffer Map : " << m_textureBufferIDMap.size() << std::endl;
	std::cout << "------------------------------------" << std::endl;

}