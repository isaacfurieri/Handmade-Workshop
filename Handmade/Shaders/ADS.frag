#version 450 

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
	float attConstant;
	float attLinear;
	float attQuadratic;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

//objects that represent the light 
//source, object being lit and viewer
uniform Light light[5];
uniform Material material;
uniform vec3 cameraPosition;

in vec4 colorOut;
in vec3 vertexOut;
in vec3 normalOut;
in vec2 textureOut;
out vec4 pixelColor;

uniform bool isLit;
uniform bool isTextured;
uniform uint totalLights; 
uniform sampler2D textureImage;

//------------------------------------------------------------------------------------------------------
//function that calculates the AMBIENT color value
//------------------------------------------------------------------------------------------------------
vec3 AmbientColor(Light light)
{

	return light.ambient * material.ambient;

}
//------------------------------------------------------------------------------------------------------
//function that calculates the DIFFUSE color value
//------------------------------------------------------------------------------------------------------
vec3 DiffuseColor(Light light, vec3 normal)
{

	//calculate the direction vector between the light and the fragment
	vec3 lightDirection = normalize(light.position - vertexOut);

	//calculate the light intensity based on the light direction vector and the surface normal
	float lightIntensity = max(dot(lightDirection, normal), 0.0);

	//return the final diffuse fragment color
	return light.diffuse * material.diffuse * lightIntensity;

}
//------------------------------------------------------------------------------------------------------
//function that calculates the SPECULAR color value
//------------------------------------------------------------------------------------------------------
vec3 SpecularColor(Light light, vec3 normal)
{

	//calculate the direction vector between the camera and the fragment
	vec3 viewDirection = normalize(cameraPosition - vertexOut);
	
	//calculate the direction vector between the light and the fragment
	//this time we make sure the vector points TOWARDS the fragment 
	vec3 lightDirection = normalize(vertexOut - light.position);

	//reflect the light direction vector around the surface normal
	vec3 reflection = reflect(lightDirection, normal);

	//first find the relation between the reflection vector and the view vector
	//then take that value to the power of the passed in shininess value
	float specularTerm = pow(max(dot(viewDirection, reflection), 0.0), material.shininess);
	
	//return the final specular fragment color
	return light.specular * material.specular * specularTerm;

}
//------------------------------------------------------------------------------------------------------
//function that calculates the ATTENUATION value
//------------------------------------------------------------------------------------------------------
float Attenuation(Light light)
{

	float lightDistance = length(light.position - vertexOut);

	return 1.0 / (light.attConstant + light.attLinear * lightDistance 
	                                + light.attQuadratic * lightDistance * lightDistance);

}
//------------------------------------------------------------------------------------------------------
//the main starting point of our shader
//------------------------------------------------------------------------------------------------------
void main(void)
{

    //if fragment is flagged to be lit then apply lighting calculations 
	if(isLit)
	{
		
		//make sure normal is always normalized
		vec3 normal = normalize(normalOut);

		vec3 totalColor;
		vec3 finalColor;

		//calculate final fragment color using ADS model
		//first we add up the ADS values for each light 
		//and then we apply attenuation to that before 
		//adding that value to the total light color value
		for(int i = 0; i < totalLights; i++)
		{
			 
	        totalColor = AmbientColor(light[i]) + 
			             DiffuseColor(light[i], normal) + 
						 SpecularColor(light[i], normal);

			finalColor += totalColor * Attenuation(light[i]);
		    
		}

		//calculate FINAL fragment color
		pixelColor = vec4(finalColor, 1.0);

	}

	//otherwise simply assign the color value
	else
	{
		pixelColor = colorOut;
	}

	//if fragment is flagged to be textured then apply texel color to final color
	if(isTextured)
	{
		pixelColor = pixelColor * texture(textureImage, textureOut);
	}
	
}