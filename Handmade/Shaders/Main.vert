#version 150

uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

in vec4 colorIn;
in vec3 vertexIn;
in vec2 textureIn;

out vec4 fragColor;
out vec2 textureOut;

void main(void)
{

	textureOut = textureIn;
	fragColor = colorIn;
	gl_Position = projectionMatrix * modelviewMatrix * vec4(vertexIn, 1.0);
	
}