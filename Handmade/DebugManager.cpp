#include <iostream>
#include <string>
#include <glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include "BufferManager.h"
#include "DebugManager.h"
#include "GameObject.h"
#include "ScreenManager.h"
#include "ShaderManager.h"
#include "Sprite.h"
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//function that checks for errors and displays them on screen
//------------------------------------------------------------------------------------------------------
void DebugManager::CheckError()
{

	//query OpenGL for occured errors
	GLenum errorCode = glGetError();

	//based on error code enum type returned, 
	//output a friendly error message
	switch (errorCode)
	{

		case GL_NO_ERROR:
		{
			std::cout << "SUCCESS : There are no errors!" << std::endl;
			break;
		}

		case GL_INVALID_ENUM:
		{
			std::cout << "ERROR : Invalid enumeration type passed." << std::endl;
			break;
		}

		case GL_INVALID_VALUE:
		{
			std::cout << "ERROR : Numeric value outside of accepted range." << std::endl;
			break;
		}

		case GL_INVALID_OPERATION:
		{
			std::cout << "ERROR : Invalid operation." << std::endl;
			break;
		}

		case GL_INVALID_FRAMEBUFFER_OPERATION:
		{
			std::cout << "ERROR : Framebuffer object incomplete." << std::endl;
			break;
		}

		case GL_STACK_OVERFLOW:
		{
			std::cout << "ERROR : Stack overflow." << std::endl;
			break;
		}

		case GL_STACK_UNDERFLOW:
		{
			std::cout << "ERROR : Stack underflow." << std::endl;
			break;
		}

		case GL_OUT_OF_MEMORY:
		{
			std::cout << "ERROR : Out of memory." << std::endl;
			break;
		}

		case GL_TABLE_TOO_LARGE:
		{
			std::cout << "ERROR : Table too large." << std::endl;
			break;
		}

	}

}
//------------------------------------------------------------------------------------------------------
//function that sets up the debug VBOs and links all shader attributes
//------------------------------------------------------------------------------------------------------
bool DebugManager::CreateBuffers()
{

	//create vertex buffer objects for all debug objects' model's vertices to be stored
	TheBuffer::Instance()->Create(BufferManager::VERTEX_BUFFER, "CUBE_VERTEX_BUFFER_3D");
	TheBuffer::Instance()->Create(BufferManager::VERTEX_BUFFER, "SPHERE_VERTEX_BUFFER_3D");

	//create vertex buffer objects for all debug objects' buffer's vertices to be stored
	TheBuffer::Instance()->Create(BufferManager::VERTEX_BUFFER, "LINE_VERTEX_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::VERTEX_BUFFER, "GRID_VERTEX_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::VERTEX_BUFFER, "COORD_VERTEX_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::VERTEX_BUFFER, "VERTEX_VERTEX_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::VERTEX_BUFFER, "VECTOR_VERTEX_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::VERTEX_BUFFER, "CUBE_VERTEX_BUFFER_2D");
	TheBuffer::Instance()->Create(BufferManager::VERTEX_BUFFER, "SPHERE_VERTEX_BUFFER_2D");
	
	//create vertex buffer objects for all debug objects' model's colors to be stored
	TheBuffer::Instance()->Create(BufferManager::COLOR_BUFFER, "CUBE_COLOR_BUFFER_3D");
	TheBuffer::Instance()->Create(BufferManager::COLOR_BUFFER, "SPHERE_COLOR_BUFFER_3D");

	//create vertex buffer objects for all debug objects' buffer's colors to be stored
	TheBuffer::Instance()->Create(BufferManager::COLOR_BUFFER, "LINE_COLOR_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::COLOR_BUFFER, "GRID_COLOR_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::COLOR_BUFFER, "COORD_COLOR_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::COLOR_BUFFER, "VERTEX_COLOR_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::COLOR_BUFFER, "VECTOR_COLOR_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::COLOR_BUFFER, "CUBE_COLOR_BUFFER_2D");
	TheBuffer::Instance()->Create(BufferManager::COLOR_BUFFER, "SPHERE_COLOR_BUFFER_2D");

	//link VBO and shader attributes to sphere model object and load sphere model data 
	//no texture or normal data is associated with the models, therefore those fields are blank
	//remember the VBOs are linked BEFORE the model data is loaded and filled into those VBOs
	m_sphere3D.SetBufferID("SPHERE_VERTEX_BUFFER_3D", "SPHERE_COLOR_BUFFER_3D", "", "");
	m_sphere3D.SetShaderAttribute("vertexIn", "colorIn", "", "");
	m_sphere3D.LoadFromFile("Assets\\Models\\Sphere.obj", "Assets\\Models\\Sphere.mtl");

	//link VBO and shader attributes to cube model object and load cube model data 
	//no texture or normal data is associated with the models, therefore those fields are blank
	//remember the VBOs are linked BEFORE the model data is loaded and filled into those VBOs
	m_cube3D.SetBufferID("CUBE_VERTEX_BUFFER_3D", "CUBE_COLOR_BUFFER_3D", "", "");
	m_cube3D.SetShaderAttribute("vertexIn", "colorIn", "", "");
	m_cube3D.LoadFromFile("Assets\\Models\\Cube.obj", "Assets\\Models\\Cube.mtl");

	//link line object with its vertex and color buffer 
	//as well as its vertex and color shader attribute
	m_lineBuffer.SetAttributeID(Buffer::VERTEX_BUFFER, "vertexIn");
	m_lineBuffer.SetAttributeID(Buffer::COLOR_BUFFER, "colorIn");
	m_lineBuffer.SetBufferID(Buffer::VERTEX_BUFFER, "LINE_VERTEX_BUFFER");
	m_lineBuffer.SetBufferID(Buffer::COLOR_BUFFER, "LINE_COLOR_BUFFER");

	//link grid object with its vertex and color buffer 
	//as well as its vertex and color shader attribute
	m_gridBuffer.SetAttributeID(Buffer::VERTEX_BUFFER, "vertexIn");
	m_gridBuffer.SetAttributeID(Buffer::COLOR_BUFFER, "colorIn");
	m_gridBuffer.SetBufferID(Buffer::VERTEX_BUFFER, "GRID_VERTEX_BUFFER");
	m_gridBuffer.SetBufferID(Buffer::COLOR_BUFFER, "GRID_COLOR_BUFFER");
		
	//link coordinate system object with its vertex and color buffer 
	//as well as its vertex and color shader attribute
	m_coordBuffer.SetAttributeID(Buffer::VERTEX_BUFFER, "vertexIn");
	m_coordBuffer.SetAttributeID(Buffer::COLOR_BUFFER, "colorIn");
	m_coordBuffer.SetBufferID(Buffer::VERTEX_BUFFER, "COORD_VERTEX_BUFFER");
	m_coordBuffer.SetBufferID(Buffer::COLOR_BUFFER, "COORD_COLOR_BUFFER");

	//link vertex object with its vertex and color buffer
	//as well as its vertex and color shader attribute
	m_vertexBuffer.SetAttributeID(Buffer::VERTEX_BUFFER, "vertexIn");
	m_vertexBuffer.SetAttributeID(Buffer::COLOR_BUFFER, "colorIn");
	m_vertexBuffer.SetBufferID(Buffer::VERTEX_BUFFER, "VERTEX_VERTEX_BUFFER");
	m_vertexBuffer.SetBufferID(Buffer::COLOR_BUFFER, "VERTEX_COLOR_BUFFER");

	//link vector object with its vertex and color buffer 
	//as well as its vertex and color shader attribute
	m_vectorBuffer.SetAttributeID(Buffer::VERTEX_BUFFER, "vertexIn");
	m_vectorBuffer.SetAttributeID(Buffer::COLOR_BUFFER, "colorIn");
	m_vectorBuffer.SetBufferID(Buffer::VERTEX_BUFFER, "VECTOR_VERTEX_BUFFER");
	m_vectorBuffer.SetBufferID(Buffer::COLOR_BUFFER, "VECTOR_COLOR_BUFFER");

	//link cube object with its vertex and color buffer 
	//as well as its vertex and color shader attribute
	m_cubeBuffer2D.SetAttributeID(Buffer::VERTEX_BUFFER, "vertexIn");
	m_cubeBuffer2D.SetAttributeID(Buffer::COLOR_BUFFER, "colorIn");
	m_cubeBuffer2D.SetBufferID(Buffer::VERTEX_BUFFER, "CUBE_VERTEX_BUFFER_2D");
	m_cubeBuffer2D.SetBufferID(Buffer::COLOR_BUFFER, "CUBE_COLOR_BUFFER_2D");

	//link sphere object with its vertex and color buffer 
	//as well as its vertex and color shader attribute
	m_sphereBuffer2D.SetAttributeID(Buffer::VERTEX_BUFFER, "vertexIn");
	m_sphereBuffer2D.SetAttributeID(Buffer::COLOR_BUFFER, "colorIn");
	m_sphereBuffer2D.SetBufferID(Buffer::VERTEX_BUFFER, "SPHERE_VERTEX_BUFFER_2D");
	m_sphereBuffer2D.SetBufferID(Buffer::COLOR_BUFFER, "SPHERE_COLOR_BUFFER_2D");

	//get texture flag ID from fragment shader
	m_textureFlagUniformID = TheShader::Instance()->GetUniformID("isTextured");

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that destroys all debug VBOs
//------------------------------------------------------------------------------------------------------
void DebugManager::DestroyBuffers()
{
	
	//destroy vertex buffer objects for all debug objects' vertices
	TheBuffer::Instance()->
    Destroy(BufferManager::VERTEX_BUFFER, BufferManager::CUSTOM_BUFFER, "CUBE_VERTEX_BUFFER_2D");
	TheBuffer::Instance()->
	Destroy(BufferManager::VERTEX_BUFFER, BufferManager::CUSTOM_BUFFER, "SPHERE_VERTEX_BUFFER_2D");
	TheBuffer::Instance()->
	Destroy(BufferManager::VERTEX_BUFFER, BufferManager::CUSTOM_BUFFER, "CUBE_VERTEX_BUFFER_3D");
	TheBuffer::Instance()->
	Destroy(BufferManager::VERTEX_BUFFER, BufferManager::CUSTOM_BUFFER, "SPHERE_VERTEX_BUFFER_3D");
	TheBuffer::Instance()->
	Destroy(BufferManager::VERTEX_BUFFER, BufferManager::CUSTOM_BUFFER, "GRID_VERTEX_BUFFER");
	TheBuffer::Instance()->
	Destroy(BufferManager::VERTEX_BUFFER, BufferManager::CUSTOM_BUFFER, "COORD_VERTEX_BUFFER");
	TheBuffer::Instance()->
	Destroy(BufferManager::VERTEX_BUFFER, BufferManager::CUSTOM_BUFFER, "VECTOR_VERTEX_BUFFER");

	//destroy vertex buffer objects for all debug objects' colors
	TheBuffer::Instance()->
	Destroy(BufferManager::COLOR_BUFFER, BufferManager::CUSTOM_BUFFER, "CUBE_COLOR_BUFFER_2D");
	TheBuffer::Instance()->
	Destroy(BufferManager::COLOR_BUFFER, BufferManager::CUSTOM_BUFFER, "SPHERE_COLOR_BUFFER_2D");
	TheBuffer::Instance()->
	Destroy(BufferManager::COLOR_BUFFER, BufferManager::CUSTOM_BUFFER, "CUBE_COLOR_BUFFER_3D");
	TheBuffer::Instance()->
	Destroy(BufferManager::COLOR_BUFFER, BufferManager::CUSTOM_BUFFER, "SPHERE_COLOR_BUFFER_3D");
	TheBuffer::Instance()->
	Destroy(BufferManager::COLOR_BUFFER, BufferManager::CUSTOM_BUFFER, "GRID_COLOR_BUFFER");
	TheBuffer::Instance()->
	Destroy(BufferManager::COLOR_BUFFER, BufferManager::CUSTOM_BUFFER, "COORD_COLOR_BUFFER");
	TheBuffer::Instance()->
	Destroy(BufferManager::COLOR_BUFFER, BufferManager::CUSTOM_BUFFER, "VECTOR_COLOR_BUFFER");

	//destroy vertex and fragment debug shaders
	TheShader::Instance()->
    Destroy(ShaderManager::VERTEX_SHADER, ShaderManager::CUSTOM_SHADER, "DEBUG_VERTEX_SHADER");
	TheShader::Instance()->
	Destroy(ShaderManager::FRAGMENT_SHADER, ShaderManager::CUSTOM_SHADER, "DEBUG_FRAGMENT_SHADER");

}
//------------------------------------------------------------------------------------------------------
//function that draws a square 3D grid to help orient objects in world space
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawGrid3D(int size, float lineWidth)
{

	//variable to flag if grid buffer data has been filled
	static bool isFilled = false;

	//set line width of grid lines based on value passed
	glLineWidth(lineWidth);
	
	//set vertex data component size to X, Y and Z (3)
	//because we will be sending data for a 3D grid
	m_gridBuffer.SetComponentSize(Buffer::VERTEX_BUFFER, Buffer::XYZ);

	//if vertex and color data has not yet been added for grid object
	//fill buffers with data. This will allow for the grid to be filled 
	//only once instead of each time this function is called 
	if (!isFilled)
	{

		//draw the gridlines 1 unit in size so that 
		//both the X and Z portions are covered
		//the amount of grid lines drawn is based on size passed

		//draw all negative X lines
		for (int i = 0; i < size; i++)
		{

			//first vertex
			m_gridBuffer.Vertices().push_back((GLfloat)(-size + i)); 
			m_gridBuffer.Vertices().push_back(0.0f); 
			m_gridBuffer.Vertices().push_back((GLfloat)size);
			
			//second vertex
			m_gridBuffer.Vertices().push_back((GLfloat)(-size + i));
			m_gridBuffer.Vertices().push_back(0.0f); 
			m_gridBuffer.Vertices().push_back((GLfloat)-size);

			//color for both vertices
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f); 
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f); 
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);

		}

		//draw all positive X lines
		//add an extra line to close the grid
		for (int i = 1; i < size + 1; i++)
		{
			
			//first vertex
			m_gridBuffer.Vertices().push_back((GLfloat)(0 + i));
			m_gridBuffer.Vertices().push_back(0.0f); 
			m_gridBuffer.Vertices().push_back((GLfloat)size);
			
			//second vertex
			m_gridBuffer.Vertices().push_back((GLfloat)(0 + i));
			m_gridBuffer.Vertices().push_back(0.0); 
			m_gridBuffer.Vertices().push_back((GLfloat)(-size));

			//color for both vertices
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f); 
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f); 
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);

		}

		//draw all negative Z lines 
		for (int i = 0; i < size; i++)
		{
			
			//first vertex
			m_gridBuffer.Vertices().push_back((GLfloat)-size);
			m_gridBuffer.Vertices().push_back(0.0f); 
			m_gridBuffer.Vertices().push_back((GLfloat)(-size + i));
			
			//second vertex
			m_gridBuffer.Vertices().push_back((GLfloat)size);
			m_gridBuffer.Vertices().push_back(0.0f); 
			m_gridBuffer.Vertices().push_back((GLfloat)(-size + i));

			//color for both vertices
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f); 
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f); 
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);

		}

		//draw all positive Z lines
		//add an extra line to close the grid
		for (int i = 1; i < size + 1; i++)
		{
			
			//first vertex
			m_gridBuffer.Vertices().push_back((GLfloat)-size);
			m_gridBuffer.Vertices().push_back(0.0f); 
			m_gridBuffer.Vertices().push_back((GLfloat)(0 + i));
			
			//second vertex
			m_gridBuffer.Vertices().push_back((GLfloat)size);
			m_gridBuffer.Vertices().push_back(0.0f); 
			m_gridBuffer.Vertices().push_back((GLfloat)(0 + i));

			//color for both vertices
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f); 
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f); 
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);

		}

		//fill VBO with grid vertex and color data
		m_gridBuffer.FillData(Buffer::VERTEX_BUFFER);
		m_gridBuffer.FillData(Buffer::COLOR_BUFFER);

		//set flag to true so that buffer filling doesn't occur again
		isFilled = true;

	}

	//send texture flag to fragment shader
	TheShader::Instance()->SetUniformData(m_textureFlagUniformID, false);

	//draw grid object using shader
	m_gridBuffer.DrawData(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a square 2D grid to help orient objects in world space
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawGrid2D(int size, float lineWidth, int pixelsPerUnit)
{

	//variable to flag if grid buffer data has been filled
	static bool isFilled = false;

	//set line width of grid lines based on value passed
	glLineWidth(lineWidth);

	//set vertex data component size to X and Y (2)
	//because we will be sending data for a 2D grid
	m_gridBuffer.SetComponentSize(Buffer::VERTEX_BUFFER, Buffer::XY);

	//if vertex and color data has not yet been added for grid object
	//fill buffers with data. This will allow for the grid to be filled 
	//only once instead of each time this function is called 
	if (!isFilled)
	{

		//draw the gridlines based on size and spacing passed so that 
		//both the X and Y portions are covered
		//the amount of grid lines drawn is based on size passed and the spacing 
		//in between allows for the lines to be more apart, because in 2D mode we are working in pixels

		//draw all negative X lines
		for (int i = 0; i < size; i++)
		{

			//first vertex
			m_gridBuffer.Vertices().push_back((GLfloat)((-size * pixelsPerUnit) + (i * pixelsPerUnit)));
			m_gridBuffer.Vertices().push_back((GLfloat)(-size * pixelsPerUnit));

			//second vertex
			m_gridBuffer.Vertices().push_back((GLfloat)((-size * pixelsPerUnit) + (i * pixelsPerUnit)));
			m_gridBuffer.Vertices().push_back((GLfloat)(size * pixelsPerUnit));

			//color for both vertices
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);

		}

		//draw all positive X lines
		//add an extra line to close the grid
		for (int i = 0; i < size + 1; i++)
		{

			//first vertex
			m_gridBuffer.Vertices().push_back((GLfloat)(0 + (i * pixelsPerUnit)));
			m_gridBuffer.Vertices().push_back((GLfloat)(-size * pixelsPerUnit));

			//second vertex
			m_gridBuffer.Vertices().push_back((GLfloat)(0 + (i * pixelsPerUnit)));
			m_gridBuffer.Vertices().push_back((GLfloat)(size * pixelsPerUnit));

			//color for both vertices
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);

		}

		//draw all negative Y lines
		for (int i = 0; i < size; i++)
		{

			//first vertex
			m_gridBuffer.Vertices().push_back((GLfloat)(-size * pixelsPerUnit));
			m_gridBuffer.Vertices().push_back((GLfloat)((-size * pixelsPerUnit) + (i * pixelsPerUnit)));

			//second vertex
			m_gridBuffer.Vertices().push_back((GLfloat)(size * pixelsPerUnit));
			m_gridBuffer.Vertices().push_back((GLfloat)((-size * pixelsPerUnit) + (i * pixelsPerUnit)));

			//color for both vertices
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);

		}

		//draw all positive Y lines
		//add an extra line to close the grid
		for (int i = 0; i < size + 1; i++)
		{

			//first vertex
			m_gridBuffer.Vertices().push_back((GLfloat)(-size * pixelsPerUnit));
			m_gridBuffer.Vertices().push_back((GLfloat)(0 + (i * pixelsPerUnit)));

			//second vertex
			m_gridBuffer.Vertices().push_back((GLfloat)(size * pixelsPerUnit));
			m_gridBuffer.Vertices().push_back((GLfloat)(0 + (i * pixelsPerUnit)));

			//color for both vertices
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);
			m_gridBuffer.Colors().push_back(1.0f); m_gridBuffer.Colors().push_back(1.0f);

		}

		//fill VBO with grid vertex and color data
		m_gridBuffer.FillData(Buffer::VERTEX_BUFFER);
		m_gridBuffer.FillData(Buffer::COLOR_BUFFER);

		//set flag to true so that buffer filling doesn't occur again
		isFilled = true;

	}

	//send texture flag to fragment shader
	TheShader::Instance()->SetUniformData(m_textureFlagUniformID, false);

	//draw grid object using shader
	m_gridBuffer.DrawData(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a X, Y and Z coordinate system to help orient objects in world space
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawCoordSystem3D(float size, float lineWidth)
{

	//clear the vertex and color data each time function is called 
	//because different sized coordinate systems may be requested
	m_coordBuffer.Vertices().clear();
	m_coordBuffer.Colors().clear();

	//set line width of grid lines based on value passed
	glLineWidth(lineWidth);

	//set vertex data component size to X, Y and Z (3)
	//because we will be sending data for a 3D grid
	m_coordBuffer.SetComponentSize(Buffer::VERTEX_BUFFER, Buffer::XYZ);

	//draw the X axis line

	//first vertex
	m_coordBuffer.Vertices().push_back(-size);
	m_coordBuffer.Vertices().push_back(0); 
	m_coordBuffer.Vertices().push_back(0); 
	
	//second vertex
	m_coordBuffer.Vertices().push_back(size);
	m_coordBuffer.Vertices().push_back(0); 
	m_coordBuffer.Vertices().push_back(0);

	//color for both vertices
	m_coordBuffer.Colors().push_back(1.0f); m_coordBuffer.Colors().push_back(0.0f); 
	m_coordBuffer.Colors().push_back(0.0f); m_coordBuffer.Colors().push_back(1.0f); 
	m_coordBuffer.Colors().push_back(0.0f); m_coordBuffer.Colors().push_back(0.0f);

	//draw the Y axis line

	//first vertex
	m_coordBuffer.Vertices().push_back(0); 
	m_coordBuffer.Vertices().push_back(-size);
	m_coordBuffer.Vertices().push_back(0); 
	
	//second vertex
	m_coordBuffer.Vertices().push_back(0); 
	m_coordBuffer.Vertices().push_back(size);
	m_coordBuffer.Vertices().push_back(0);

	//color for both vertices
	m_coordBuffer.Colors().push_back(0.0f); m_coordBuffer.Colors().push_back(1.0f); 
	m_coordBuffer.Colors().push_back(0.0f); m_coordBuffer.Colors().push_back(0.0f); 
	m_coordBuffer.Colors().push_back(1.0f); m_coordBuffer.Colors().push_back(0.0f);

	//draw the Z axis line

	//first vertex
	m_coordBuffer.Vertices().push_back(0); 
	m_coordBuffer.Vertices().push_back(0);
	m_coordBuffer.Vertices().push_back(-size);
	
	//second vertex
	m_coordBuffer.Vertices().push_back(0);
	m_coordBuffer.Vertices().push_back(0); 
	m_coordBuffer.Vertices().push_back(size);

	//color for both vertices
	m_coordBuffer.Colors().push_back(0.0f); m_coordBuffer.Colors().push_back(0.0f);
	m_coordBuffer.Colors().push_back(1.0f); m_coordBuffer.Colors().push_back(0.0f);
	m_coordBuffer.Colors().push_back(0.0f); m_coordBuffer.Colors().push_back(1.0f);

	//fill VBO with coordinate system vertex and color data
	m_coordBuffer.FillData(Buffer::VERTEX_BUFFER);
	m_coordBuffer.FillData(Buffer::COLOR_BUFFER);

	//send texture flag to fragment shader
	TheShader::Instance()->SetUniformData(m_textureFlagUniformID, false);

	//draw coordinate system using shader
	m_coordBuffer.DrawData(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a X and Y coordinate system to help orient objects in world space
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawCoordSystem2D(float size, float lineWidth, int pixelsPerUnit)
{

	//clear the vertex and color data each time function is called 
	//because different sized coordinate systems may be requested
	m_coordBuffer.Vertices().clear();
	m_coordBuffer.Colors().clear();

	//set line width of grid lines based on value passed
	glLineWidth(lineWidth);

	//set vertex data component size to X and Y (2)
	//because we will be sending data for a 2D grid
	m_coordBuffer.SetComponentSize(Buffer::VERTEX_BUFFER, Buffer::XY);

	//draw the X axis line

	//first vertex
	m_coordBuffer.Vertices().push_back(-size * pixelsPerUnit);
	m_coordBuffer.Vertices().push_back(0);

	//second vertex
	m_coordBuffer.Vertices().push_back(size * pixelsPerUnit);
	m_coordBuffer.Vertices().push_back(0);

	//color for both vertices
	m_coordBuffer.Colors().push_back(1.0f); m_coordBuffer.Colors().push_back(0.0f);
	m_coordBuffer.Colors().push_back(0.0f); m_coordBuffer.Colors().push_back(1.0f);
	m_coordBuffer.Colors().push_back(0.0f); m_coordBuffer.Colors().push_back(0.0f);

	//draw the Y axis line

	//first vertex
	m_coordBuffer.Vertices().push_back(0);
	m_coordBuffer.Vertices().push_back(-size * pixelsPerUnit);

	//second vertex
	m_coordBuffer.Vertices().push_back(0);
	m_coordBuffer.Vertices().push_back(size * pixelsPerUnit);

	//color for both vertices
	m_coordBuffer.Colors().push_back(0.0f); m_coordBuffer.Colors().push_back(1.0f);
	m_coordBuffer.Colors().push_back(0.0f); m_coordBuffer.Colors().push_back(0.0f);
	m_coordBuffer.Colors().push_back(1.0f); m_coordBuffer.Colors().push_back(0.0f);

	//fill VBO with coordinate system vertex and color data
	m_coordBuffer.FillData(Buffer::VERTEX_BUFFER);
	m_coordBuffer.FillData(Buffer::COLOR_BUFFER);

	//send texture flag to fragment shader
	TheShader::Instance()->SetUniformData(m_textureFlagUniformID, false);

	//draw coordinate system using shader
	m_coordBuffer.DrawData(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 3D cube based on width, height and depth passed
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawCube3D(float width, float height, float depth, Color color)
{

	//variable to store scale transformation value 
	glm::mat4 scale;

	//bookmark model matrix to create a temporary transformation
	//so that we can scale the 3D cube accordingly and render it
	GameObject::PushMatrix();

		//assign scale value of cube based on dimensions passed and apply to model matrix
	    //because by default the cube model will have been loaded in as a 1 x 1 x 1 cube
		scale = glm::scale(scale, glm::vec3(width, height, depth));
		GameObject::MultiplyMatrix(scale);

		//send model matrix data to vertex shader
		GameObject::ApplyMatrix();

		//set color of cube based on color value passed
		m_cube3D.SetColor(color);

		//send texture flag to fragment shader
		TheShader::Instance()->SetUniformData(m_textureFlagUniformID, false);

		//draw the 3D cube
		m_cube3D.Draw();

	//remove temporary model matrix and go back to previous transformation
	GameObject::PopMatrix();

}
//------------------------------------------------------------------------------------------------------
//function that draws a 2D cube based on width and height passed
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawCube2D(float width, float height, Color color, int pixelsPerUnit)
{

	//store the half dimensions to be used later 
	//because all vertices are drawn around the centre position
	glm::vec2 halfDimension((width * pixelsPerUnit) / 2.0f, (height * pixelsPerUnit) / 2.0f);

	//clear the vertex and color data each time function is called 
	//because different sized cubes may be requested
	m_cubeBuffer2D.Vertices().clear();
	m_cubeBuffer2D.Colors().clear();

	//set color data component size to R, G, B and A (4)
	//because we will be sending color data with alpha channels
	m_cubeBuffer2D.SetComponentSize(Buffer::VERTEX_BUFFER, Buffer::XY);
	m_cubeBuffer2D.SetComponentSize(Buffer::COLOR_BUFFER, Buffer::RGBA);

	//add vertex data for cube 

	//vertex data for vertex #1
	m_cubeBuffer2D.Vertices().push_back(-halfDimension.x);
	m_cubeBuffer2D.Vertices().push_back(halfDimension.y);

	//vertex data for vertex #2
	m_cubeBuffer2D.Vertices().push_back(halfDimension.x);
	m_cubeBuffer2D.Vertices().push_back(halfDimension.y);

	//vertex data for vertex #3
	m_cubeBuffer2D.Vertices().push_back(-halfDimension.x);
	m_cubeBuffer2D.Vertices().push_back(-halfDimension.y);

	//vertex data for vertex #4
	m_cubeBuffer2D.Vertices().push_back(-halfDimension.x);
	m_cubeBuffer2D.Vertices().push_back(-halfDimension.y);

	//vertex data for vertex #5
	m_cubeBuffer2D.Vertices().push_back(halfDimension.x);
	m_cubeBuffer2D.Vertices().push_back(halfDimension.y);

	//vertex data for vertex #6
	m_cubeBuffer2D.Vertices().push_back(halfDimension.x);
	m_cubeBuffer2D.Vertices().push_back(-halfDimension.y);

	//add color data for cube 

	//color data for vertex #1
	m_cubeBuffer2D.Colors().push_back(color.R); m_cubeBuffer2D.Colors().push_back(color.G);
	m_cubeBuffer2D.Colors().push_back(color.B); m_cubeBuffer2D.Colors().push_back(color.A);

	//color data for vertex #2
	m_cubeBuffer2D.Colors().push_back(color.R); m_cubeBuffer2D.Colors().push_back(color.G);
	m_cubeBuffer2D.Colors().push_back(color.B); m_cubeBuffer2D.Colors().push_back(color.A);

	//color data for vertex #3
	m_cubeBuffer2D.Colors().push_back(color.R); m_cubeBuffer2D.Colors().push_back(color.G);
	m_cubeBuffer2D.Colors().push_back(color.B); m_cubeBuffer2D.Colors().push_back(color.A);

	//color data for vertex #4
	m_cubeBuffer2D.Colors().push_back(color.R); m_cubeBuffer2D.Colors().push_back(color.G);
	m_cubeBuffer2D.Colors().push_back(color.B); m_cubeBuffer2D.Colors().push_back(color.A);

	//color data for vertex #5
	m_cubeBuffer2D.Colors().push_back(color.R); m_cubeBuffer2D.Colors().push_back(color.G);
	m_cubeBuffer2D.Colors().push_back(color.B); m_cubeBuffer2D.Colors().push_back(color.A);

	//color data for vertex #6
	m_cubeBuffer2D.Colors().push_back(color.R); m_cubeBuffer2D.Colors().push_back(color.G);
	m_cubeBuffer2D.Colors().push_back(color.B); m_cubeBuffer2D.Colors().push_back(color.A);

	//fill VBO with cube vertex and color data
	m_cubeBuffer2D.FillData(Buffer::VERTEX_BUFFER);
	m_cubeBuffer2D.FillData(Buffer::COLOR_BUFFER);

	//send texture flag to fragment shader
	TheShader::Instance()->SetUniformData(m_textureFlagUniformID, false);

	//draw cube using shader
	m_cubeBuffer2D.DrawData(Buffer::TRIANGLES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 3D sphere 
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawSphere3D(float radius, Color color)
{

	//variable to store scale transformation value 
	glm::mat4 scale;

	//bookmark model matrix to create a temporary transformation
	//so that we can scale the 3D sphere accordingly and render it
	GameObject::PushMatrix();

		//assign scale value of sphere based on radius passed and apply to model matrix
		//because by default the sphere model will have been loaded in with a radius of 1
		scale = glm::scale(scale, glm::vec3(radius, radius, radius));
		GameObject::MultiplyMatrix(scale);

		//send model matrix data to vertex shader
		GameObject::ApplyMatrix();

		//set color of sphere based on color value passed
		m_sphere3D.SetColor(color);

		//send texture flag to fragment shader
		TheShader::Instance()->SetUniformData(m_textureFlagUniformID, false);

		//draw the 3D sphere
		m_sphere3D.Draw();

	//remove temporary model matrix and go back to previous transformation
	GameObject::PopMatrix();

}
//------------------------------------------------------------------------------------------------------
//function that draws a 2D sphere 
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawSphere2D(float radius, Color color, int slices, int pixelsPerUnit)
{

	//vector that will generate values in a circular method 
	//to create the vertices around the origin, forming a circle
	glm::vec2 tempVector; 
	
	//divide the circle into slices based on slices amount passed
	//the more slices, the more detailed the sphere is drawn 
	double tempAngle = 360.0 / (double)slices;

	//clear the vertex and color data each time function is called 
	//because different positioned vectors may be requested
	m_sphereBuffer2D.Vertices().clear();
	m_sphereBuffer2D.Colors().clear();

	//set vertex data component size to X and Y (2)
	//because we will be sending data for a 2D sphere
	m_sphereBuffer2D.SetComponentSize(Buffer::VERTEX_BUFFER, Buffer::XY);

	//set color data component size to R, G, B and A (4)
	//because we will be sending color data with alpha channels
	m_sphereBuffer2D.SetComponentSize(Buffer::COLOR_BUFFER, Buffer::RGBA);

	//draw the sphere
	
	//because we are using a triangle fan for rendering, we need a starting
	//vertex point. Set starting vertex to 0, which will be relative to where
	//the sphere is positioned in client code
	m_sphereBuffer2D.Vertices().push_back(0.0f);
	m_sphereBuffer2D.Vertices().push_back(0.0f);

	//set starting color for vertex origin point
	m_sphereBuffer2D.Colors().push_back(color.R); m_sphereBuffer2D.Colors().push_back(color.G);
	m_sphereBuffer2D.Colors().push_back(color.B); m_sphereBuffer2D.Colors().push_back(color.A);

	//loop through the amount of slices passed and add an extra slice into 
	//the loop to close the sphere off. The loop will use sin and cos internally
	//to generate a vertex point in a circular method around the origin
	//the generated vertices and color data will be added to the sphere's buffer
	for (int i = 0; i < slices + 1; i++)
	{
		
		tempVector.x = (float)(cos(glm::radians(tempAngle * (i + 1))) * radius * pixelsPerUnit);
		tempVector.y = (float)(sin(glm::radians(tempAngle * (i + 1))) * radius * pixelsPerUnit);

		m_sphereBuffer2D.Vertices().push_back((GLfloat)tempVector.x);
		m_sphereBuffer2D.Vertices().push_back((GLfloat)tempVector.y);
		
		m_sphereBuffer2D.Colors().push_back(color.R); m_sphereBuffer2D.Colors().push_back(color.G);
		m_sphereBuffer2D.Colors().push_back(color.B); m_sphereBuffer2D.Colors().push_back(color.A);

	}

	//fill VBO with sphere vertex and color data
	m_sphereBuffer2D.FillData(Buffer::VERTEX_BUFFER);
	m_sphereBuffer2D.FillData(Buffer::COLOR_BUFFER);

	//send texture flag to fragment shader
	TheShader::Instance()->SetUniformData(m_textureFlagUniformID, false);

	//draw sphere using shader
	m_sphereBuffer2D.DrawData(Buffer::TRIANGLE_FAN);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 2D or 3D vector 
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawVector(float x, float y, float z, 
	                          float lineWidth, Color color, int pixelsPerUnit)
{

	//clear the vertex and color data each time function is called 
	//because different positioned vectors may be requested
	m_vectorBuffer.Vertices().clear();
	m_vectorBuffer.Colors().clear();
	
	//set line width of vector based on value passed
	glLineWidth(lineWidth);
	
	//set vertex data component size to X, Y and Z (3)
	//because we will be sending data for a 2D or 3D vector
	m_vectorBuffer.SetComponentSize(Buffer::VERTEX_BUFFER, Buffer::XYZ);
	
	//set color data component size to R, G, B and A (4)
	//because we will be sending color data with alpha channels
	m_vectorBuffer.SetComponentSize(Buffer::COLOR_BUFFER, Buffer::RGBA);
	
	//draw the vector
	
	//starting vertex
	m_vectorBuffer.Vertices().push_back(0);
	m_vectorBuffer.Vertices().push_back(0);
	m_vectorBuffer.Vertices().push_back(0);
	
	//ending vertex
	m_vectorBuffer.Vertices().push_back(x * pixelsPerUnit);
	m_vectorBuffer.Vertices().push_back(y * pixelsPerUnit);
	m_vectorBuffer.Vertices().push_back(z * pixelsPerUnit);
	
	//colors for both vertices
	m_vectorBuffer.Colors().push_back(color.R); m_vectorBuffer.Colors().push_back(color.G);
	m_vectorBuffer.Colors().push_back(color.B); m_vectorBuffer.Colors().push_back(color.A);
	m_vectorBuffer.Colors().push_back(color.R); m_vectorBuffer.Colors().push_back(color.G);
	m_vectorBuffer.Colors().push_back(color.B); m_vectorBuffer.Colors().push_back(color.A);
	
	//fill VBO with vector vertex and color data
	m_vectorBuffer.FillData(Buffer::VERTEX_BUFFER);
	m_vectorBuffer.FillData(Buffer::COLOR_BUFFER);
	
	//send texture flag to fragment shader
	TheShader::Instance()->SetUniformData(m_textureFlagUniformID, false);

	//draw vector using shader
	m_vectorBuffer.DrawData(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 2D or 3D vertex point
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawVertex(float x, float y, float z, 
	                          float pointSize, Color color, int pixelsPerUnit)
{

	//clear the vertex and color data each time function is called 
	//because different positioned vertices may be requested
	m_vertexBuffer.Vertices().clear();
	m_vertexBuffer.Colors().clear();

	//set point size of vertex based on value passed
	glPointSize(pointSize);

	//set vertex data component size to X, Y and Z (3)
	//because we will be sending data for a 2D or 3D point
	m_vertexBuffer.SetComponentSize(Buffer::VERTEX_BUFFER, Buffer::XYZ);

	//set color data component size to R, G, B and A (4)
	//because we will be sending color data with alpha channels
	m_vertexBuffer.SetComponentSize(Buffer::COLOR_BUFFER, Buffer::RGBA);

	//vertex data for vertex point
	m_vertexBuffer.Vertices().push_back(x * pixelsPerUnit);
	m_vertexBuffer.Vertices().push_back(y * pixelsPerUnit);
	m_vertexBuffer.Vertices().push_back(z * pixelsPerUnit);

	//color data for vertex point
	m_vertexBuffer.Colors().push_back(color.R); m_vertexBuffer.Colors().push_back(color.G);
	m_vertexBuffer.Colors().push_back(color.B); m_vertexBuffer.Colors().push_back(color.A);

	//fill VBO with vertex and color data for vertex point
	m_vertexBuffer.FillData(Buffer::VERTEX_BUFFER);
	m_vertexBuffer.FillData(Buffer::COLOR_BUFFER);

	//send texture flag to fragment shader
	TheShader::Instance()->SetUniformData(m_textureFlagUniformID, false);

	//draw vertex using shader
	m_vertexBuffer.DrawData(Buffer::POINTS);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 2D or 3D line segment
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawLine(float x1, float y1, float z1, float x2, float y2, float z2, 
	                        float lineWidth, Color color, int pixelsPerUnit)
{

	//clear the vertex and color data each time function is called 
	//because different positioned line segments may be requested
	m_lineBuffer.Vertices().clear();
	m_lineBuffer.Colors().clear();

	//set line width of line segment based on value passed
	glLineWidth(lineWidth);

	//set vertex data component size to X, Y and Z (3)
	//because we will be sending data for a 2D or 3D line segment
	m_lineBuffer.SetComponentSize(Buffer::VERTEX_BUFFER, Buffer::XYZ);

	//set color data component size to R, G, B and A (4)
	//because we will be sending color data with alpha channels
	m_lineBuffer.SetComponentSize(Buffer::COLOR_BUFFER, Buffer::RGBA);

	//draw the line segment

	//starting vertex
	m_lineBuffer.Vertices().push_back(x1 * pixelsPerUnit);
	m_lineBuffer.Vertices().push_back(y1 * pixelsPerUnit);
	m_lineBuffer.Vertices().push_back(z1 * pixelsPerUnit);

	//ending vertex
	m_lineBuffer.Vertices().push_back(x2 * pixelsPerUnit);
	m_lineBuffer.Vertices().push_back(y2 * pixelsPerUnit);
	m_lineBuffer.Vertices().push_back(z2 * pixelsPerUnit);

	//colors for both vertices
	m_lineBuffer.Colors().push_back(color.R); m_lineBuffer.Colors().push_back(color.G);
	m_lineBuffer.Colors().push_back(color.B); m_lineBuffer.Colors().push_back(color.A);
	m_lineBuffer.Colors().push_back(color.R); m_lineBuffer.Colors().push_back(color.G);
	m_lineBuffer.Colors().push_back(color.B); m_lineBuffer.Colors().push_back(color.A);

	//fill VBO with vector vertex and color data
	m_lineBuffer.FillData(Buffer::VERTEX_BUFFER);
	m_lineBuffer.FillData(Buffer::COLOR_BUFFER);

	//send texture flag to fragment shader
	TheShader::Instance()->SetUniformData(m_textureFlagUniformID, false);

	//draw line segment using shader
	m_lineBuffer.DrawData(Buffer::LINES);

}