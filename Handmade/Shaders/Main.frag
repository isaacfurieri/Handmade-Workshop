#version 150

uniform sampler2D textureImage;

in vec4 fragColor;
in vec2 textureOut;

out vec4 colorOut;

void main(void)
{

	colorOut = fragColor * texture(textureImage, textureOut.st);

}