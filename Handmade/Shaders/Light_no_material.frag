#version 460

struct Light
{
	vec3 position;
	float intensity;
	vec4 color;  
	vec4 attenuation;  
};

in vec4 colorOut;
in vec3 vertexOut;
in vec3 normalOut;
in vec2 textureOut;

out vec4 pixelColor;

uniform Light light;
uniform float finalAlpha;
uniform float emissiveness;
uniform vec3 cameraPosition;

vec4 GetDiffuseSpecular(in vec3 position, in vec3 normal, in vec4 lightColor, 
in vec3 lightPosition, in float lightIntensity, in float specularFactor, in float specularAmount) 
{
	vec3 lightDirection = normalize(lightPosition - position);
	vec3 viewDirection = normalize(cameraPosition - position);
	vec3 reflection = normalize(reflect(-lightDirection, normal)); 

	float intensity = max(dot(normal, lightDirection), 0.0);
	float specScale = smoothstep(0.0, 0.01, intensity);

	float specular = lightColor.a; 
	float spec = pow(max(dot(-reflection, viewDirection), 0.0), specularFactor) * specScale * specular * specularAmount;

	return vec4(intensity * lightColor.xyz, spec) * lightIntensity;
}

void main()
{	
	float specularFactor = 2.0; 
	float specularAmount = 1.0; 

	vec4 lightAccum = vec4(0.0); 	
	vec4 shadowlightTemp = GetDiffuseSpecular(vertexOut, 
	normalOut.xyz, light.color, light.position, light.intensity, specularFactor, specularAmount);

	vec4 lightingShadow = vec4(shadowlightTemp.rgb * colorOut.rgb, shadowlightTemp.w);
	vec4 lightingPoints = lightAccum + lightingShadow;

	vec3 ambientColor = vec3(0.1, 0.1, 0.1); 
	vec4 diffuseColor = vec4(colorOut.rgb, 1.0);
	
	float depthValue = gl_FragCoord.z / gl_FragCoord.w; 

	lightAccum.rgb = mix(diffuseColor.rgb, (lightAccum.rgb + lightingPoints.rgb) * diffuseColor.rgb, emissiveness);			
	lightAccum.a += lightingPoints.a;

	lightAccum.rgb = max(lightAccum.rgb, ambientColor * diffuseColor.rgb);

	pixelColor = vec4(lightAccum.rgb + vec3(lightAccum.a), diffuseColor.a);
	pixelColor.a *= finalAlpha; 
}