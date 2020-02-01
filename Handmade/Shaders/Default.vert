#version 450 

in vec3 vertexIn;
in vec4 colorIn;
in vec2 textureIn;

out vec4 colorOut;
out vec2 textureOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{

	//send interpolated color data to fragment shader
    colorOut = colorIn;

	//send interpolated texture coordinate data to fragment shader
	textureOut = textureIn;

	//interpolate each vertex based on MVP transformations
	gl_Position = projection * view * model * vec4(vertexIn, 1.0);

}