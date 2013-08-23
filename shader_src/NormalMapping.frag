#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 eyeVector_tangent;

// Ouput data
out vec3 color;

uniform sampler2D ColorMap;
uniform sampler2D NormalMap;

void main(){

	vec3 c1, c2;
	float cfactor;
	c1 = texture2D( ColorMap, UV ).rgb;
	c2 = texture2D( NormalMap, UV ).rgb;
	c2 = c2*2 - vec3(1.0, 1.0, 1.0);
	
	cfactor = dot(c2, normalize(eyeVector_tangent));
	cfactor = clamp(cfactor, 0.0, 1.0);
	
	color = c1 * cfactor;
}