#version 330 core

in vec2 UV;
in float lightIntensity;
in float specular_factor;

out vec3 color;

uniform sampler2D ColorMap;

void main()
{

	vec3 c1;
	color = texture2D( ColorMap, UV ).rgb;
	color = color * lightIntensity;
	color = color + vec3(specular_factor);
	color = clamp(color, 0.0, 1.0);
	
}