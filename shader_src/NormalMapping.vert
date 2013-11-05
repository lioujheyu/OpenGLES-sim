#version 330 core

in vec4 obj_vertex;
in vec3 obj_normal;
in vec2 obj_texCoord;

out vec2 UV;
out vec3 eyeVector_tangent;

uniform mat4 MVP;
uniform vec3 eye_pos;

void main()
{
	mat3 tangent_mat = mat3(1.0, 0.0, 0.0,
	                        0.0, 0.0, 1.0,
						    0.0, 1.0, 0.0
	                        );
	eyeVector_tangent = tangent_mat * (eye_pos + vec3(0.0,0.0,8.5) - obj_vertex.xyz);

	gl_Position =  MVP * obj_vertex;
	
	UV = obj_texCoord;
}
