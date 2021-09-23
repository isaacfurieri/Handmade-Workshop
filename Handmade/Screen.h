#pragma once

/*===================================================================#
| 'Screen' source files last updated on 21 July 2021                 |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include <Windows.h>
#include <glm.hpp>
#include <string>
#include "glad.h"
#include "wglext.h"

class Screen
{

public:

	static Screen* Instance();

	const glm::vec2& GetResolution() const;

	void SetResolution(GLuint width, GLuint height);
	void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height);

	void SetColor(const glm::vec4& color);
	void SetColor(const glm::uvec4& color);

	void SetColor(GLfloat r = 0.0f,
		GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 1.0f);
	void SetColor(GLuint r = 0U,
		GLuint g = 0U, GLuint b = 0U, GLuint a = 1U);

	void IsDepthTestEnabled(bool flag);

	bool Initialize(HWND wnd, const std::string& filename);

	void ActivateContext();
	void DeactivateContext();

	void Refresh();
	void Present();
	void Shutdown();

private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(const Screen&);

	GLint m_pixelFormat;

	glm::ivec4 m_viewport;
	glm::uvec2 m_resolution;

	HDC m_deviceContext;
	HGLRC m_renderContext;

	PIXELFORMATDESCRIPTOR m_pixelFormatClass;
	PFNWGLCREATECONTEXTATTRIBSARBPROC m_wglCreateContextAttribsARB;

};