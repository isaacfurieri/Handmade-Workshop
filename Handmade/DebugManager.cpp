#include <iostream>
#include <string>
#include <glew.h>
#include <glm.hpp>
#include "DebugManager.h"
#include "GameObject.h"
#include "PipelineManager.h"
#include "ScreenManager.h"

//------------------------------------------------------------------------------------------------------
//function that checks for OpenGL errors and displays meaningful custom error messages on screen
//------------------------------------------------------------------------------------------------------
void DebugManager::CheckError()
{

	//query OpenGL for errors which will return the first 
	//error that occured since this function was last called
	GLenum errorCode = glGetError();

	//based on error code enum type returned output a more friendly error message
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
//function that creates the debug VBOs, loads models and links all shader attributes
//------------------------------------------------------------------------------------------------------
bool DebugManager::CreateDebugObjects(GLint size)
{

	if (!m_cube3D.LoadModel("Assets\\Models\\Cube.obj", "CUBE_3D"))
	{
		return false;
	}

	if (!m_sphere3D.LoadModel("Assets\\Models\\Sphere.obj", "SPHERE_3D"))
	{
		return false;
	}

	CreateGrid2D(size);
	CreateGrid3D(size);

	m_lineBuffer.CreateBuffers("LINE", 2);
	m_lineBuffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_lineBuffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGB, Buffer::FLOAT);
	m_lineBuffer.FillVBO(Buffer::VERTEX_BUFFER, (GLuint*)nullptr, 6 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);
	m_lineBuffer.FillVBO(Buffer::COLOR_BUFFER, (GLuint*)nullptr, 6 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);

	m_coordBuffer.CreateBuffers("COORD_SYS", 6);
	m_coordBuffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_coordBuffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGB, Buffer::FLOAT);
	m_coordBuffer.FillVBO(Buffer::VERTEX_BUFFER, (GLuint*)nullptr, 18 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);
	m_coordBuffer.FillVBO(Buffer::COLOR_BUFFER, (GLuint*)nullptr, 18 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);

	m_vertexBuffer.CreateBuffers("VERTEX", 1);
	m_vertexBuffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_vertexBuffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGB, Buffer::FLOAT);
	m_vertexBuffer.FillVBO(Buffer::VERTEX_BUFFER, (GLuint*)nullptr, 3 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);
	m_vertexBuffer.FillVBO(Buffer::COLOR_BUFFER, (GLuint*)nullptr, 3 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);

	m_vectorBuffer.CreateBuffers("VECTOR", 2);
	m_vectorBuffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_vectorBuffer.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGB, Buffer::FLOAT);
	m_vectorBuffer.FillVBO(Buffer::VERTEX_BUFFER, (GLuint*)nullptr, 6 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);
	m_vectorBuffer.FillVBO(Buffer::COLOR_BUFFER, (GLuint*)nullptr, 6 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);

	m_cubeBuffer2D.CreateBuffers("CUBE_2D", 6, true);
	m_cubeBuffer2D.BindEBO();
	m_cubeBuffer2D.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XY, Buffer::FLOAT);
	m_cubeBuffer2D.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGBA, Buffer::FLOAT);
	m_cubeBuffer2D.FillEBO(nullptr, 18 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);
	m_cubeBuffer2D.FillVBO(Buffer::VERTEX_BUFFER, (GLfloat*)nullptr, 12 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);
	m_cubeBuffer2D.FillVBO(Buffer::COLOR_BUFFER, (GLfloat*)nullptr, 24 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);

	m_sphereBuffer2D.CreateBuffers("SPHERE_2D", 100);
	m_sphereBuffer2D.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XY, Buffer::FLOAT);
	m_sphereBuffer2D.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGBA, Buffer::FLOAT);
	m_sphereBuffer2D.FillVBO(Buffer::VERTEX_BUFFER, (GLuint*)nullptr, 200 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);
	m_sphereBuffer2D.FillVBO(Buffer::COLOR_BUFFER, (GLuint*)nullptr, 400 * sizeof(GLfloat), Buffer::DYNAMIC_FILL);

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that destroys all debug VBOs and unloads all model files
//------------------------------------------------------------------------------------------------------
void DebugManager::DestroyDebugObjects()
{
	
	m_sphereBuffer2D.DestroyBuffers("SPHERE_2D");
	m_cubeBuffer2D.DestroyBuffers("CUBE_2D");
	m_vectorBuffer.DestroyBuffers("VECTOR");
	m_vertexBuffer.DestroyBuffers("VERTEX");
	m_coordBuffer.DestroyBuffers("COORD_SYS");
	m_lineBuffer.DestroyBuffers("LINE");
	m_gridBuffer3D.DestroyBuffers("GRID_3D");
	m_gridBuffer2D.DestroyBuffers("GRID_2D");
	m_sphere3D.UnloadModel("SPHERE_3D");
	m_cube3D.UnloadModel("CUBE_3D");

}
//------------------------------------------------------------------------------------------------------
//function that draws a square 2D grid to help orient objects in world space
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawGrid2D(GLfloat lineWidth)
{

	//reset model matrix to identity since the grid is likely
	//the very first object to get rendered in the scene
	GameObject::SetIdentity();

	//send all flags and matrices to shaders
	GameObject::SendToShader(false, false);

	//set line width of grid lines based on value passed
	m_gridBuffer2D.SetLineWidth(lineWidth);

	//draw grid object
	m_gridBuffer2D.Draw(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a square 3D grid to help orient objects in world space
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawGrid3D(GLfloat lineWidth)
{

	//reset model matrix to identity since the grid is likely
	//the very first object to get rendered in the scene
	GameObject::SetIdentity();

	//send all flags and matrices to shaders
	GameObject::SendToShader(false, false);

	//set line width of grid lines based on value passed
	m_gridBuffer3D.SetLineWidth(lineWidth);

	//draw grid object
	m_gridBuffer3D.Draw(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a X and Y coordinate system to help orient objects in world space
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawCoordSystem2D(GLfloat size, GLfloat lineWidth)
{

	//this value determines how many pixels there are between 
	//each unit because in 2D mode we are working in pixels
	int pixelsPerUnit = TheScreen::Instance()->GetPixelsPerUnit();

	//data that represents vertices for XY axis lines
	GLfloat vertices[] = { -size * pixelsPerUnit, 0, size * pixelsPerUnit, 0,      //X axis
		                    0, -size * pixelsPerUnit, 0, size * pixelsPerUnit };   //Y axis

	//data that represents colors for axis lines
	GLfloat colors[] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,       //X axis        
		                 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f  };     //Y axis

	//since we are sharing one coordinate system buffer re-bind vertex buffer each time 
	//this is to ensure that if the 3D version is called, we set the VBO back to using XY
	m_coordBuffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XY, Buffer::FLOAT);

	//fill vertex and color VBOs with data 
	m_coordBuffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_coordBuffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	//send flags and matrices to shaders
	GameObject::SendToShader(false, false);

	//set line width of grid lines based on value passed
	m_coordBuffer.SetLineWidth(lineWidth);

	//draw coordinate system 
	m_coordBuffer.Draw(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a X, Y and Z coordinate system to help orient objects in world space
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawCoordSystem3D(GLfloat size, GLfloat lineWidth)
{

	//data that represents vertices for XYZ axis lines
	GLfloat vertices[] = { -size,  0.0f,  0.0f, size, 0.0f, 0.0f,             //X axis
						    0.0f, -size,  0.0f, 0.0f, size, 0.0f,             //Y axis
						    0.0f,  0.0f, -size, 0.0f, 0.0f, size  };          //Z axis

	//data that represents colors for axis lines
	GLfloat colors[] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,      //X axis
						 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,      //Y axis
						 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f  };   //Z axis

	//since we are sharing one coordinate system buffer re-bind vertex buffer each time 
	//this is to ensure that if the 2D version is called, we set the VBO back to using XYZ
	m_coordBuffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);

	//fill vertex and color VBOs with data 
	m_coordBuffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_coordBuffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	//send flags and matrices to shaders
	GameObject::SendToShader(false, false);

	//set line width of grid lines based on value passed
	m_coordBuffer.SetLineWidth(lineWidth);

	//draw coordinate system 
	m_coordBuffer.Draw(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 2D cube based on width and height passed
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawCube2D(GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

	//this value determines how many pixels there are between 
	//each unit because in 2D mode we are working in pixels
	int pixelsPerUnit = TheScreen::Instance()->GetPixelsPerUnit();

	//data that represents vertices for quad image
	GLfloat vertices[] = { 0, height * pixelsPerUnit,                        //top left
						   width * pixelsPerUnit, height * pixelsPerUnit,    //top right
						   width * pixelsPerUnit, 0,                         //bottom right
						   0, 0 };                                           //bottom left

	//data that represents colors for quad image
	GLfloat colors[] = { r, g, b, a,                      //top left
						 r, g, b, a,					  //top right
						 r, g, b, a,					  //bottom right
						 r, g, b, a  };					  //bottom left

	//data that represents indices for quad image
	GLuint indices[] = { 0, 1, 3,
						 3, 1, 2 };

	//fill EBO and all VBOs for simple quad
	m_cubeBuffer2D.FillEBO(indices, sizeof(indices));
	m_cubeBuffer2D.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_cubeBuffer2D.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	//send flags and matrices to shaders
	GameObject::SendToShader(false, false);

	//draw cube
	m_cubeBuffer2D.Draw(Buffer::TRIANGLES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 3D cube based on width, height and depth passed
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawCube3D(GLfloat width, GLfloat height, GLfloat depth,
	                          GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

	//bookmark model matrix to create a temporary transformation
	//so that we can scale the 3D cube accordingly and render it
	//thereafter go back to the previous transformation and continue
	GameObject::PushMatrix();

		//assign scale value of cube based on dimensions passed and apply to model matrix
	    //because by default the cube model will have been loaded in as a 1 x 1 x 1 cube
		GameObject::Scale(width, height, depth);

		//send flags and matrices data to shaders
		GameObject::SendToShader(false, false);

		//set color of cube based on color value passed
		m_cube3D.SetColor(r, g, b, a);

		//draw the 3D cube
		m_cube3D.Draw();

	GameObject::PopMatrix();

	//pushing and popping the model matrix allows for the temporary sizing 
	//of the cube not to interfere with other client code transformations

}
//------------------------------------------------------------------------------------------------------
//function that draws a 2D sphere on screen
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawSphere2D(GLfloat radius, GLfloat r, GLfloat g, 
	                            GLfloat b, GLfloat a, GLint slices)
{

	//we need the amount of bytes to advance by for 
	//each iteration for the vertex and color VBOs
	const int BYTES_PER_VERTEX = 2 * sizeof(GLfloat);
	const int BYTES_PER_COLOR = 4 * sizeof(GLfloat);

	//divide the circle into slices based on slices amount passed
	//the more slices, the more detailed the sphere is drawn 
	double tempAngle = 360.0 / (double)slices;

	//this value determines how many pixels there are between 
	//each unit because in 2D mode we are working in pixels
	int pixelsPerUnit = TheScreen::Instance()->GetPixelsPerUnit();

	//because we are using a triangle fan for rendering, we need a starting
	//vertex point. Set starting vertex to 0, which will be relative to where
	//the sphere is positioned in client code and set the starting color too
	GLfloat startVertex[2] = { 0.0f, 0.0f };
	GLfloat startColor[4] =  { r, g, b, a };

	m_sphereBuffer2D.AppendVBO(Buffer::VERTEX_BUFFER, startVertex, BYTES_PER_VERTEX, 0);
	m_sphereBuffer2D.AppendVBO(Buffer::COLOR_BUFFER, startColor, BYTES_PER_COLOR, 0);

	//when filling the remaining VBOs, we begin from these offset points
	GLuint offsetVertex = BYTES_PER_VERTEX;
	GLuint offsetColor = BYTES_PER_COLOR;

	//loop through the amount of slices passed and add an extra slice into 
	//the loop to close the sphere off. The loop will use sin and cos internally
	//to generate a vertex point in a circular method around the origin
	//the generated vertices and color data will be added to the sphere's buffer
	for (int i = 0; i < slices + 1; i++)
	{

		GLfloat vertices[] = { (GLfloat)(cos(glm::radians(tempAngle * (i + 1))) * radius * pixelsPerUnit),     //X coord
			                   (GLfloat)(sin(glm::radians(tempAngle * (i + 1))) * radius * pixelsPerUnit) };   //Y coord

		GLfloat colors[] = { r, g, b, a, r, g, b, a };

		//fill vertex and color VBO
		m_sphereBuffer2D.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_sphereBuffer2D.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		//advance vertex and color VBO offsets
		offsetVertex += BYTES_PER_VERTEX;
		offsetColor += BYTES_PER_COLOR;

	}

	//send flags and matrices to shaders
	GameObject::SendToShader(false, false);

	//draw 2D sphere
	m_sphereBuffer2D.Draw(Buffer::TRIANGLE_FAN);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 3D sphere 
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawSphere3D(GLfloat radius, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

	//bookmark model matrix to create a temporary transformation
	//so that we can scale the 3D sphere accordingly and render it
	//thereafter go back to the previous transformation and continue
	GameObject::PushMatrix();

		//assign scale value of sphere based on radius passed and apply to model matrix
		//because by default the sphere model will have been loaded in with a radius of 1
		GameObject::Scale(radius, radius, radius);

		//send flags and matrices to shaders
		GameObject::SendToShader(false, false);

		//set color of sphere based on color value passed
		m_sphere3D.SetColor(r, g, b, a);

		//draw the 3D sphere
		m_sphere3D.Draw();

	GameObject::PopMatrix();

	//pushing and popping the model matrix allows for the temporary sizing 
	//of the sphere not to interfere with other client code transformations

}
//------------------------------------------------------------------------------------------------------
//function that draws a 2D vector 
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawVector2D(GLfloat x, GLfloat y, GLfloat lineWidth,
								GLfloat r, GLfloat g, GLfloat b)
{

	//this value determines how many pixels there are between 
	//each unit because in 2D mode we are working in pixels	
	int pixelsPerUnit = TheScreen::Instance()->GetPixelsPerUnit();

	//data for vertex and color of vector which starts at an origin point based on
	//the client's transformations and extends out at a size based on values passed in
	GLfloat vertices[] = { 0.0f, 0.0f, x * pixelsPerUnit, y * pixelsPerUnit };
	GLfloat colors[] =   { r, g, b, r, g, b };

	//since we are sharing one line buffer re-bind vertex buffer each time 
	//so that if the 3D version is called, we set the VBO back to using XY
	m_lineBuffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XY, Buffer::FLOAT);

	//fill vertex and color buffer with above array data
	m_lineBuffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_lineBuffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	//send flags and matrices to shaders
	GameObject::SendToShader(false, false);

	//set line width of vector based on value passed
	m_lineBuffer.SetLineWidth(lineWidth);

	//draw vector 
	m_lineBuffer.Draw(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 3D vector 
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawVector3D(GLfloat x, GLfloat y, GLfloat z,
							    GLfloat lineWidth, GLfloat r, GLfloat g, GLfloat b)
{

	//data for vertex and color of vector which starts at an origin point based on
	//the client's transformations and extends out at a size based on values passed in
	GLfloat vertices[] = { 0.0f, 0.0f, 0.0f, x, y, z };
	GLfloat colors[] =   { r, g, b, r, g, b };

	//since we are sharing one line buffer re-bind vertex buffer each time 
	//so that if the 2D version is called, we set the VBO back to using XYZ
	m_lineBuffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);

	//fill vertex and color buffer with above array data
	m_lineBuffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_lineBuffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	//send flags and matrices to shaders
	GameObject::SendToShader(false, false);

	//set line width of vector based on value passed
	m_lineBuffer.SetLineWidth(lineWidth);

	//draw vector 
	m_lineBuffer.Draw(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 2D vertex point
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawVertex2D(GLfloat x, GLfloat y, GLfloat pointSize,
							    GLfloat r, GLfloat g, GLfloat b)
{

	//this value determines how many pixels there are between 
	//each unit because in 2D mode we are working in pixels	
	int pixelsPerUnit = TheScreen::Instance()->GetPixelsPerUnit();

	//vertex and color data for a simple dot on the screen which 
	//renders at an origin point based on the client's transformations 
	GLfloat vertices[] = { x * pixelsPerUnit, y * pixelsPerUnit, };
	GLfloat colors[] =   { r, g, b };

	//since we are sharing one vertex buffer re-bind vertex buffer each time 
	//so that if the 3D version is called, we set the VBO back to using XY
	m_vertexBuffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XY, Buffer::FLOAT);

	//fill vertex and color buffer with above array data
	m_vertexBuffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_vertexBuffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	//send flags and matrices to shaders
	GameObject::SendToShader(false, false);

	//set point size of vertex based on value passed
	m_vertexBuffer.SetPointSize(pointSize);

	//draw vertex 
	m_vertexBuffer.Draw(Buffer::POINTS);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 3D vertex point
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawVertex3D(GLfloat x, GLfloat y, GLfloat z, 
	                            GLfloat pointSize, GLfloat r, GLfloat g, GLfloat b)
{

	//vertex and color data for a simple dot on the screen which 
	//renders at an origin point based on the client's transformations 
	GLfloat vertices[] = { x, y, z };
	GLfloat colors[] =   { r, g, b };

	//since we are sharing one vertex buffer re-bind vertex buffer each time 
	//so that if the 2D version is called, we set the VBO back to using XYZ
	m_vertexBuffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);

	//fill vertex and color buffer with above array data
	m_vertexBuffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_vertexBuffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	//send flags and matrices to shaders
	GameObject::SendToShader(false, false);

	//set point size of vertex based on value passed
	m_vertexBuffer.SetPointSize(pointSize);

	//draw vertex 
	m_vertexBuffer.Draw(Buffer::POINTS);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 2D or 3D line segment
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawLine2D(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,
							  GLfloat lineWidth, GLfloat r, GLfloat g, GLfloat b)
{

	//this value determines how many pixels there are between 
	//each unit because in 2D mode we are working in pixels	
	int pixelsPerUnit = TheScreen::Instance()->GetPixelsPerUnit();

	//data for vertex and color of vector which starts and ends at
	//specified point passed in and is based on client transformations
	GLfloat vertices[] = { x1 * pixelsPerUnit, y1 * pixelsPerUnit,
						   x2 * pixelsPerUnit, y2 * pixelsPerUnit };

	GLfloat colors[] = { r, g, b, r, g, b };

	//since we are sharing one line buffer re-bind vertex buffer each time 
	//so that if the 3D version is called, we set the VBO back to using XY
	m_lineBuffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XY, Buffer::FLOAT);

	//fill vertex and color buffer with above array data
	m_lineBuffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_lineBuffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	//send flags and matrices to shaders
	GameObject::SendToShader(false, false);

	//set line width of line segment based on value passed
	m_lineBuffer.SetLineWidth(lineWidth);

	//draw line segment 
	m_lineBuffer.Draw(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that draws a 3D line segment
//------------------------------------------------------------------------------------------------------
void DebugManager::DrawLine3D(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, 
	                          GLfloat lineWidth, GLfloat r, GLfloat g, GLfloat b)
{

	//data for vertex and color of vector which starts and ends at
	//specified point passed in and is based on client transformations
	GLfloat vertices[] = { x1, y1, z1, x2, y2, z2 };
	GLfloat colors[] =   { r, g, b, r, g, b };

	//since we are sharing one line buffer re-bind vertex buffer each time 
	//so that if the 2D version is called, we set the VBO back to using XYZ
	m_lineBuffer.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);

	//fill vertex and color buffer with above array data
	m_lineBuffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::DYNAMIC_FILL);
	m_lineBuffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::DYNAMIC_FILL);

	//send flags and matrices to shaders
	GameObject::SendToShader(false, false);

	//set line width of line segment based on value passed
	m_lineBuffer.SetLineWidth(lineWidth);

	//draw line segment 
	m_lineBuffer.Draw(Buffer::LINES);

}
//------------------------------------------------------------------------------------------------------
//function that creates a 2D grid and all its buffers
//------------------------------------------------------------------------------------------------------
void DebugManager::CreateGrid2D(GLint size)
{

	//the offsets will add up and keep track of how
	//many bytes are added to the vertex and color VBOs
	GLuint offsetVertex = 0;
	GLuint offsetColor = 0;

	//constants to help clarify different calculations below
	const int SIZE = size;
	const int QUADRANTS = 4;
	const int BYTES_PER_VERTEX = 4 * sizeof(GLfloat);
	const int BYTES_PER_COLOR = 6 * sizeof(GLfloat);

	//create VAO, VBOs and EBO which is based on the amount of
	//lines (2 vertices for each line) multipled by the 4 quadrants
	m_gridBuffer2D.CreateBuffers("GRID_2D", SIZE * 2 * QUADRANTS);

	//bind all VBOs and shader attributes together with VAO
	m_gridBuffer2D.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XY, Buffer::FLOAT);
	m_gridBuffer2D.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGB, Buffer::FLOAT);

	//create empty VBOs to be filled below 
	int bufferSizeVert = SIZE * QUADRANTS * BYTES_PER_VERTEX;
	int bufferSizeColor = SIZE * QUADRANTS * BYTES_PER_COLOR;

	m_gridBuffer2D.FillVBO(Buffer::VERTEX_BUFFER, (GLfloat*)nullptr, bufferSizeVert, Buffer::STATIC_FILL);
	m_gridBuffer2D.FillVBO(Buffer::COLOR_BUFFER, (GLfloat*)nullptr, bufferSizeColor, Buffer::STATIC_FILL);

	//this value determines how many pixels there are between 
	//each unit because in 2D mode we are working in pixels
	int pixelsPerUnit = TheScreen::Instance()->GetPixelsPerUnit();

	//now we create the grid one quadrant at a time	and fill each vertex and
	//color VBO with the line's vertex and color data accordingly. The offset
	//will get updated each iteration and keep track of how many bytes into
	//each VBO we already are in order to fill the VBOs in the right place

	//**********************************
	//create all negative X lines
	//**********************************

	for (int i = 0; i < size; i++)
	{

		//data that represents vertices for grid lines
		GLfloat vertices[] = { (GLfloat)(-size * pixelsPerUnit) + (i * pixelsPerUnit),
							   (GLfloat)(-size * pixelsPerUnit),                            //first vertex
							   (GLfloat)((-size * pixelsPerUnit) + (i * pixelsPerUnit)),
							   (GLfloat)(size * pixelsPerUnit) };                           //second vertex

		//data that represents colors for grid lines (all white)
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		//fill vertex and color VBO
		m_gridBuffer2D.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_gridBuffer2D.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		//advance vertex and color buffer offsets
		offsetVertex += BYTES_PER_VERTEX;
		offsetColor += BYTES_PER_COLOR;

	}

	//**********************************
	//create all positive X lines
	//**********************************

	for (int i = 1; i < size + 1; i++)
	{

		//data that represents vertices for grid lines
		GLfloat vertices[] = { (GLfloat)(0 + (i * pixelsPerUnit)),
							   (GLfloat)(-size * pixelsPerUnit),           //first vertex
							   (GLfloat)(0 + (i * pixelsPerUnit)),
							   (GLfloat)(size * pixelsPerUnit) };          //second vertex

		//data that represents colors for grid lines (all white)
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		//fill vertex and color VBO
		m_gridBuffer2D.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_gridBuffer2D.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		//advance vertex and color buffer offsets
		offsetVertex += BYTES_PER_VERTEX;
		offsetColor += BYTES_PER_COLOR;

	}

	//**********************************
	//create all negative Y lines
	//**********************************

	for (int i = 0; i < size; i++)
	{

		//data that represents vertices for grid lines
		GLfloat vertices[] = { (GLfloat)(-size * pixelsPerUnit),
							   (GLfloat)((-size * pixelsPerUnit) + (i * pixelsPerUnit)),         //first vertex
							   (GLfloat)(size * pixelsPerUnit),
							   (GLfloat)((-size * pixelsPerUnit) + (i * pixelsPerUnit)) };       //second vertex

		//data that represents colors for grid lines (all white)
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		//fill vertex and color VBO
		m_gridBuffer2D.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_gridBuffer2D.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		//advance vertex and color buffer offsets
		offsetVertex += BYTES_PER_VERTEX;
		offsetColor += BYTES_PER_COLOR;

	}

	//**********************************
	//create all positive Y lines
	//**********************************

	for (int i = 1; i < size + 1; i++)
	{

		//data that represents vertices for grid lines
		GLfloat vertices[] = { (GLfloat)(-size * pixelsPerUnit),
							   (GLfloat)(0 + (i * pixelsPerUnit)),         //first vertex
							   (GLfloat)(size * pixelsPerUnit),
							   (GLfloat)(0 + (i * pixelsPerUnit)) };       //second vertex

		//data that represents colors for grid lines (all white)
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		//fill vertex and color VBO
		m_gridBuffer2D.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offsetVertex);
		m_gridBuffer2D.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offsetColor);

		//advance vertex and color buffer offsets
		offsetVertex += BYTES_PER_VERTEX;
		offsetColor += BYTES_PER_COLOR;

	}

}
//------------------------------------------------------------------------------------------------------
//function that creates a 3D grid and all its buffers
//------------------------------------------------------------------------------------------------------
void DebugManager::CreateGrid3D(GLint size)
{

	//the offset will add up and keep track of 
	//how many bytes are added to the VBOs
	GLuint offset = 0;

	//constants to help clarify different calculations below
	const int SIZE = size;
	const int QUADRANTS = 4;
	const int BYTES_PER_VERTEX = 6 * sizeof(GLfloat);
	const int BYTES_PER_COLOR = 6 * sizeof(GLfloat);

	//create VAO, VBOs and EBO which is based on the amount of
	//lines (2 vertices for each line) multipled by the 4 quadrants
	m_gridBuffer3D.CreateBuffers("GRID_3D", SIZE * 2 * QUADRANTS);

	//bind all VBOs and shader attributes together with VAO
	m_gridBuffer3D.BindVBO(Buffer::VERTEX_BUFFER, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_gridBuffer3D.BindVBO(Buffer::COLOR_BUFFER, "colorIn", Buffer::RGB, Buffer::FLOAT);

	//create empty VBOs to be filled below 
	int bufferSize = SIZE * QUADRANTS * BYTES_PER_VERTEX;
	m_gridBuffer3D.FillVBO(Buffer::VERTEX_BUFFER, (GLfloat*)nullptr, bufferSize, Buffer::STATIC_FILL);
	m_gridBuffer3D.FillVBO(Buffer::COLOR_BUFFER, (GLfloat*)nullptr, bufferSize, Buffer::STATIC_FILL);

	//now we create the grid one quadrant at a time	and fill each vertex and
	//color VBO with the line's vertex and color data accordingly the offset
	//will get updated each iteration and keep track of how many bytes into
	//each VBO we already are in order to fill the VBOs in the right place

	//**********************************
	//create all negative X lines
	//**********************************

	for (int i = 0; i < size; i++)
	{

		//data that represents vertices for grid lines
		GLfloat vertices[] = { (GLfloat)(-size + i), 0.0f, (GLfloat)size,      //first vertex
			                   (GLfloat)(-size + i), 0.0f, (GLfloat)-size };   //second vertex

		//data that represents colors for grid lines (all white)
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		//fill vertex and color VBO
		m_gridBuffer3D.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offset);
		m_gridBuffer3D.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offset);

		//advance vertex buffer offsets
		offset += BYTES_PER_VERTEX;

	}

	//**********************************
	//create all positive X lines
	//**********************************

	for (int i = 1; i < size + 1; i++)
	{

		//data that represents vertices for grid lines
		GLfloat vertices[] = { (GLfloat)(0 + i), 0.0f, (GLfloat)size,      //first vertex
							   (GLfloat)(0 + i), 0.0f, (GLfloat)-size };   //second vertex

		//data that represents colors for grid lines (all white)
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		//fill vertex and color VBO
		m_gridBuffer3D.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offset);
		m_gridBuffer3D.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offset);

		//advance vertex buffer offsets
		offset += BYTES_PER_VERTEX;

	}

	//**********************************
	//create all negative Z lines
	//**********************************

	for (int i = 0; i < size; i++)
	{

		//data that represents vertices for grid lines
		GLfloat vertices[] = { (GLfloat)(-size), 0.0f, (GLfloat)(-size + i),      //first vertex
							   (GLfloat)(size), 0.0f, (GLfloat)(-size + i) };     //second vertex

		//data that represents colors for grid lines (all white)
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		//fill vertex and color VBO
		m_gridBuffer3D.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offset);
		m_gridBuffer3D.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offset);

		//advance vertex buffer offsets
		offset += BYTES_PER_VERTEX;

	}

	//**********************************
	//create all positive Z lines
	//**********************************

	for (int i = 1; i < size + 1; i++)
	{

		//data that represents vertices for grid lines
		GLfloat vertices[] = { (GLfloat)(-size), 0.0f, (GLfloat)(0 + i),      //first vertex
							   (GLfloat)(size), 0.0f, (GLfloat)(0 + i) };     //second vertex

		//data that represents colors for grid lines (all white)
		GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		//fill vertex and color VBO
		m_gridBuffer3D.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), offset);
		m_gridBuffer3D.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), offset);

		//advance vertex buffer offsets
		offset += BYTES_PER_VERTEX;

	}

}