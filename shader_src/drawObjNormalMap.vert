#version 330 core

in vec3 obj_vertex;
in vec3 obj_normal;
in vec4 obj_tangent;
in vec3 obj_bitangent;
in vec2 obj_texcoord;

out vec2 UV;
//out vec3 eyeVector_tangent;
out vec3 lightVector_tangent;

uniform mat4 MV_mat;
uniform mat4 M_mat;
uniform mat4 V_mat;
uniform mat4 P_mat;
uniform vec3 light_pos;

void main ()
{
	float lightIntensity;
	vec4 eye_space, tangent_eyespace, normal_eyespace ,bitangent_eyespace;
	vec3 light_vector, reflect_vector;
	float distance, specular_factor;
	
	eye_space = MV_mat * vec4(obj_vertex, 1.0);
	tangent_eyespace = MV_mat * obj_tangent * obj_tangent.w;
	bitangent_eyespace = MV_mat * vec4(obj_bitangent, 1.0);
	normal_eyespace = MV_mat * vec4(obj_normal, 1.0);
	
	light_vector = (V_mat * vec4(light_pos, 1.0) - eye_space).xyz;

	mat3 tangent_mat = mat3(tangent_eyespace.xyz, bitangent_eyespace.xyz, normal_eyespace.xyz);
	tangent_mat = inverse(tangent_mat);
	lightVector_tangent = tangent_mat * light_vector;
	
	gl_Position =  P_mat * eye_space;
	UV = obj_texcoord;
}