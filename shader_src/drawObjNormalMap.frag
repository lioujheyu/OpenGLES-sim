#version 330 core

in vec2 UV;
in float lightIntensity;
in vec3 specular_color;
in vec3 eyeVector_tangent;

out vec3 color;

uniform sampler2D ColorMap;
uniform sampler2D NormalMap;

void main()
{
	vec3 c1, c2;
	float cfactor; 
	c1 = texture2D( ColorMap, UV ).rgb;
	c2 = texture2D( NormalMap, UV ).rgb;
		
	c2 = c2*2 - vec3(1.0, 1.0, 1.0);
	
	cfactor = dot(c2, normalize(eyeVector_tangent));
	cfactor = clamp(cfactor, 0.0, 1.0);
	
	color = c1 * cfactor * lightIntensity;
	//color = c1 * cfactor;
	//color = c1 * lightIntensity;
	//color = color + specular_color;
	color = clamp(color, 0.0, 1.0);
}