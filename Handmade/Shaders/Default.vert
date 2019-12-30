#version 450 

in vec3 vertexIn;
in vec3 colorIn;
out vec3 colorOut;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main(void)
{

	//send interpolated color data to fragment shader
    colorOut = colorIn;

	//interpolate each vertex based on MVP transformations
	gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(vertexIn, 1.0);

}