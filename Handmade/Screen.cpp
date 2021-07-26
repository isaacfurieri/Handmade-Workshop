#include <gtc\matrix_transform.hpp>
#include "Screen.h"
#include "Shader.h"
#include "Utility.h"

//======================================================================================================
Screen* Screen::Instance()
{
	static Screen* screen = new Screen;
	return screen;
}
//======================================================================================================
Screen::Screen()
{
	m_pixelFormat = 0;
	m_pixelFormatClass = { 0 };

	m_viewport = glm::vec4(0);
	m_resolution = glm::uvec2(0);

	m_deviceContext = nullptr;
	m_renderContext = nullptr;
	m_wglCreateContextAttribsARB = nullptr;
}
//======================================================================================================
void Screen::IsDepthTestEnabled(bool flag)
{
	flag ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}
//======================================================================================================
void Screen::SetResolution(GLuint width, GLuint height)
{
	m_resolution.x = width;
	m_resolution.y = height;
	glm::max(m_resolution, 1U);
}
//======================================================================================================
void Screen::SetColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}
//======================================================================================================
void Screen::SetColor(const glm::uvec4& color)
{
	glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}
//======================================================================================================
void Screen::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glClearColor(r, g, b, a);
}
//======================================================================================================
void Screen::SetColor(GLuint r, GLuint g, GLuint b, GLuint a)
{
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
//======================================================================================================
void Screen::SetViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
	m_viewport = glm::vec4(x, y, width, height);
}
//======================================================================================================
const glm::vec2& Screen::GetResolution() const
{
	//The resolution cannot be zero. If this happens that means the Screen manager
	//has not yet been properly set up or the width and height values are faulty
	//Have you called 'SetResolution()' yet?
	assert(m_resolution != glm::uvec2(0));
	return m_resolution;
}
//======================================================================================================
bool Screen::Initialize(HWND wnd, const std::string& filename)
{
	std::map<std::string, std::string> dataMap;

	if (!Utility::LoadConfigFile(filename, dataMap))
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error opening config file '" + filename + "'", Utility::Severity::Failure);
		return false;
	}

	m_deviceContext = GetDC(wnd);

	//==================================================================================

	m_pixelFormatClass.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	m_pixelFormatClass.nVersion = 1;
	m_pixelFormatClass.dwFlags = PFD_SUPPORT_OPENGL |
		PFD_DRAW_TO_WINDOW |
		PFD_DOUBLEBUFFER;
	m_pixelFormatClass.iPixelType = PFD_TYPE_RGBA;
	m_pixelFormatClass.cDepthBits = 32;
	m_pixelFormatClass.cStencilBits = 32;

	m_pixelFormat = ChoosePixelFormat(m_deviceContext, &m_pixelFormatClass);
	SetPixelFormat(m_deviceContext, m_pixelFormat, &m_pixelFormatClass);

	//create a temporary OpenGL rendering context which is only used to acquire
	//the extension function to enable us to create a modern OpenGL context
	HGLRC temporaryContext = wglCreateContext(m_deviceContext);

	wglMakeCurrent(m_deviceContext, temporaryContext);

	m_wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)
		wglGetProcAddress("wglCreateContextAttribsARB");

	if (!m_wglCreateContextAttribsARB)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Your graphics card does not support modern OpenGL", Utility::Severity::Failure);
		return false;
	}

	wglDeleteContext(temporaryContext);

	//==================================================================================

	//SetPixelFormat(m_deviceContext, m_pixelFormat, &m_pixelFormatClass);

	int profile = std::stoi(dataMap["Core"]) == 1 ? WGL_CONTEXT_CORE_PROFILE_BIT_ARB
		: WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;

	//set the attributes for creating a modern OpenGL conGLText 
	//the final 0 value in the array indicates the end of the array
	int attribs[] = { WGL_CONTEXT_MAJOR_VERSION_ARB, std::stoi(dataMap["Major"]),
					   WGL_CONTEXT_MINOR_VERSION_ARB, std::stoi(dataMap["Minor"]),
					   WGL_CONTEXT_PROFILE_MASK_ARB, profile, 0 };

	//create the modern OpenGL context using the extension function
	m_renderContext = m_wglCreateContextAttribsARB(m_deviceContext, NULL, attribs);

	if (!m_renderContext)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"OpenGL context could not be created. "
			"The context is either invalid or not supported by your graphics card",
			Utility::Severity::Failure);
	}

	wglMakeCurrent(m_deviceContext, m_renderContext);

	//==================================================================================

	if (!gladLoadGL())
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"GLAD could not be initialized", Utility::Severity::Failure);
		return false;
	}

	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}
//======================================================================================================
void Screen::ActivateContext()
{
	wglMakeCurrent(m_deviceContext, m_renderContext);
}
//======================================================================================================
void Screen::DeactivateContext()
{
	wglMakeCurrent(nullptr, nullptr);
}
//======================================================================================================
void Screen::Refresh()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//======================================================================================================
void Screen::Present()
{
	SwapBuffers(m_deviceContext);
}
//======================================================================================================
void Screen::Shutdown()
{
	wglMakeCurrent(m_deviceContext, nullptr);
	wglDeleteContext(m_renderContext);
}