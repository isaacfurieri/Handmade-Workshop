#version 330 core

in vec3 vertexIn;
in vec4 colorIn;
in vec2 textureIn;
in vec3 normalIn;

out vec4 colorOut;
out vec2 textureOut;
out vec3 normalOut;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{

	//send interpolated color data to fragment shader
	colorOut = colorIn;

	//send interpolated texture coordinate data to fragment shader
	textureOut = textureIn;

	//send interpolated normal to fragment shader
	normalOut = normalIn;
	
	//interpolate each vertex based on MVP transformations
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexIn, 1.0);
	
}