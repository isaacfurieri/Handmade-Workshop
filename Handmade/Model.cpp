#include <fstream>
#include <iostream>
#include "Debug.h"
#include "Model.h"

//------------------------------------------------------------------------------------------------------
//setter function that sets shininess value of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetShininess(GLfloat shininess)
{

	m_material.SetShininess(shininess);

}
//------------------------------------------------------------------------------------------------------
//function that assigns buffers to model based on buffer ID passed
//------------------------------------------------------------------------------------------------------
void Model::SetBuffer(const std::string bufferID)
{

	m_buffer.SetBuffers(bufferID);

}
//------------------------------------------------------------------------------------------------------
//function that assigns texture to model based on texture ID passed
//------------------------------------------------------------------------------------------------------
void Model::SetTexture(const std::string textureID)
{

	m_texture.SetTexture(textureID);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns specific color of model
//------------------------------------------------------------------------------------------------------
void Model::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

	//offset to keep track of buffer filling position
	GLuint offset = 0;

	//data that represents colors for model
	//this color is based on value passed to function
	GLfloat colors[] = { r, g, b, a };

	//based on size of model's color VBO, loop through entire color
	//buffer and fill it with the same color that was passed in
	for (size_t i = 0; i < m_groups.size(); i++)
	{
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offset);
		offset += sizeof(colors);
	}

}
//------------------------------------------------------------------------------------------------------
//setter function that sets ambient component of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetAmbient(GLfloat r, GLfloat g, GLfloat b)
{

	m_material.SetAmbient(r, g, b);

}
//------------------------------------------------------------------------------------------------------
//setter function that sets diffuse component of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetDiffuse(GLfloat r, GLfloat g, GLfloat b)
{

	m_material.SetDiffuse(r, g, b);

}
//------------------------------------------------------------------------------------------------------
//setter function that sets specular component of model's material
//------------------------------------------------------------------------------------------------------
void Model::SetSpecular(GLfloat r, GLfloat g, GLfloat b)
{

	m_material.SetSpecular(r, g, b);

}
//------------------------------------------------------------------------------------------------------
//function that loads raw model data from OBJ file 
//------------------------------------------------------------------------------------------------------
bool Model::LoadModel(const std::string& filename, const std::string bufferID)
{

	//variables to load and store all model data
	std::fstream file;
	std::string lineText = "";
	unsigned int tokenPosition = 0;

	std::vector<glm::vec3> faceArray;
	std::vector<glm::vec3> vertexArray;
	std::vector<glm::vec2> textureArray;
	std::vector<glm::vec3> normalArray;
	
	std::vector<std::string> subNumbers;
	std::vector<std::string> subStrings;
	
	//display text to state that file is being opened and read
	Debug::Log("Opening and reading model file: '" + filename + "'");

	//open model file
	file.open(filename);

	//if opening of model file failed, display error message
	if (!file)
	{
		Debug::Log("File could not be loaded.", Debug::ErrorCode::FAILURE);
		Debug::Log("===============================================================");
		return false;
	}

	//read in all model data until end of file is reached
	while (!file.eof())
	{

		//read line of text
		getline(file, lineText);

		//break text string into smaller substrings
		do
		{
			tokenPosition = lineText.find(' ');
			subStrings.push_back(lineText.substr(0, tokenPosition));
			lineText.erase(0, tokenPosition + 1);
		} while (tokenPosition != std::string::npos);

		//if first token is "v" or "vn", set the vertices and normal values
		if (subStrings[0] == "v" || subStrings[0] == "vn")
		{

			//if it's a vertex position, add it to the vertex array
			if (subStrings[0] == "v")
			{
				vertexArray.push_back(glm::vec3((GLfloat)(atof(subStrings[1].c_str())),
				  	                            (GLfloat)(atof(subStrings[2].c_str())),
					                            (GLfloat)(atof(subStrings[3].c_str()))));
			}

			//if it's a normal direction, add it to the normal array
			if (subStrings[0] == "vn")
			{
				normalArray.push_back(glm::vec3((GLfloat)(atof(subStrings[1].c_str())),
											    (GLfloat)(atof(subStrings[2].c_str())),
											    (GLfloat)(atof(subStrings[3].c_str()))));
			}

		}

		//if first token is "vt", set the UV data
		if (subStrings[0] == "vt")
		{

			//add to the textureArray
			textureArray.push_back(glm::vec2((GLfloat)(atof(subStrings[1].c_str())),
				                             (GLfloat)(atof(subStrings[2].c_str()))));

		}

		//if first token is "f", create a new face and set the face data
		if (subStrings[0] == "f")
		{

			//loop through all three face sub strings 
			for (int i = 1; i <= 3; i++)
			{

				//break each face substring into three face numeric values
				do
				{
					tokenPosition = subStrings[i].find('/');
					subNumbers.push_back(subStrings[i].substr(0, tokenPosition));
					subStrings[i].erase(0, tokenPosition + 1);
				} while (tokenPosition != std::string::npos);

				//add to face array
				faceArray.push_back(glm::vec3(atoi(subNumbers[0].c_str()) - 1,
										      atoi(subNumbers[1].c_str()) - 1,
										      atoi(subNumbers[2].c_str()) - 1));

				//clear numbers for next use
				subNumbers.clear();

			}

		}

		//clear the sub strings for next use
		subStrings.clear();

	}

	//close model file
	file.close();

	//---------------------------------
	//sift through all data for EBO
	//---------------------------------

	//loop through all triangle faces and individually build vertex groups out of them
	//then add each vertex group to the array but first check if it's already there and
	//if it is then skip it but mark EBO to point to that existing index
	//this alleviates the problem of creating a EBO out of OBJ model file data
	for (size_t i = 0; i < faceArray.size(); i++)
	{

		//create a temporary group
		Groups tri;
		tri.vertex = vertexArray[(GLuint)faceArray[i].x];
		tri.texture = textureArray[(GLuint)faceArray[i].y];
		tri.normal = normalArray[(GLuint)faceArray[i].z];

		//flag for element found
		bool isFound = false;

		//set below for-loop starting point to always go 5 elements back
		//so that we don't loop through entire group array each time
		int loopStart = (m_groups.size() >= 5 ? m_groups.size() - 5 : 0);

		//loop through existing groups to see if this group already exists in there
		//and if its found use that index for the EBO otherwise continue searching
		for (size_t j = loopStart; j < m_groups.size(); j++)
		{
					
			if (tri.vertex == m_groups[j].vertex &&
				tri.texture == m_groups[j].texture &&
				tri.normal == m_groups[j].normal)
			{
				m_indices.push_back(j);
				isFound = true;
				break;
			}	

		}

		//if nothing was found, it's a new group so add it and index the EBO
		if (!isFound)
		{
			m_groups.push_back(tri);
			m_indices.push_back(m_groups.size() - 1);
		}

	}

	//stats for vertices saved
	Debug::Log((GLfloat)m_indices.size(), "Total vertices");
	Debug::Log((GLfloat)m_groups.size(), "Actual vertices");

	int savedVerts = 100 - (int)((GLfloat)(m_groups.size()) /
		                         (GLfloat)(m_indices.size()) * 100);

	Debug::Log((GLfloat)savedVerts, "Vertex space saved %");
	
	//display text to state that file has been opened and read
	Debug::Log("File opened and read successfully.", Debug::ErrorCode::SUCCESS);
	Debug::Log("===============================================================");
	
	//---------------------------------
	//add all data to VBOs
	//---------------------------------

	//add all vertex, texture and normal data to the main vectors
	//from here this data will be fed into to VBO later on
	//add default white color as well in case models are NOT lit!
	for (size_t j = 0; j < m_groups.size(); j++)
	{
		
		m_vertices.push_back(m_groups[j].vertex.x);
		m_vertices.push_back(m_groups[j].vertex.y);
		m_vertices.push_back(m_groups[j].vertex.z);

		m_colors.push_back(1.0f);
		m_colors.push_back(1.0f);
		m_colors.push_back(1.0f);
		m_colors.push_back(1.0f);

		m_normals.push_back(m_groups[j].normal.x);
		m_normals.push_back(m_groups[j].normal.y);
		m_normals.push_back(m_groups[j].normal.z);

		m_textures.push_back(m_groups[j].texture.s);
		m_textures.push_back(m_groups[j].texture.t);

	}

	//create VAO, VBOs and EBO
	m_buffer.CreateBuffers(bufferID, m_indices.size(), true);

	//bind EBO and VBO to VAO
	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGBA, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::NORMAL_BUFFER, "normalIn", Buffer::XYZ, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::TEXTURE_BUFFER, "textureIn", Buffer::UV, Buffer::FLOAT);

	//fill EBO and all VBOs with data
	m_buffer.FillEBO(&m_indices[0], m_indices.size() * sizeof(GLuint));
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, &m_vertices[0], m_vertices.size() * sizeof(GLfloat));
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, &m_colors[0], m_colors.size() * sizeof(GLfloat));
	m_buffer.FillVBO(Buffer::NORMAL_BUFFER, &m_normals[0], m_normals.size() * sizeof(GLfloat));
	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, &m_textures[0], m_textures.size() * sizeof(GLfloat));

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that loads in texture file for model
//------------------------------------------------------------------------------------------------------
bool Model::LoadTexture(const std::string& filename, const std::string textureID)
{

	return m_texture.Load(filename, textureID);

}
//------------------------------------------------------------------------------------------------------
//function that removes model's buffer data from memory
//------------------------------------------------------------------------------------------------------
void Model::UnloadModel(const std::string bufferID)
{

	m_buffer.DestroyBuffers(bufferID);

}
//------------------------------------------------------------------------------------------------------
//function that removes model's texture data from memory
//------------------------------------------------------------------------------------------------------
void Model::UnloadTexture(const std::string textureID)
{

	m_texture.Unload(textureID);

}
//------------------------------------------------------------------------------------------------------
//function that sends material properties to fragment shader and renders the model
//------------------------------------------------------------------------------------------------------
void Model::Draw()
{

	m_texture.Bind();
	m_material.SendToShader();
	m_buffer.Draw(Buffer::TRIANGLES);

}