#pragma once

/*===================================================================#
| 'Material' source files last updated on 23 September 2021          |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include <map>
#include <string>
#include <vector>
#include <glm.hpp>
#include "glad.h"
#include "Shader.h"
#include "Texture.h"

class Material
{

public:

	static bool Load(const std::string& filename);
	static bool Load(std::vector<Material>& materials, 
		const std::string& filename);

	Material();
	~Material();

	const std::string& GetName() const;

	const Texture& GetNormalMap() const;
	const Texture& GetAmbientMap() const;
	const Texture& GetDiffuseMap() const;
	const Texture& GetSpecularMap() const;

	void SetName(const std::string& name);
	void SetMaterial(const std::string& name);

	bool IsTextured() const;

	void SetNormalMap(const std::string& filename);
	void SetAmbientMap(const std::string& filename);
	void SetDiffuseMap(const std::string& filename);
	void SetSpecularMap(const std::string& filename);

	void SetShininess(GLfloat shininess);
	void SetRefractiveIndex(GLfloat refractiveIndex);

	void SetAmbient(const glm::vec3& ambient);
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);

	void SetDiffuse(const glm::vec3& diffuse);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);

	void SetSpecular(const glm::vec3& specular);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

	void SetEmission(const glm::vec3& emission);
	void SetEmission(GLfloat r, GLfloat g, GLfloat b);

	void SetTransmittance(const glm::vec3& transmittance);
	void SetTransmittance(GLfloat r, GLfloat g, GLfloat b);

	//we send the shader in here so as to not pass into the ctor which causes other issues
	void SendToShader(Shader& shader);

private:

	bool m_isTextured;
	std::string m_name;

	GLfloat m_shininess;
	GLfloat m_refractiveIndex;

	Texture m_normalMap;
	Texture m_ambientMap;
	Texture m_diffuseMap;
	Texture m_specularMap;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	glm::vec3 m_emission;
	glm::vec3 m_transmittance;

	static std::string s_rootFolder;
	static std::map<std::string, Material> s_materials;

};