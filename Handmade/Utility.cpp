#include <fstream>
#include <string>
#include "Utility.h"

HWND Utility::s_windowHandle = nullptr;
//======================================================================================================
void Utility::CheckGLError()
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
	const GLubyte* profile = nullptr;

	profile = reinterpret_cast<const GLubyte*>(glGetString(GL_VENDOR));
	Utility::Log(Destination::LogFile, "Graphics card vendor: " + (*profile));

	profile = reinterpret_cast<const GLubyte*>(glGetString(GL_RENDERER));
	Utility::Log(Destination::LogFile, "Graphics card model: " + (*profile));

	profile = reinterpret_cast<const GLubyte*>(glGetString(GL_VERSION));
	Utility::Log(Destination::LogFile, "OpenGL version: " + (*profile));

	profile = reinterpret_cast<const GLubyte*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	Utility::Log(Destination::LogFile, "GLSL version: " + (*profile));
}
//======================================================================================================
void Utility::DisplayExtensions()
{
	GLint totalExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtensions);

	for (GLint i = 0; i < totalExtensions; i++)
	{
		const GLubyte* extension = reinterpret_cast<const GLubyte*>(glGetStringi(GL_EXTENSIONS, i));
		//Utility::Log(Destination::LogFile, std::to_string(i + 1) + (*extension));
	}
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
	std::fstream file(filename, std::ios_base::in);

	if (!file.is_open())
	{
		return false;
	}

	std::string line;

	while (!file.eof())
	{
		std::getline(file, line);
		std::vector<std::string> subStrings;
		ParseString(line, subStrings, '=');

		if (!subStrings.empty())
		{
			dataMap[subStrings[0]] = subStrings[1];
		}
	}

	file.close();
	return true;
}
//======================================================================================================
bool Utility::LoadShaderFile(const std::string& filename, std::string& sourceCode)
{
	std::fstream file(filename, std::ios_base::in);

	if (!file.is_open())
	{
		return false;
	}

	std::string line;

	while (!file.eof())
	{
		getline(file, line);
		sourceCode += line + "\n";
	}

	file.close();
	return true;
}
//======================================================================================================
void Utility::Log(Destination destination, const glm::vec2& value, const std::string& label)
{
	Log(destination, value.x, value.y, 0.0f, label);
}
//======================================================================================================
void Utility::Log(Destination destination, const glm::vec3& value, const std::string& label)
{
	Log(destination, value.x, value.y, value.z, label);
}
//======================================================================================================
void Utility::Log(Destination destination, GLfloat value, const std::string& label)
{
	if (!label.empty())
	{
		if (destination == Destination::WindowsMessageBox)
		{
			MessageBox(s_windowHandle,
				reinterpret_cast<LPCWSTR>(std::to_wstring(value).c_str()),
				reinterpret_cast<LPCWSTR>(std::wstring(label.begin(), label.end()).c_str()),
				MB_ICONINFORMATION | MB_OK);
		}

		else if (destination == Destination::OutputWindow)
		{
			std::string message = "[" + label + "] " + std::to_string(value) + "\n";
			OutputDebugString(reinterpret_cast<LPCWSTR>
				(std::wstring(message.begin(), message.end()).c_str()));
		}

		else if (destination == Destination::LogFile)
		{
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);
			std::string message = "[" + label + "] " + std::to_string(value) + "\n";
			file << message;
			file.close();
		}
	}
}
//======================================================================================================
void Utility::Log(Destination destination, const std::string& message, Severity severity)
{
	if (!message.empty())
	{
		if (destination == Destination::WindowsMessageBox)
		{
			MessageBox(s_windowHandle,
				reinterpret_cast<LPCWSTR>(std::wstring(message.begin(), message.end()).c_str()),
				L"Log", static_cast<GLuint>(severity) | MB_OK);
		}

		else if (destination == Destination::OutputWindow)
		{
			std::string finalMessage;

			if (severity == Severity::Failure)
			{
				finalMessage = "[FAILURE] " + message + "\n";
			}

			else if (severity == Severity::Warning)
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

		else if (destination == Destination::LogFile)
		{
			std::string finalMessage;
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);

			if (severity == Severity::Failure)
			{
				finalMessage = "[FAILURE] " + message + "\n";
			}

			else if (severity == Severity::Warning)
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
void Utility::Log(Destination destination, GLfloat x, GLfloat y, GLfloat z, const std::string& label)
{
	if (!label.empty())
	{
		if (destination == Destination::WindowsMessageBox)
		{
			std::string message = "x = " + std::to_string(x) +
				", y = " + std::to_string(y) +
				", z = " + std::to_string(z);

			MessageBox(s_windowHandle,
				reinterpret_cast<LPCWSTR>(std::wstring(message.begin(), message.end()).c_str()),
				reinterpret_cast<LPCWSTR>(std::wstring(label.begin(), label.end()).c_str()),
				MB_ICONINFORMATION | MB_OK);
		}

		else if (destination == Destination::OutputWindow)
		{
			std::string message = "[" + label + "] " + "x = " + std::to_string(x) +
				", y = " + std::to_string(y) +
				", z = " + std::to_string(z) + "\n";
			OutputDebugString(reinterpret_cast<LPCWSTR>
				(std::wstring(message.begin(), message.end()).c_str()));
		}

		else if (destination == Destination::LogFile)
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