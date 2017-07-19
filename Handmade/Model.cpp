#include <fstream>
#include <iostream>
#include "Model.h"
#include "TextureManager.h"
#include "Tools.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Model::Model()
{

	//assign ID to a default 0
	m_textureID = 0;

	//set texture color to a default white color
	m_color = Color::WHITE;

	//set the component sizes for the model object's vertex and color data
	m_buffer.SetComponentSize(Buffer::VERTEX_BUFFER, Buffer::XYZ);
	m_buffer.SetComponentSize(Buffer::COLOR_BUFFER, Buffer::RGBA);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns color of model
//------------------------------------------------------------------------------------------------------
void Model::SetColor(Color& color)
{

	//variable to store size of model's internal buffer's color vector
	int bufferSize = 0;

	//first set color of model
	m_color = color;

	//assign buffer size value by dividing color vector size by component size
	//this gives us the actual amounts of color groupings for each vertex 
	bufferSize = m_buffer.Colors().size() / Buffer::RGBA;
	
	//clear the color vector for fresh use
	m_buffer.Colors().clear();

	//loop through each color grouping and change the RGBA values 
	//of each vertex color component based on color set above
	for (int i = 0; i < bufferSize; i++)
	{
		m_buffer.Colors().push_back(m_color.R);
		m_buffer.Colors().push_back(m_color.G);
		m_buffer.Colors().push_back(m_color.B);
		m_buffer.Colors().push_back(m_color.A);
	}

	//fill VBO buffer with color data
	m_buffer.FillData(Buffer::COLOR_BUFFER);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns texture image ID to model based on index value passed
//------------------------------------------------------------------------------------------------------
void Model::SetTextureID(const std::string& mapIndex)
{

	m_textureID = TheTexture::Instance()->GetTextureID(mapIndex);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns VBO IDs based on ID names passed
//------------------------------------------------------------------------------------------------------
void Model::SetBufferID(const std::string& vertexID, const std::string& colorID,
	                    const std::string& textureID, const std::string& normalID)
{

	m_buffer.SetBufferID(Buffer::VERTEX_BUFFER, vertexID);
	m_buffer.SetBufferID(Buffer::COLOR_BUFFER, colorID);
	m_buffer.SetBufferID(Buffer::TEXTURE_BUFFER, textureID);
	m_buffer.SetBufferID(Buffer::NORMAL_BUFFER, normalID);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns shader attribute IDs based on attribute names passed
//------------------------------------------------------------------------------------------------------
void Model::SetShaderAttribute(const std::string& vertexAttr, const std::string& colorAttr,
	                           const std::string& textureAttr, const std::string& normalAttr)
{

	m_buffer.SetAttributeID(Buffer::VERTEX_BUFFER, vertexAttr);
	m_buffer.SetAttributeID(Buffer::COLOR_BUFFER, colorAttr);
	m_buffer.SetAttributeID(Buffer::TEXTURE_BUFFER, textureAttr);
	m_buffer.SetAttributeID(Buffer::NORMAL_BUFFER, normalAttr);

}
//------------------------------------------------------------------------------------------------------
//function that opens, loads and stores OBJ and MTL model file data based on filenames passed
//------------------------------------------------------------------------------------------------------
bool Model::LoadFromFile(const std::string& OBJfilename, const std::string& MTLfilename)
{

	//variables for storing various string text from 
	//model files and temporary model data values
	std::fstream file;
	std::string lineText = "";
	std::string materialName = "";

	std::vector<std::string> subStrings;
	std::vector<std::string> subNumbers;

	std::vector<glm::vec3> tempFaces;
	std::vector<glm::vec2> tempUVs;
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec3> tempNormals;

	//-----------------------------------------------------------------------------------------------------
	//OBJ FILE
	//-----------------------------------------------------------------------------------------------------

	//display text to state that file is being opened and read
	std::cout << "Opening and reading model file : " << "\"" << OBJfilename << "\"" << std::endl;

	//open model file
	file.open(OBJfilename);

	//if opening of model file failed, display error message
	if (!file)
	{
		std::cout << "File could not be loaded." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
		return false;
	}

	//read in all model data until end of file is reached
	while (!file.eof())
	{

		//read line of text
		getline(file, lineText);

		//break text string into smaller substrings
		ParseString(lineText, subStrings, ' ');

		//if first token is "g", create a new group
		/*if(subStrings[0] == "g")
		{
			groupName = subStrings[1];
			m_model->Groups()[groupName] = new Group;
		}*/

		//if first token is "v" or "vt", set the vertices and normal values
		if (subStrings[0] == "v" || subStrings[0] == "vn")
		{

			glm::vec3 v((GLfloat)(atof(subStrings[1].c_str())),
				        (GLfloat)(atof(subStrings[2].c_str())),
				        (GLfloat)(atof(subStrings[3].c_str())));

			if (subStrings[0] == "v")  tempVertices.push_back(v);
			if (subStrings[0] == "vn") tempNormals.push_back(v);

		}

		//if first token is "vt", set the UV data
		if (subStrings[0] == "vt")
		{

			glm::vec2 UVs((GLfloat)(atof(subStrings[1].c_str())),
				          (GLfloat)(atof(subStrings[2].c_str())));

			tempUVs.push_back(UVs);

		}

		//if first token is "f", create a new face and set the face data
		if (subStrings[0] == "f")
		{

			//loop through all three face sub strings 
			for (int i = 1; i <= 3; i++)
			{

				//break each face substring into three face numeric values
				ParseString(subStrings[i], subNumbers, '/');

				glm::vec3 v(atoi(subNumbers[0].c_str()) - 1,
					        atoi(subNumbers[1].c_str()) - 1,
					        atoi(subNumbers[2].c_str()) - 1);

				tempFaces.push_back(v);
				subNumbers.clear();

			}
			
		}

		//if first token is "usemtl", create a new group and assign the material name
		/*if (subStrings[0] == "usemtl")
		{
			modelData->Groups().push_back(new Group);
			modelData->Groups()[modelData->Groups().size() - 1]->materialName = subStrings[1];
		}*/

		//clear the sub strings for next use
		subStrings.clear();

	}

	//close model file
	file.close();

	//display text to state that file has been opened and read
	std::cout << "File opened and read successfully." << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	//-----------------------------------------------------------------------------------------------------
	//MTL FILE
	//-----------------------------------------------------------------------------------------------------
	
	//display text to state that file is being opened and read
	std::cout << "Opening and reading material file : " << "\"" << MTLfilename << "\"" << std::endl;
	
	//open material file
	file.open(MTLfilename);

	//if opening of material file failed, display error message
	if (!file)
	{
		std::cout << "File could not be loaded." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
		return false;
	}

	//read in all material data until end of file is reached
	while (!file.eof())
	{

		//read line of text
		getline(file, lineText);

		//break text string into smaller substrings
		ParseString(lineText, subStrings, ' ');

		//if first token is "newmtl", add a new material object to map
		if (subStrings[0] == "newmtl")
		{
			materialName = subStrings[1];
			m_materials[materialName] = new Material();
		}

		//if first token is "illum", set the illumination value
		if (subStrings[0] == "illum")
		{
			m_materials[materialName]->illum = atoi(subStrings[1].c_str());
		}

		//if first token is "Ka", "Kd" or "Ks", set the ambient, diffuse or specular material values
		if (subStrings[0] == "Ka" || subStrings[0] == "Kd" || subStrings[0] == "Ks")
		{

			//create temporary vector to hold converted float values
			glm::vec4 K;

			K.x = (GLfloat)(atof(subStrings[1].c_str()));
			K.y = (GLfloat)(atof(subStrings[2].c_str()));
			K.z = (GLfloat)(atof(subStrings[3].c_str()));

			//if the alpha value is included, add it
			if (subStrings.size() == 5)
			{
				K.w = (GLfloat)(atof(subStrings[4].c_str()));
			}

			//based on what material property is being set, assign appropriate values
			if (subStrings[0] == "Ka") m_materials[materialName]->ambient = K;
			if (subStrings[0] == "Kd") m_materials[materialName]->diffuse = K;
			if (subStrings[0] == "Ks") m_materials[materialName]->specular = K;

		}

		//if first token is "Ns", set the shininess value
		if (subStrings[0] == "Ns")
		{
			m_materials[materialName]->shininess = (GLfloat)(atof(subStrings[1].c_str()));
		}

		//clear the substrings for next use
		subStrings.clear();

	}

	//close material file
	file.close();

	//display text to state that file has been opened and read
	std::cout << "File opened and read successfully." << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	//loop through all faces stored and individually put all data 
	//read in above into the model's internal buffer object
	for (auto it = tempFaces.begin(); it != tempFaces.end(); it++)
	{

		//add all vertex data
		m_buffer.Vertices().push_back(tempVertices[(unsigned int)it->x].x);
		m_buffer.Vertices().push_back(tempVertices[(unsigned int)it->x].y);
		m_buffer.Vertices().push_back(tempVertices[(unsigned int)it->x].z);

		//add all texture coordinate data
		m_buffer.Textures().push_back(tempUVs[(unsigned int)it->y].x);
		m_buffer.Textures().push_back(tempUVs[(unsigned int)it->y].y);

		//add all normal data
		m_buffer.Normals().push_back(tempNormals[(unsigned int)it->z].x);
		m_buffer.Normals().push_back(tempNormals[(unsigned int)it->z].y);
		m_buffer.Normals().push_back(tempNormals[(unsigned int)it->z].z);

		//add all color data
		//should be based on MTL material colors (fix later!)
		m_buffer.Colors().push_back(m_color.R);
		m_buffer.Colors().push_back(m_color.G);
		m_buffer.Colors().push_back(m_color.B);
		m_buffer.Colors().push_back(m_color.A);

	}

	//fill VBOs with the vertex, color, texture coordinate and normal data
	m_buffer.FillData(Buffer::VERTEX_BUFFER);
	m_buffer.FillData(Buffer::COLOR_BUFFER);
	m_buffer.FillData(Buffer::TEXTURE_BUFFER);
	m_buffer.FillData(Buffer::NORMAL_BUFFER);

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that binds the texture, fills the VBO buffer and draws the model
//------------------------------------------------------------------------------------------------------
void Model::Draw()
{

	//bind texture with model based on texture ID
	TheTexture::Instance()->Enable(m_textureID);

	//send model data to shaders
	m_buffer.DrawData(Buffer::TRIANGLES);

	//unbind texture so that there are no left over links
	TheTexture::Instance()->Disable();

}