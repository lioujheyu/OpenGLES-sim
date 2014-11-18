#version 330 core

in vec4 obj_vertex;
in vec3 obj_normal;
in vec2 obj_texCoord;

//noperspective out vec2 UV;
out vec2 UV;
out vec3 eyeVector_tangent;
out float distance;

uniform mat4 MVP;
uniform vec3 eye_pos;
uniform vec3 light_pos;

void main()
{
	mat3 tangent_mat = mat3(1.0, 0.0, 0.0,
	                        0.0, 0.0, 1.0,
						    0.0, 1.0, 0.0
	                        );
	eyeVector_tangent = tangent_mat * (light_pos - obj_vertex.xyz);
	
	distance = length(light_pos - obj_vertex.xyz);

	gl_Position =  MVP * obj_vertex;
	
	UV = obj_texCoord;
}
