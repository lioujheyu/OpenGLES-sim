#version 330

in vec3 UV;
out vec4 color;
uniform samplerCube cubemap;

void main (void)
{
	color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	color = texture(cubemap, UV);
}