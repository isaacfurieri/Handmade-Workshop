#pragma once

/*===================================================================#
| 'Axes' source files last updated on 21 July 2021                   |
#===================================================================*/

#include "Buffer.h"
#include "Model.h"
#include "Object.h"
#include "Shader.h"

class Axes : public Object
{

public:

	Axes(const std::string& filenameModel);
	Axes(GLint size = 15, GLfloat lineWidth = 5.0f);
	virtual ~Axes();

	void SetSize(GLint size);
	void SetLineWidth(GLfloat lineWidth);

	//Not currently used
	//const glm::vec3& GetArrowTipPositionX();
	//const glm::vec3& GetArrowTipPositionY();
	//const glm::vec3& GetArrowTipPositionZ();

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader) {}

private:

	void Create();

	GLint m_size;
	bool m_isPrimitive;
	GLfloat m_lineWidth;
	
	Model m_model;
	Buffer m_buffer;

	//Not currently used
	//glm::vec3 m_arrowTipPositionX;
	//glm::vec3 m_arrowTipPositionY;
	//glm::vec3 m_arrowTipPositionZ;

};