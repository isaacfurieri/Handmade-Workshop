#include <fstream>
#include <string>
#include "Utility.h"

HWND Utility::s_windowHandle = nullptr;
//HANDLE Utility::s_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//======================================================================================================
void Utility::GLError()
{
	//query OpenGL for errors which will return the first 
	//error that occured since this function was last called
	GLenum errorCode = glGetError();

	//based on error code enum type returned output a more friendly error message
	switch (errorCode)
	{

	case GL_NO_ERROR:
	{
		//Log("There are no errors.", ErrorCode::SUCCESS);
		break;
	}

	case GL_INVALID_ENUM:
	{
		//Log("Invalid enumeration type passed.", ErrorCode::FAILURE);
		break;
	}

	case GL_INVALID_VALUE:
	{
		//Log("Numeric value outside of accepted range.", ErrorCode::FAILURE);
		break;
	}

	case GL_INVALID_OPERATION:
	{
		//Log("Invalid operation.", ErrorCode::FAILURE);
		break;
	}

	case GL_INVALID_FRAMEBUFFER_OPERATION:
	{
		//Log("Framebuffer object incomplete.", ErrorCode::FAILURE);
		break;
	}

	case GL_STACK_OVERFLOW:
	{
		//Log("Stack overflow.", ErrorCode::FAILURE);
		break;
	}

	case GL_STACK_UNDERFLOW:
	{
		//Log("Stack underflow.", ErrorCode::FAILURE);
		break;
	}

	case GL_OUT_OF_MEMORY:
	{
		//Log("Out of memory.", ErrorCode::FAILURE);
		break;
	}

	}
}
//======================================================================================================
void Utility::DisplayProfile()
{
	std::string profile;

	profile = (const char*)(glGetString(GL_VENDOR));
	Utility::Log(FILE, "Graphics card vendor: " + profile);

	profile = (const char*)(glGetString(GL_RENDERER));
	Utility::Log(FILE, "Graphics card model: " + profile);

	profile = (const char*)(glGetString(GL_VERSION));
	Utility::Log(FILE, "OpenGL version: " + profile);

	profile = (const char*)(glGetString(GL_SHADING_LANGUAGE_VERSION));
	Utility::Log(FILE, "GLSL version: " + profile);
}
//======================================================================================================
void Utility::DisplayExtensions()
{
	GLint totalExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtensions);

	/*Debug::Log("===============================================================");
	Debug::Log("The following extensions are supported by your graphics card:  ");
	Debug::Log("===============================================================");*/

	for (GLint i = 0; i < totalExtensions; i++)
	{
		std::string extension = (const char*)glGetStringi(GL_EXTENSIONS, i);
		//Debug::Log("Extension #" + std::to_string(i + 1) + ": " + extension);
	}

	//Debug::Log("===============================================================");
}
//======================================================================================================
void Utility::SetWindowHandle(HWND windowHandle)
{
	s_windowHandle = windowHandle;
}
//======================================================================================================
void Utility::RemoveCharacter(std::string& str, char character)
{
	auto it = std::find(str.begin(), str.end(), character);

	if (it != str.end())
	{
		do
		{
			str.erase(it);
			it = std::find(str.begin(), str.end(), character);
		} while (it != str.end());
	}
}
//======================================================================================================
void Utility::ParseString(std::string& str, std::vector<std::string>& subStrings, char token)
{
	size_t start = 0;
	size_t end = 0;

	assert(!str.empty());

	while (end != std::string::npos)
	{
		end = str.find(token, start);
		if ((end - start) > 0)
		{
			subStrings.push_back(str.substr(start, end - start));
		}
		start = end + 1;
	}
}
//======================================================================================================
bool Utility::LoadConfigFile(const std::string& filename,
	std::map<std::string, std::string>& dataMap)
{
	std::string lineText;
	std::vector<std::string> subStrings;
	std::fstream file(filename, std::ios_base::in);

	if (!file.is_open())
	{
		return false;
	}

	while (!file.eof())
	{
		std::getline(file, lineText);
		ParseString(lineText, subStrings, '=');
		dataMap.insert(std::pair<std::string, std::string>(subStrings[KEY],
			subStrings[VALUE]));
		subStrings.clear();
	}

	file.close();
	return true;
}
//======================================================================================================
bool Utility::LoadShaderFile(const std::string& filename, std::string& sourceCode)
{
	std::string lineText;
	std::fstream file(filename, std::ios_base::in);

	if (!file.is_open())
	{
		return false;
	}

	while (!file.eof())
	{
		getline(file, lineText);
		sourceCode += lineText + "\n";
	}

	file.close();
	return true;
}
//======================================================================================================
void Utility::Log(int destination, const glm::vec2& value, const std::string& label)
{
	Log(destination, value.x, value.y, 0.0f, label);
}
//======================================================================================================
void Utility::Log(int destination, const glm::vec3& value, const std::string& label)
{
	Log(destination, value.x, value.y, value.z, label);
}
//======================================================================================================
void Utility::Log(int destination, GLfloat value, const std::string& label)
{
	if (!label.empty())
	{
		if (destination == MESSAGE_BOX)
		{
			MessageBox(s_windowHandle,
				reinterpret_cast<LPCWSTR>(std::to_wstring(value).c_str()),
				reinterpret_cast<LPCWSTR>(std::wstring(label.begin(), label.end()).c_str()),
				MB_ICONINFORMATION | MB_OK);
		}

		else if (destination == VS_OUTPUT)
		{
			std::string message = "[" + label + "] " + std::to_string(value) + "\n";
			OutputDebugString(reinterpret_cast<LPCWSTR>
				(std::wstring(message.begin(), message.end()).c_str()));
		}

		else if (destination == FILE)
		{
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);
			std::string message = "[" + label + "] " + std::to_string(value) + "\n";
			file << message;
			file.close();
		}
	}
}
//======================================================================================================
void Utility::Log(int destination, const std::string& message, Severity severity)
{
	if (!message.empty())
	{
		if (destination == MESSAGE_BOX)
		{
			MessageBox(s_windowHandle,
				reinterpret_cast<LPCWSTR>(std::wstring(message.begin(), message.end()).c_str()),
				L"Log", severity | MB_OK);
		}

		else if (destination == VS_OUTPUT)
		{
			std::string finalMessage;

			if (severity == FAILURE)
			{
				finalMessage = "[FAILURE] " + message + "\n";
			}

			else if (severity == WARNING)
			{
				finalMessage = "[WARNING] " + message + "\n";
			}

			else
			{
				finalMessage = message + "\n";
			}

			OutputDebugString(reinterpret_cast<LPCWSTR>
				(std::wstring(finalMessage.begin(), finalMessage.end()).c_str()));
		}

		else if (destination == FILE)
		{
			std::string finalMessage;
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);

			if (severity == FAILURE)
			{
				finalMessage = "[FAILURE] " + message + "\n";
			}

			else if (severity == WARNING)
			{
				finalMessage = "[WARNING] " + message + "\n";
			}

			else
			{
				finalMessage = message + "\n";
			}

			file << finalMessage;
			file.close();
		}
	}
}
//======================================================================================================
void Utility::Log(int destination, GLfloat x, GLfloat y, GLfloat z, const std::string& label)
{
	if (!label.empty())
	{
		if (destination == MESSAGE_BOX)
		{
			std::string message = "x = " + std::to_string(x) +
				", y = " + std::to_string(y) +
				", z = " + std::to_string(z);

			MessageBox(s_windowHandle,
				reinterpret_cast<LPCWSTR>(std::wstring(message.begin(), message.end()).c_str()),
				reinterpret_cast<LPCWSTR>(std::wstring(label.begin(), label.end()).c_str()),
				MB_ICONINFORMATION | MB_OK);
		}

		else if (destination == VS_OUTPUT)
		{
			std::string message = "[" + label + "] " + "x = " + std::to_string(x) +
				", y = " + std::to_string(y) +
				", z = " + std::to_string(z) + "\n";
			OutputDebugString(reinterpret_cast<LPCWSTR>
				(std::wstring(message.begin(), message.end()).c_str()));
		}

		else if (destination == FILE)
		{
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);
			std::string message = "[" + label + "] " + "x = " + std::to_string(x) +
				", y = " + std::to_string(y) +
				", z = " + std::to_string(z) + "\n";
			file << message;
			file.close();
		}
	}
}

//===================================================================================================================
//OLD code for logging to the console window

//======================================================================================================
//void Debug::Log(GLfloat value, const std::string& label)
//{
//	//set color to a bright white
//	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(ErrorCode::DEFAULT));
//
//	//display numeric data and if there is a label
//	//to identify the data then display that first
//
//	if (!label.empty())
//	{
//		std::cout << "[" << label << "] ";
//	}
//
//	std::cout << value << std::endl;
//}
////======================================================================================================
//void Debug::Log(const glm::vec3& vector, const std::string& label)
//{
//	//set color to a bright white
//	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(ErrorCode::DEFAULT));
//
//	//display vector data in coordinate format and if there
//	//is a label to identify the data then display that first
//
//	if (!label.empty())
//	{
//		std::cout << "[" << label << "] ";
//	}
//
//	std::cout << "x = " << vector.x << ", y = " << vector.y << ", z = " << vector.z << std::endl;
//}
////======================================================================================================
//void Debug::Log(const std::string& message, ErrorCode errorCode)
//{
//	//set color based on the numeric error code passed
//	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(errorCode));
//
//	//display the message on the console
//	std::cout << message << std::endl;
//
//	//set color back to a bright white so that if the
//	//text is output elsewhere it will be regular white
//	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(ErrorCode::DEFAULT));
//}
////======================================================================================================
//void Debug::Log(GLfloat x, GLfloat y, GLfloat z, const std::string& label)
//{
//	//set color to a bright white
//	SetConsoleTextAttribute(s_consoleHandle, static_cast<WORD>(ErrorCode::DEFAULT));
//
//	//display vector data in coordinate format and if there
//	//is a label to identify the data then display that first
//
//	if (!label.empty())
//	{
//		std::cout << "[" << label << "] ";
//	}
//
//	std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
//}