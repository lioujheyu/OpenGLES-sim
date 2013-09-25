#version 330

in vec3 obj_vertex;

out vec3 UV;

uniform mat4 MVP;

void main() 
{
	gl_Position = MVP * vec4(obj_vertex, 1.0);

	UV = obj_vertex;
}