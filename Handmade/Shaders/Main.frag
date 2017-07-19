#version 330 core

in vec4 colorOut;
in vec2 textureOut;
in vec3 normalOut;

out vec4 pixelColor;

uniform bool isTextured;
uniform sampler2D textureImage;

void main(void)
{

	if(isTextured)
	{	
		pixelColor = colorOut * texture(textureImage, textureOut);  
	}	

	else
	{
		pixelColor = colorOut;
	}

}