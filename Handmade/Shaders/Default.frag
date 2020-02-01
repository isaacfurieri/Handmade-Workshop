#version 450  

in vec3 colorOut;
in vec2 textureOut;
out vec4 pixelColor;

uniform bool isTextured;
uniform sampler2D textureImage;

void main(void)
{

    //if fragment is flagged to be textured then apply texel color to final color
	if(isTextured)
	{
		pixelColor = pixelColor * texture(textureImage, textureOut);
	}

	//otherwise simply assign the color value
	else
	{
		pixelColor = vec4(colorOut, 1.0);
	}

}