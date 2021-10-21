#pragma once

/*===================================================================#
| 'HandmadeView' source files last updated on 21 October 2021        |
#===================================================================*/

#include <memory>
#include <vector>
#include <glm.hpp>
#include "Axes.h"
#include "Audio.h"
#include "Cuboid.h"
#include "FreeCamera.h"
#include "Grid.h"
#include "Quad.h"
#include "Sphere.h"
#include "Shader.h"
#include "Light.h"
#include "Model.h"
#include "Text.h"

class CHandmadeView : public CView
{

public:

	CHandmadeView();
	virtual ~CHandmadeView() {}
	CHandmadeDoc* GetDocument() const;

private:

	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	afx_msg void OnAppExit();
	afx_msg void OnAppAbout();

	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	bool m_isLeftButtonDown;
	bool m_isRightButtonDown;
	bool m_isMiddleButtonDown;
	bool m_isScreenInitialized;

	int m_mouseWheelMotion;
	glm::ivec2 m_mouseMotion;
	glm::ivec2 m_mousePosition;

	std::unique_ptr<Grid> m_grid;
	std::unique_ptr<Axes> m_axes;

	std::unique_ptr<Text> m_topText;
	std::unique_ptr<Text> m_bottomText;
	std::unique_ptr<Text> m_axesLabelText;

	std::unique_ptr<Shader> m_mainShader;
	std::unique_ptr<Shader> m_textShader;
	std::unique_ptr<Shader> m_lightShader;

	std::unique_ptr<Shader> m_testShader;

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

	std::unique_ptr<FreeCamera> m_UICamera;
	std::unique_ptr<FreeCamera> m_mainCamera;

	std::vector<std::unique_ptr<Object>> m_objects;

	DECLARE_DYNCREATE(CHandmadeView)
	DECLARE_MESSAGE_MAP()

};