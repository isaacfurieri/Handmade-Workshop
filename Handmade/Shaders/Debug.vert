#version 150

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

in vec4 colorIn;
in vec3 vertexIn;
out vec4 fragColor;

void main(void)
{

	fragColor = colorIn;
	gl_Position = projectionMatrix * modelviewMatrix * vec4(vertexIn, 1.0);
	
}