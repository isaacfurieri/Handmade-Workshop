#version 450 

in vec3 vertexIn;
in vec4 colorIn;
in vec3 normalIn;
in vec2 textureIn;

out vec3 vertexOut;
out vec4 colorOut;
out vec3 normalOut;
out vec2 textureOut;

uniform mat3 normMatrix;
uniform mat4 texMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main(void)
{

	//send interpolated color to fragment shader
	colorOut = colorIn;

	//send interpolated world space vertex data to fragment shader
    vertexOut = (modelMatrix * vec4(vertexIn, 1.0)).xyz;

	//send interpolated appropriately transformed normal to fragment shader
	normalOut = normMatrix * normalIn;

	//send interpolated and transformed texture coordinate data to fragment shader
	textureOut = (texMatrix * vec4(textureIn, 0.0, 1.0)).xy;

	//interpolate each vertex based on MVP transformations
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(vertexIn, 1.0);

}