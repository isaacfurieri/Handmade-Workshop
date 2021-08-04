#include "framework.h"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Handmade.h"
#endif

#include "Audio.h"
#include "HandmadeDoc.h"
#include "HandmadeView.h"
#include "Screen.h"
#include "Shader.h"
#include "Utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CHandmadeView, CView)

BEGIN_MESSAGE_MAP(CHandmadeView, CView)

	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

	ON_WM_SIZE()
	ON_WM_CREATE()

	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()

	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONUP()

	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()

END_MESSAGE_MAP()

//======================================================================================================
CHandmadeView::CHandmadeView() noexcept
{
	m_isScreenInitialized = false;

	m_mouseWheelMotion = 0;
	m_mouseMotion = glm::ivec2(0);
	m_mousePosition = glm::ivec2(0);

	m_isLeftButtonDown = false;
	m_isRightButtonDown = false;
	m_isMiddleButtonDown = false;
}
//======================================================================================================
CHandmadeView::~CHandmadeView()
{
}
//======================================================================================================
BOOL CHandmadeView::PreCreateWindow(CREATESTRUCT& cs)
{

	return CView::PreCreateWindow(cs);
}
//======================================================================================================
void CHandmadeView::OnSize(UINT nType, int cx, int cy)
{
	Screen::Instance()->SetResolution(cx, cy);
	Screen::Instance()->SetViewport(0, 0, cx, cy);
}
//======================================================================================================
int CHandmadeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	//Remove the thick edge from the main window. Not 
	//sure if there is another method of doing this?
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

	//===================================================================

	Utility::SetWindowHandle(GetSafeHwnd());

	//===================================================================

	if (!Screen::Instance()->Initialize(GetSafeHwnd(), "Data/Config.ini"))
	{
		return -1;
	}

	Screen::Instance()->SetColor(23U, 24U, 23U);

	m_isScreenInitialized = true;

	//===================================================================

	m_mainShader = std::make_unique<Shader>();

	if (!m_mainShader->Create("Shaders/Main.vert", "Shaders/Main.frag"))
	{
		return -1;
	}

	m_mainShader->BindAttribute("vertexIn");
	m_mainShader->BindAttribute("colorIn");
	m_mainShader->BindAttribute("textureIn");

	m_mainShader->BindUniform("model");
	m_mainShader->BindUniform("view");
	m_mainShader->BindUniform("projection");
	m_mainShader->BindUniform("isTextured");

	//===================================================================

	m_textShader = std::make_unique<Shader>();

	if (!m_textShader->Create("Shaders/Text.vert", "Shaders/Text.frag"))
	{
		return -1;
	}

	m_textShader->BindAttribute("vertexIn");
	m_textShader->BindAttribute("colorIn");
	m_textShader->BindAttribute("textureIn");
	
	m_textShader->BindUniform("model");
	m_textShader->BindUniform("view");
	m_textShader->BindUniform("projection");
	m_textShader->BindUniform("textureImage");

	//===================================================================

	m_lightShader = std::make_unique<Shader>();

	if (!m_lightShader->Create("Shaders/Light.vert", "Shaders/Light.frag"))
	{
		return false;
	}

	m_lightShader->BindAttribute("vertexIn");
	m_lightShader->BindAttribute("colorIn");
	m_lightShader->BindAttribute("textureIn");
	m_lightShader->BindAttribute("normalIn");

	m_lightShader->BindUniform("model");
	m_lightShader->BindUniform("view");
	m_lightShader->BindUniform("projection");
	m_lightShader->BindUniform("normal");

	m_lightShader->BindUniform("isTextured");
	m_lightShader->BindUniform("cameraPosition");

	m_lightShader->BindUniform("light.ambient");
	m_lightShader->BindUniform("light.diffuse");
	m_lightShader->BindUniform("light.specular");
	m_lightShader->BindUniform("light.position");

	m_lightShader->BindUniform("material.ambient");
	m_lightShader->BindUniform("material.diffuse");
	m_lightShader->BindUniform("material.specular");
	m_lightShader->BindUniform("material.shininess");

	//m_lightShader->BindUniform("light.attenuationLinear");
	//m_lightShader->BindUniform("light.attenuationConstant");
	//m_lightShader->BindUniform("light.attenuationQuadratic");

	//TEST CODE to be used later for multiple lights
	/*for (size_t i = 0; i < TOTAL_LIGHTS; i++)
	{
		std::string index = std::to_string(i);

		m_lightShader->BindUniform("lights[" + index + "].ambient");
		m_lightShader->BindUniform("lights[" + index + "].diffuse");
		m_lightShader->BindUniform("lights[" + index + "].specular");
		m_lightShader->BindUniform("lights[" + index + "].position");
		m_lightShader->BindUniform("lights[" + index + "].attenuationConstant");
		m_lightShader->BindUniform("lights[" + index + "].attenuationLinear");
		m_lightShader->BindUniform("lights[" + index + "].attenuationQuadratic");
	}*/

	//===================================================================

	Material::LoadMaterials("Materials.mat");

	//===================================================================

	if (!(Text::Initialize()))
	{
		return false;
	}

	if (!(Audio::Initialize()))
	{
		return false;
	}

	//===================================================================

	m_grid = std::make_unique<Grid>();
	m_grid->GetTransform().SetRotation(45.0f, -30.0f, 0.0f);

	m_axes = std::make_unique<Axes>();

	m_topText = std::make_unique<Text>();
	m_topText->LoadFont("Assets/Fonts/Quikhand.ttf", 30);
	m_topText->SetColor(1.0f, 0.0f, 0.196f, 1.0f);
	m_topText->SetText("Handmade Alpha");
	
	m_bottomText = std::make_unique<Text>();
	m_bottomText->LoadFont("Assets/Fonts/Quikhand.ttf", 30);
	m_bottomText->SetColor(0.0f, 0.564f, 1.0f, 1.0f);
	m_bottomText->SetText("Click/Drag the mouse to rotate the grid. Use the mouse wheel to zoom in/out");

	//For current testing=======================================================
	/*m_audio = std::make_unique<Audio>();
	m_audio->Load("Test.mp3", Audio::Type::Music, "Test");
	m_audio->SetAudio("Test", Audio::Type::Music);
	m_audio->Play();*/

	//m_light = std::make_unique<Light>();

	//m_model = std::make_unique<Model>();
	//m_model->Load("Teapot.obj");
	//m_model->SetColor(1, 0, 1, 1);

	//m_quad = std::make_unique<Quad>();
	//m_cube = std::make_unique<Cuboid>();
	//m_sphere = std::make_unique<Sphere>(10.0f, 50.0f, 50.0f);
	//=========================================================================

	m_mainCamera = std::make_unique<FreeCamera>();
	m_mainCamera->SetVelocity(0.0f);
	m_mainCamera->SetSensitivity(0.0f);
	m_mainCamera->GetTransform().SetPosition(0.0f, 0.0f, 50.0f);

	m_UICamera = std::make_unique<FreeCamera>();
	m_UICamera->SetVelocity(0.0f);
	m_UICamera->SetSensitivity(0.0f);

	return 0;
}
//======================================================================================================
void CHandmadeView::OnDestroy()
{
	m_objects.clear();
	Audio::Shutdown();
	Text::Shutdown();
}
//======================================================================================================
void CHandmadeView::OnMouseMove(UINT nFlags, CPoint point)
{
	glm::ivec2 newMousePosition = glm::ivec2(point.x, -point.y);
	m_mouseMotion = newMousePosition - m_mousePosition;
	m_mousePosition = newMousePosition;

	static glm::vec3 eulerAngles = m_grid->GetTransform().GetEulerAngles();

	if (m_isLeftButtonDown)
	{
		eulerAngles.x += -m_mouseMotion.y;
		eulerAngles.y += m_mouseMotion.x;
	}

	m_grid->GetTransform().SetRotation(eulerAngles);

	Invalidate(FALSE);
}
//======================================================================================================
BOOL CHandmadeView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	zDelta /= 120;
	m_mouseWheelMotion = -zDelta;

	auto camPos = m_mainCamera->GetTransform().GetPosition();
	camPos.z -= (zDelta * 2);
	m_mainCamera->GetTransform().SetPosition(camPos);

	Invalidate(FALSE);
	return TRUE;
}
//======================================================================================================
void CHandmadeView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_isLeftButtonDown = false;
	Invalidate(FALSE);
}
//======================================================================================================
void CHandmadeView::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_isRightButtonDown = false;
	Invalidate(FALSE);
}
//======================================================================================================
void CHandmadeView::OnMButtonUp(UINT nFlags, CPoint point)
{
	m_isMiddleButtonDown = false;
	Invalidate(FALSE);
}
//======================================================================================================
void CHandmadeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_isLeftButtonDown = true;
	Invalidate(FALSE);
}
//======================================================================================================
void CHandmadeView::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_isRightButtonDown = true;
	Invalidate(FALSE);
}
//======================================================================================================
void CHandmadeView::OnMButtonDown(UINT nFlags, CPoint point)
{
	m_isMiddleButtonDown = true;
	Invalidate(FALSE);
}
//======================================================================================================
void CHandmadeView::OnDraw(CDC* pDC)
{
	CHandmadeDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	Audio::Update();

	Screen::Instance()->Refresh();

	Shader& mainShader = *m_mainShader.get();
	Shader& textShader = *m_textShader.get();
	Shader& lightShader = *m_lightShader.get();
	Shader& testShader = *m_testShader.get();

	mainShader.Use();

	m_mainCamera->CreatePerspView();
	m_mainCamera->Update(16.0f);
	m_mainCamera->SendToShader(mainShader);

	//==============================================================================

	m_grid->Render(mainShader);

	m_axes->GetTransform().SetRotation(m_grid->GetTransform().GetRotation());
	m_axes->Render(mainShader);

	lightShader.Use();
	lightShader.SendData("cameraPosition", m_mainCamera->GetTransform().GetPosition());

	//m_light->SendToShader(lightShader);
	//m_light->Render(lightShader);
	//m_mainCamera->SendToShader(lightShader);
	
	//m_cube->GetTransform().SetRotation(m_grid->GetTransform().GetRotation());
	//m_cube->Render(lightShader);

	//m_model->GetTransform().SetRotation(m_grid->GetTransform().GetRotation());
	//m_model->Render(lightShader);

	//==============================================================================
	//Text rendering & UI
	//==============================================================================

	const auto PADDING = 25;
	auto resolution = Screen::Instance()->GetResolution();

	textShader.Use();
	
	m_UICamera->CreateOrthoView();
	m_UICamera->Update(16.0f);
	m_UICamera->SendToShader(textShader);

	m_topText->GetTransform().SetPosition(resolution.x - m_topText->GetTotalWidth() - PADDING, 
		resolution.y - 50.0f, 0.0f);
	m_topText->SendToShader(textShader);
	m_topText->Render(textShader);

	m_bottomText->GetTransform().SetPosition(PADDING, PADDING, 0.0f);
	m_bottomText->SendToShader(textShader);
	m_bottomText->Render(textShader);

	//For current testing
	//m_quad->GetTransform().SetRotation(m_grid->GetTransform().GetRotation());
	//m_quad->Render(*Shader::Instance());

	//m_sphere->GetTransform().SetRotation(m_grid->GetTransform().GetRotation());
	//m_sphere->Render(*Shader::Instance());

	//TEST CODE to be used later on
	/*m_UICamera->SetOrthoView();
	m_UICamera->Update();

	glm::vec2 pixels = m_mainCamera->ConvertWorldToScreen(m_axes->GetArrowTipPositionX());
	m_labelX->GetTransform().SetPosition(pixels.x, pixels.y, 0.0f);
	m_labelX->Render();

	pixels = m_mainCamera->ConvertWorldToScreen(m_axes->GetArrowTipPositionY());
	m_labelY->GetTransform().SetPosition(pixels.x, pixels.y, 0.0f);
	m_labelY->Render();

	pixels = m_mainCamera->ConvertWorldToScreen(m_axes->GetArrowTipPositionZ());
	m_labelZ->GetTransform().SetPosition(pixels.x, pixels.y, 0.0f);
	m_labelZ->Render();*/

	//TODO - calculate elapsed time
	static GLfloat deltaTime = 0.0f;

	for (const auto& object : m_objects)
	{
		if (object->IsActive())
		{
			object->Update(deltaTime);
		}

		if (object->IsVisible())
		{
			object->Render(lightShader);
		}
	}

	if (!pDC->IsPrinting())
	{
		Screen::Instance()->Present();
	}
}
//======================================================================================================
BOOL CHandmadeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}
//======================================================================================================
void CHandmadeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}
//======================================================================================================
void CHandmadeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}
//======================================================================================================
// CHandmadeView diagnostics
#ifdef _DEBUG
void CHandmadeView::AssertValid() const
{
	CView::AssertValid();
}
//======================================================================================================
void CHandmadeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
//======================================================================================================
CHandmadeDoc* CHandmadeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHandmadeDoc)));
	return (CHandmadeDoc*)m_pDocument;
}
#endif //_DEBUG