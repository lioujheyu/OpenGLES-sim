#version 330 core

in vec2 UV;
in float lightIntensity;
in vec3 specular_color;

out vec3 color;

uniform sampler2D ColorMap;

void main()
{
	//color = texture2D( ColorMap, UV ).rgb;
	color = vec3(1.0, 1.0, 1.0);
	color = color * lightIntensity;
	color = color + specular_color;
	color = clamp(color, 0.0, 1.0);
}