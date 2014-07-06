#version 330 core

in vec2 UV;
in vec3 specular_color;
//in vec3 eyeVector_tangent;
in vec3 lightVector_tangent;

out vec3 color;

uniform sampler2D ColorMap;
uniform sampler2D NormalMap;

void main()
{
	vec3 c1, fvNormal;
	float cfactor; 
	c1 = texture2D( ColorMap, UV ).rgb;
	fvNormal = texture2D( NormalMap, UV ).rgb * 2.0 - 1.0;
		
	cfactor = max(0.0, dot(fvNormal, normalize(lightVector_tangent)));
	
	//color = c1 * clamp(cfactor + 0.25, 0.0, 1.0);
	//color = c1 * cfactor;
	color = c1;
	//color = color + specular_color;
	color = clamp(color, 0.0, 1.0);
}