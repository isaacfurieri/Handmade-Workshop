#pragma once

/*===================================================================#
| 'Screen' source files last updated on 23 November 2021             |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include "GLAD/gl.h"
#include <glm.hpp>
#include <string>
#include <SDL.h>

#define NOMINMAX

//This code usually resides in the stdafx.h file and  
//sets the manifest so that the modern Windows controls  
//are used. If this is missing dialog boxes will look old 
#ifdef _UNICODE 
#if defined _M_IX86 
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"") 
#elif defined _M_X64 
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"") 
#else 
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 
#endif 
#endif

class Screen
{

public:

	enum class VSync
	{
		On,
		Off
	};

	static Screen* Instance();

	bool Initialize(const std::string& filename);

	const glm::ivec2& GetResolution();

	void SetVSync(VSync VSync);
	void IsDepthTestEnabled(bool flag);
	void SetCursorPosition(GLuint x, GLuint y);
	void SetResolution(GLint width, GLint height);

	void SetColor(const glm::vec4& color);
	void SetColor(const glm::uvec4& color);
	void SetColor(GLfloat r = 0.0f,
		GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 1.0f);
	void SetColor(GLuint r = 0U,
		GLuint g = 0U, GLuint b = 0U, GLuint a = 1U);

	void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height);

	void Refresh();
	void Present();
	void Shutdown();

private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(Screen&);

	glm::ivec4 m_viewport;
	glm::ivec2 m_resolution;

	SDL_Window* m_window;
	SDL_GLContext m_context;

};