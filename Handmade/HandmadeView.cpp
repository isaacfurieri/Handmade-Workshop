#include "framework.h"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Handmade.h"
#endif

#include "AudioManager.h"
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

	m_isScreenInitialized = true;

	if (!Shader::Instance()->CreateProgram())
	{
		return -1;
	}

	if (!Shader::Instance()->CreateShaders())
	{
		return -1;
	}

	if (!Shader::Instance()->CompileShader("Shaders/Main.vert",
		Shader::ShaderType::VERTEX_SHADER))
	{
		return -1;
	}

	if (!Shader::Instance()->CompileShader("Shaders/Main.frag",
		Shader::ShaderType::FRAGMENT_SHADER))
	{
		return -1;
	}

	Shader::Instance()->AttachShaders();

	if (!Shader::Instance()->LinkProgram())
	{
		return -1;
	}

	Shader::Instance()->BindAttribute("vertexIn");
	Shader::Instance()->BindAttribute("colorIn");
	Shader::Instance()->BindAttribute("textureIn");
	//Shader::Instance()->BindAttribute("normalIn");

	Shader::Instance()->BindUniform("model");
	Shader::Instance()->BindUniform("view");
	Shader::Instance()->BindUniform("projection");
	//Shader::Instance()->BindUniform("normal");

	//Shader::Instance()->BindUniform("isText");
	Shader::Instance()->BindUniform("isTextured");
	Shader::Instance()->BindUniform("textureImage");
	
	/*Shader::Instance()->BindUniform("light.ambient");
	Shader::Instance()->BindUniform("light.diffuse");
	Shader::Instance()->BindUniform("light.specular");
	Shader::Instance()->BindUniform("light.position");
					
	Shader::Instance()->BindUniform("material.ambient");
	Shader::Instance()->BindUniform("material.diffuse");
	Shader::Instance()->BindUniform("material.specular");
	Shader::Instance()->BindUniform("material.shininess");*/

	//Shader::Instance()->BindUniform("light.attenuationLinear");
	//Shader::Instance()->BindUniform("light.attenuationConstant");
	//Shader::Instance()->BindUniform("light.attenuationQuadratic");

	//Shader::Instance()->BindUniform("cameraPosition");

	//Material::LoadMaterials("Materials.mat");

	//initialize FMOD audio sub-system and return false if error occured
	if (!(AudioManager::Instance()->Initialize()))
	{
		return false;
	}

	m_grid = std::make_unique<Grid>();
	m_grid->GetTransform().SetRotation(45.0f, -30.0f, 0.0f);

	m_axes = std::make_unique<Axes>();
	

	//For current testing
	//m_light = std::make_unique<Light>();

	//m_model = std::make_unique<Model>();
	//m_model->Load("Teapot.obj");
	//m_model->SetColor(1, 0, 1, 1);

	//m_quad = std::make_unique<Quad>();
	//m_cube = std::make_unique<Cuboid>();
	//m_sphere = std::make_unique<Sphere>(10.0f, 50.0f, 50.0f);

	m_mainCamera = std::make_unique<FreeCamera>();
	m_mainCamera->SetVelocity(0.0f);
	m_mainCamera->SetSensitivity(0.0f);
	m_mainCamera->GetTransform().SetPosition(0.0f, 0.0f, 50.0f);

	return 0;
}
//======================================================================================================
void CHandmadeView::OnDestroy()
{
	m_objects.clear();
	AudioManager::Instance()->ShutDown();
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

	AudioManager::Instance()->Update();

	Screen::Instance()->Refresh();
	
	m_mainCamera->CreatePerspView();
	m_mainCamera->Update(16.0f);
	m_mainCamera->SendToShader(*Shader::Instance());

	//==============================================================================

	m_grid->Render(*Shader::Instance());
	
	m_axes->GetTransform().SetRotation(m_grid->GetTransform().GetRotation());
	m_axes->Render(*Shader::Instance());
	
	//For current testing
	//m_light->SendToShader(*Shader::Instance());

	//m_model->Render(*Shader::Instance());

	//m_quad->GetTransform().SetRotation(m_grid->GetTransform().GetRotation());
	//m_quad->Render(*Shader::Instance());

	//m_cube->GetTransform().SetRotation(m_grid->GetTransform().GetRotation());
	//m_cube->Render(*Shader::Instance());
	
	//m_sphere->GetTransform().SetRotation(m_grid->GetTransform().GetRotation());
	//m_sphere->Render(*Shader::Instance());
	
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
			object->Render(*Shader::Instance());
		}
	}

	Utility::Log(VS_OUTPUT, m_mouseWheelMotion, "MouseWheel");

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