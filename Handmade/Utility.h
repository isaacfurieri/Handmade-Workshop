#pragma once

/*===================================================================#
| 'Utility' source files last updated on 22 June 2021                |
#===================================================================*/

#include <Windows.h>
#include <map>
#include <string>
#include <vector>
#include <glm.hpp>
#include "glad.h"

#define KEY 0
#define VALUE 1

#define FILE 2
#define VS_OUTPUT 4
#define MESSAGE_BOX 8

class Utility
{

public:

	enum Severity
	{
		FAILURE = MB_ICONERROR,
		WARNING = MB_ICONWARNING,
		DEFAULT = MB_ICONINFORMATION
	};

	enum class ErrorColor
	{
		FAILURE = 4,
		WARNING = 6,
		SUCCESS = 10,
		DEFAULT = 15
	};

	static void GLError();

	static void DisplayProfile();
	static void DisplayExtensions();

	static void SetWindowHandle(HWND windowHandle);

	static void RemoveCharacter(std::string& str, char character);

	static void ParseString(std::string& str,
		std::vector<std::string>& subStrings, char token);

	static bool LoadConfigFile(const std::string& filename,
		std::map<std::string, std::string>& dataMap);

	static bool LoadShaderFile(const std::string& filename, std::string& sourceCode);

	static void Log(int destination, GLfloat value, const std::string& label = "");
	static void Log(int destination, const glm::vec2& value , const std::string& label = "");
	static void Log(int destination, const glm::vec3& value, const std::string& label = "");
	static void Log(int destination, const std::string& message, Severity severity = DEFAULT);
	static void Log(int destination, GLfloat x, GLfloat y, GLfloat z = 0.0f, const std::string& label = "");

private:

	static HWND s_windowHandle;

	//static HANDLE s_consoleHandle;

};