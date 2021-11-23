#pragma once

/*===================================================================#
| 'Design' source files last updated on 23 November 2021             |
#===================================================================*/

#include <memory>
#include <vector>
#include <glm.hpp>
#include "Audio.h"
#include "Axes.h"
#include "Cuboid.h"
#include "FreeCamera.h"
#include "Grid.h"
#include "Light.h"
#include "Model.h"
#include "Object.h"
#include "Quad.h"
#include "Sphere.h"
#include "Shader.h"
#include "State.h"
#include "Text.h"

class Design : public State
{

public:

	Design() {}
	virtual ~Design() {}

	virtual bool OnEnter();
	virtual State* Update(int deltaTime);
	virtual bool Render();
	virtual void OnExit();

private:

	std::unique_ptr<Grid> m_grid;
	std::unique_ptr<Axes> m_axes;

	std::unique_ptr<Text> m_topText;
	std::unique_ptr<Text> m_bottomText;
	std::unique_ptr<Text> m_axesLabelText;

	std::unique_ptr<Shader> m_mainShader;
	std::unique_ptr<Shader> m_textShader;
	std::unique_ptr<Shader> m_lightShader;

	std::unique_ptr<Shader> m_testShader;

	std::unique_ptr<FreeCamera> m_sceneCamera;
	std::unique_ptr<FreeCamera> m_consoleCamera;
	std::unique_ptr<FreeCamera> m_propertiesCamera;

	//For current testing===============================================
	/*std::unique_ptr<Audio> m_audio1;
	std::unique_ptr<Audio> m_audio2;
	std::unique_ptr<Audio> m_audio3;*/

	std::unique_ptr<Light> m_light;
	std::unique_ptr<Model> m_model;

	//std::unique_ptr<Quad> m_quad;
	//std::unique_ptr<Cuboid> m_cube;
	//std::unique_ptr<Sphere> m_sphere;

	//std::unique_ptr<Tile> m_labelX;
	//std::unique_ptr<Tile> m_labelY;
	//std::unique_ptr<Tile> m_labelZ;

	//Using static objects will enforce more copies being made 
	//especially if the vector container has not been reserved
	//Prefer to use smart pointer objects instead to avoid copies
	//std::vector<Text> m_text;
	//std::vector<Audio> m_audio;
	//==================================================================

	std::vector<std::unique_ptr<Object>> m_objects;

};