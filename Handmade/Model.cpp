#include <assert.h>
#include <fstream>
#include <unordered_map>
#include "Model.h"
#include "Shader.h"
#include "Utility.h"

std::string Model::s_rootFolder = "Assets/Models/";
//======================================================================================================
Model::Model()
{
	m_dimension = glm::vec3(0.0f);
}
//======================================================================================================
bool Model::Load(const std::string& filename, bool isNormalized, const std::string& defaultMaterial)
{
	if (filename.empty())
	{
		return false;
	}

	std::fstream file(s_rootFolder + filename, std::ios_base::in);

	if (!file)
	{
		Utility::Log(MESSAGE_BOX,
			"Error loading model file \"" + (s_rootFolder + filename) + "\"."
			"Possible causes could be a corrupt or missing file. It could also be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::FAILURE);
		return false;
	}

	Mesh rawMesh;
	Material lastMaterial;

	std::string line;
	std::string lastName;
	std::vector<Face> faces;

	std::vector<std::string> subStrings;
	subStrings.reserve(10);

	while (!file.eof())
	{
		std::getline(file, line);
		subStrings.clear();

		//Only process data that is not blank or intended to be a comment
		if (!line.empty() && line[0] != '#')
		{
			Utility::ParseString(line, subStrings, ' ');

			//Vertex data
			if (subStrings[0] == "v")
			{
				rawMesh.vertices.push_back(glm::vec3(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3])));
				continue;
			}

			//Normal data
			if (subStrings[0] == "vn")
			{
				rawMesh.normals.push_back(glm::vec3(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3])));
				continue;
			}

			//Texture coordinate data
			if (subStrings[0] == "vt")
			{
				rawMesh.textureCoords.push_back(glm::vec2(std::stof(subStrings[1]),
					std::stof(subStrings[2])));
				continue;
			}

			//This is the line of face indices that contains data in 'v/t/n v/t/n v/t/n' format
			//This data together will make up a polygon face or triangle using the vtn indices
			//The data will be stored as v = subString[1], t = subString[2] and n = subString[3] 
			if (subStrings[0] == "f")
			{
				Face face;
				std::vector<std::string> numbers;
				numbers.reserve(10);

				//Parse face indices into individual index numbers so 1/2/3 becomes 1, 2 and 3
				//We subtract 1 because the index values in the .obj file are not zero-based
				for (int i = 1; i <= 3; i++)
				{
					numbers.clear();
					VertexGroup vertexGroup;
					Utility::ParseString(subStrings[i], numbers, '/');

					vertexGroup.v = std::stoi(numbers[0]) - 1;

					//Some .obj files do not contain texture coordinate data 
					//so only add a texture index if there is one present
					if (numbers.size() > 2)
					{
						vertexGroup.t = std::stoi(numbers[1]) - 1;
						vertexGroup.n = std::stoi(numbers[2]) - 1;
					}

					else
					{
						vertexGroup.n = std::stoi(numbers[1]) - 1;
					}

					face.push_back(vertexGroup);
				}

				faces.push_back(face);
				continue;
			}

			//This is the name of the material to use for the group 
			//All materials are found in the subsequent .mtl file
			if (subStrings[0] == "usemtl")
			{
				if (!m_materials.empty())
				{
					for (size_t i = 0; i < m_materials.size(); ++i)
					{
						if (m_materials[i].GetName() == subStrings[1])
						{
							lastMaterial = m_materials[i];
							break;
						}
					}
				}

				continue;
			}

			//This indicates the name of the .mtl file to use for the mesh 
			//group. All materials are found in the subsequent material file
			//Note that sometimes the material file might not be found
			if (subStrings[0] == "mtllib")
			{
				Material::LoadMaterials(m_materials, subStrings[1]);
				continue;
			}

			//This indicates mesh groups or objects within 
			//the model which will make up the final model 
			if (subStrings[0] == "g" || subStrings[0] == "o")
			{
				//Go through all previously loaded faces 
				//and build a mesh from the previous group
				if (!faces.empty())
				{
					Mesh mesh;

					mesh.vertices.reserve(rawMesh.vertices.size());
					mesh.textureCoords.reserve(rawMesh.textureCoords.size());
					mesh.normals.reserve(rawMesh.normals.size());

					mesh.name = lastName;
					mesh.material = lastMaterial;
					SortVertexData(mesh, rawMesh, faces);
					m_meshes.push_back(mesh);
				}

				//Make a note of the group name for the next mesh group
				lastName = subStrings[1];
				faces.clear();

				//TODO - Find a way to clear data that's 
				//no longer required from the raw mesh 
				//Not sure why this does not work?
				//rawMesh.vertices.clear();
				//rawMesh.textureCoords.clear();
				//rawMesh.normals.clear();

				continue;
			}

			//These are the smoothing groups
			if (subStrings[0] == "s")
			{
				//TODO
				continue;
			}
		}
	}

	file.close();

	//We do one more final clean-up of the raw data because v/t/n data is
	//usually read in AFTER a group name so the final data group needs sorting
	if (!faces.empty())
	{
		Mesh mesh;
		mesh.name = lastName;
		mesh.material = lastMaterial;
		SortVertexData(mesh, rawMesh, faces);
		m_meshes.push_back(mesh);
	}

	//Check if any materials were loaded because there may be a 'mtllib' 
	//statement missing. This means that no materials, not even default 
	//ones are loaded so as a last resort, we add a default material
	if (m_materials.empty())
	{
		Material material;
		material.SetMaterial(defaultMaterial);

		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i].material = material;
		}
	}

	//Make sure the model has a normalized width, height and depth if required
	if (isNormalized)
	{
		Normalize();
	}

	//Get the new max lengths

	glm::vec3 minValues = glm::vec3(0.0f);
	glm::vec3 maxValues = glm::vec3(0.0f);

	for (size_t i = 0; i < m_meshes.size(); i++)
	{
		for (size_t j = 0; j < m_meshes[i].vertices.size(); j++)
		{
			maxValues = glm::max(maxValues, m_meshes[i].vertices[j]);
			minValues = glm::min(minValues, m_meshes[i].vertices[j]);
		}
	}

	m_dimension = maxValues - minValues;

	FillBuffers();
	return true;
}
//======================================================================================================
const glm::vec3& Model::GetDimension() const
{
	return m_dimension;
}
//======================================================================================================
void Model::SetColor(const glm::vec4& color)
{
	SetColor(color.r, color.g, color.b, color.a);
}
//======================================================================================================
void Model::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	for (size_t i = 0; i < m_meshes.size(); i++)
	{
		for (size_t j = 0; j < m_meshes[i].colors.size(); j++)
		{
			glm::vec4 color(r, g, b, a);
			m_meshes[i].colors[j] = color;
		}

		m_buffers[i].FillVBO(Buffer::COLOR_BUFFER, &m_meshes[i].colors[0].x, 
			m_meshes[i].colors.size() * sizeof(glm::vec4));
	}
}
//======================================================================================================
void Model::FillBuffers()
{
	//We have to create separate buffer objects if the .obj file data has separate groups
	//because of how the indices have been set up. Single group models will use one buffer
	//We can use one buffer for all data but then the indices have to be calculated differently
	for (size_t i = 0; i < m_meshes.size(); i++)
	{
		Buffer buffer;

		//TODO - Need to label each buffer object properly
		static auto count = 0;
		buffer.Create("Mesh_" + std::to_string(count++), m_meshes[i].indices.size(), true);

		buffer.FillEBO(&m_meshes[i].indices[0], m_meshes[i].indices.size() * sizeof(GLuint));
		buffer.FillVBO(Buffer::VERTEX_BUFFER, &m_meshes[i].vertices[0].x, m_meshes[i].vertices.size() * sizeof(glm::vec3));
		buffer.FillVBO(Buffer::NORMAL_BUFFER, &m_meshes[i].normals[0].x, m_meshes[i].normals.size() * sizeof(glm::vec3));

		//Fill the color buffer with a default white color 
		//For each vertex in the mesh there is a color value
		for (size_t j = 0; j < m_meshes[i].vertices.size(); j++)
		{
			glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
			m_meshes[i].colors.push_back(color);
		}

		buffer.FillVBO(Buffer::COLOR_BUFFER, &m_meshes[i].colors[0].x, m_meshes[i].colors.size() * sizeof(glm::vec4));

		if (!m_meshes[i].textureCoords.empty())
		{
			buffer.FillVBO(Buffer::TEXTURE_BUFFER, &m_meshes[i].textureCoords[0].x, 
				m_meshes[i].textureCoords.size() * sizeof(glm::vec2));
		}

		m_buffers.push_back(buffer);
	}
}
//======================================================================================================
void Model::SortVertexData(Mesh& newMesh, const Mesh& oldMesh, const std::vector<Face>& faces)
{
	GLuint count = 0;
	std::unordered_map<VertexGroup, GLuint, HashFunction> map; 

	//Because the .obj file does not have any EBO data or any indices
	//this needs to be manually created. The raw .obj data will consist
	//of different amounts of vertex, UV and normal data. To use an EBO
	//we need to make sure the v/t/n VBO buffer sizes are all equal
	for (size_t i = 0; i < faces.size(); i++)
	{
		//We need to loop through all three v/t/n groupings for each face
		//because all three v/t/n groupings together make up a face triangle
		//We then see if the grouping is already in the map because groupings
		//can duplicate in the .obj. For example we could have 2/2/2 in the
		//.obj file multiple times, so we don't want to store duplicates
		for (size_t j = 0; j < 3; j++)
		{
			auto it = map.find(faces[i][j]);

			if (it == map.end())
			{
				glm::vec3 v = oldMesh.vertices[faces[i][j].v];
				newMesh.vertices.push_back(v);

				//Some .obj files do not have texture coordinates 
				if (!oldMesh.textureCoords.empty())
				{
					newMesh.textureCoords.push_back(oldMesh.textureCoords[faces[i][j].t]);
				}

				newMesh.normals.push_back(oldMesh.normals[faces[i][j].n]);
				newMesh.indices.push_back(count);

				map[faces[i][j]] = count;

				count++;

				if (count % 10 == 0)
				{
					map.clear();
				}
			}

			else
			{
				newMesh.indices.push_back(it->second);
			}
		}
	}
}
//======================================================================================================
void Model::Render(Shader& shader)
{
	for (size_t i = 0; i < m_meshes.size(); i++)
	{
		m_buffers[i].LinkEBO();
		m_buffers[i].LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
		m_buffers[i].LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);
		m_buffers[i].LinkVBO(shader.GetAttributeID("textureIn"), Buffer::TEXTURE_BUFFER, Buffer::UV, Buffer::FLOAT);
		m_buffers[i].LinkVBO(shader.GetAttributeID("normalIn"), Buffer::NORMAL_BUFFER, Buffer::XYZ, Buffer::FLOAT);

		m_meshes[i].material.SendToShader(shader);

		if (m_meshes[i].material.IsTextured())
		{
			shader.SendData("isTextured", true);
			m_meshes[i].material.GetDiffuseMap().Bind();
		}

		else
		{
			shader.SendData("isTextured", false);
		}

		m_buffers[i].Render(Buffer::TRIANGLES);
	}
}
//======================================================================================================
void Model::Unload()
{
	for (size_t i = 0; i < m_buffers.size(); i++)
	{
		m_buffers[i].Destroy();
	}

	m_meshes.clear();
	m_materials.clear();
}
//======================================================================================================
void Model::Normalize()
{
	glm::vec3 minValues = glm::vec3(0.0f);
	glm::vec3 maxValues = glm::vec3(0.0f);

	for (auto& mesh : m_meshes)
	{
		for (auto& vertex : mesh.vertices)
		{
			maxValues = glm::max(maxValues, vertex);
			minValues = glm::min(minValues, vertex);
		}
	}

	glm::vec3 length = maxValues - minValues;

	if (length == glm::vec3(0.0f))
	{
		return;
	}

	auto fraction = (1.0f / glm::max(glm::max(length.x, length.y), length.z));

	for (auto& mesh : m_meshes)
	{
		for (auto& vertex : mesh.vertices)
		{
			vertex *= fraction;
		}
	}
}