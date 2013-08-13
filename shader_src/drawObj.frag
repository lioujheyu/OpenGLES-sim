#version 330 core

in vec2 UV;
in float color_scale_factor;

out vec3 color;

uniform sampler2D ColorMap;

void main(){

	vec3 c1;
	color = texture2D( ColorMap, UV ).rgb;
	color = color * color_scale_factor;
	
}