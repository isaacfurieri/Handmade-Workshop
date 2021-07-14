#include <assert.h>
#include <fstream>
#include "Material.h"
#include "Shader.h"
#include "Utility.h"

std::string Material::s_rootFolder = "Assets/Materials/";
std::map<std::string, Material> Material::s_materials;
//======================================================================================================
//This function will load a .mat file with a set of 
//pre-defined materials in there for default settings
bool Material::LoadMaterials(const std::string& filename)
{
	if (filename.empty())
	{
		return false;
	}

	std::fstream file(s_rootFolder + filename, std::ios_base::in);

	if (!file)
	{
		Utility::Log(MESSAGE_BOX, 
			"Error loading material file \"" + (s_rootFolder + filename) + "\"." 
			"Possible causes could be a corrupt or missing file. It could also be " 
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::FAILURE);
		return false;
	}

	std::string line;
	Material material;
	std::vector<std::string> subStrings_1;
	std::vector<std::string> subStrings_2;
	subStrings_1.reserve(5);
	subStrings_2.reserve(5);

	while (!file.eof())
	{
		subStrings_1.clear();
		subStrings_2.clear();
		std::getline(file, line);

		if (!line.empty())
		{
			//This means we have reached a block of material data
			if (line[0] == '[')
			{
				Utility::RemoveCharacter(line, '[');
				Utility::RemoveCharacter(line, ']');
				material.SetName(line);
				continue;
			}

			Utility::ParseString(line, subStrings_1, '=');

			if (subStrings_1[0] == "ambient")
			{
				Utility::ParseString(subStrings_1[1], subStrings_2, ',');
				material.SetAmbient(std::stof(subStrings_2[0]),
					std::stof(subStrings_2[1]),
					std::stof(subStrings_2[2]));
				continue;
			}

			if (subStrings_1[0] == "diffuse")
			{
				Utility::ParseString(subStrings_1[1], subStrings_2, ',');
				material.SetDiffuse(std::stof(subStrings_2[0]),
					std::stof(subStrings_2[1]),
					std::stof(subStrings_2[2]));
				continue;
			}

			if (subStrings_1[0] == "specular")
			{
				Utility::ParseString(subStrings_1[1], subStrings_2, ',');
				material.SetSpecular(std::stof(subStrings_2[0]),
					std::stof(subStrings_2[1]),
					std::stof(subStrings_2[2]));
				continue;
			}

			if (subStrings_1[0] == "shininess")
			{
				material.SetShininess(std::stof(subStrings_1[1]) * 128.0f);
				s_materials[material.GetName()] = material;
			}
		}
	}

	file.close();
	return true;
}
//======================================================================================================
//This function will load a .mtl file and store 
//all materials into the passed material container
bool Material::LoadMaterials(std::vector<Material>& materials, const std::string& filename)
{
	if (filename.empty())
	{
		return false;
	}

	std::fstream file(s_rootFolder + filename, std::ios_base::in);

	if (!file)
	{
		Utility::Log(MESSAGE_BOX,
			"Error loading material file \"" + (s_rootFolder + filename) + "\"."
			"Possible causes could be a corrupt or missing file. It could also be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::FAILURE);
		return false;
	}

	std::string line;
	std::vector<std::string> subStrings;
	subStrings.reserve(5);

	while (!file.eof())
	{
		getline(file, line);
		subStrings.clear();

		if (!line.empty())
		{
			Utility::ParseString(line, subStrings, ' ');

			//Add the material into the container. All properties from now will add to this
			//material which is the start of a material grouping matching the OBJ grouping
			if (subStrings[0] == "newmtl")
			{
				materials.push_back(Material());
				materials.back().SetName(subStrings[1]);
				continue;
			}

			//Ambient RGB values
			if (subStrings[0] == "Ka")
			{
				materials.back().SetAmbient(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3]));
				continue;
			}

			//Diffuse RGB values
			if (subStrings[0] == "Kd")
			{
				materials.back().SetDiffuse(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3]));
				continue;
			}

			//Specular RGB values
			if (subStrings[0] == "Ks")
			{
				materials.back().SetSpecular(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3]));
				continue;
			}

			//Transmittance RGB values which is the ratio of the light 
			//energy falling on a surface to that transmitted through it
			if (subStrings[0] == "Kt")
			{
				materials.back().SetTransmittance(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3]));
				continue;
			}

			//Emission RGB values
			if (subStrings[0] == "Ke")
			{
				materials.back().SetEmission(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3]));
				continue;
			}

			//Refractive index scalar value which is the measure of the 
			//bending of light when passing from one medium into another
			if (subStrings[0] == "Ni")
			{
				materials.back().SetRefractiveIndex(std::stof(subStrings[1]));
				continue;
			}

			//Specular exponent or shininess value (possible 0 - 1000)
			if (subStrings[0] == "Ns")
			{
				materials.back().SetShininess(std::stof(subStrings[1]));
				continue;
			}

			//Ambient texture file
			if (subStrings[0] == "map_Ka")
			{
				materials.back().SetAmbientMap(subStrings[1]);
				continue;
			}

			//Diffuse texture file
			if (subStrings[0] == "map_Kd")
			{
				materials.back().SetDiffuseMap(subStrings[1]);
				continue;
			}

			//Specular texture file
			if (subStrings[0] == "map_Ks")
			{
				materials.back().SetSpecularMap(subStrings[1]);
				continue;
			}

			//Normal texture file
			if (subStrings[0] == "map_Ns" || subStrings[0] == "bump")
			{
				materials.back().SetNormalMap(subStrings[1]);
				continue;
			}
		}
	}

	file.close();
	return true;
}
//======================================================================================================
Material::Material()
{
	m_isTextured = false;
	m_shininess = 1.0f;
	m_refractiveIndex = 0.0f;
	m_ambient = glm::vec3(0.0f);
	m_diffuse = glm::vec3(0.0f);
	m_specular = glm::vec3(0.0f);
	m_emission = glm::vec3(0.0f);
	m_transmittance = glm::vec3(1.0f);
}
//======================================================================================================
Material::~Material()
{
	//TODO - We need to unload these somewhere
	/*m_ambientMap.Unload();
	m_diffuseMap.Unload();
	m_specularMap.Unload();
	m_normalMap.Unload();*/
}
//======================================================================================================
const std::string& Material::GetName() const
{
	return m_name;
}
//======================================================================================================
const Texture& Material::GetNormalMap() const
{
	return m_normalMap;
}
//======================================================================================================
const Texture& Material::GetAmbientMap() const
{
	return m_ambientMap;
}
//======================================================================================================
const Texture& Material::GetDiffuseMap() const
{
	return m_diffuseMap;
}
//======================================================================================================
const Texture& Material::GetSpecularMap() const
{
	return m_specularMap;
}
//======================================================================================================
void Material::SetName(const std::string& name)
{
	m_name = name;
}
//======================================================================================================
void Material::SetMaterial(const std::string& name)
{
	*this = s_materials[name];
}
//======================================================================================================
bool Material::IsTextured() const
{
	return m_isTextured;
}
//======================================================================================================
void Material::SetNormalMap(const std::string& filename)
{
	//TODO - Find a better way to ID the texture
	m_normalMap.Load(filename, filename);
	m_isTextured = true;
}
//======================================================================================================
void Material::SetAmbientMap(const std::string& filename)
{
	//TODO - Find a better way to ID the texture
	m_ambientMap.Load(filename, filename);
	m_isTextured = true;
}
//======================================================================================================
void Material::SetDiffuseMap(const std::string& filename)
{
	//TODO - Find a better way to ID the texture
	m_diffuseMap.Load(filename, filename);
	m_isTextured = true;
}
//======================================================================================================
void Material::SetSpecularMap(const std::string& filename)
{
	//TODO - Find a better way to ID the texture
	m_specularMap.Load(filename, filename);
	m_isTextured = true;
}
//======================================================================================================
void Material::SetShininess(GLfloat shininess)
{
	m_shininess = shininess;
}
//======================================================================================================
void Material::SetRefractiveIndex(GLfloat refractiveIndex)
{
	m_refractiveIndex = refractiveIndex;
}
//======================================================================================================
void Material::SetAmbient(const glm::vec3& ambient)
{
	m_ambient = ambient;
}
//======================================================================================================
void Material::SetAmbient(GLfloat r, GLfloat g, GLfloat b)
{
	m_ambient.r = r;
	m_ambient.g = g;
	m_ambient.b = b;
}
//======================================================================================================
void Material::SetDiffuse(const glm::vec3& diffuse)
{
	m_diffuse = diffuse;
}
//======================================================================================================
void Material::SetDiffuse(GLfloat r, GLfloat g, GLfloat b)
{
	m_diffuse.r = r;
	m_diffuse.g = g;
	m_diffuse.b = b;
}
//======================================================================================================
void Material::SetSpecular(const glm::vec3& specular)
{
	m_specular = specular;
}
//======================================================================================================
void Material::SetSpecular(GLfloat r, GLfloat g, GLfloat b)
{
	m_specular.r = r;
	m_specular.g = g;
	m_specular.b = b;
}
//======================================================================================================
void Material::SetEmission(const glm::vec3& emission)
{
	m_emission = emission;
}
//======================================================================================================
void Material::SetEmission(GLfloat r, GLfloat g, GLfloat b)
{
	m_emission.r = r;
	m_emission.g = g;
	m_emission.b = b;
}
//======================================================================================================
void Material::SetTransmittance(const glm::vec3& transmittance)
{
	m_transmittance = transmittance;
}
//======================================================================================================
void Material::SetTransmittance(GLfloat r, GLfloat g, GLfloat b)
{
	m_transmittance.r = r;
	m_transmittance.g = g;
	m_transmittance.b = b;
}
//======================================================================================================
void Material::SendToShader(Shader& shader)
{
	shader.SendData("material.ambient", m_ambient);
	shader.SendData("material.diffuse", m_diffuse);
	shader.SendData("material.specular", m_specular);
	shader.SendData("material.shininess", m_shininess);
}