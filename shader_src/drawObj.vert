#version 330 core

in vec3 obj_vertex;
in vec3 obj_normal;
in vec2 obj_texcoord;

out vec2 UV;
out float color_scale_factor;

uniform mat4 model_mat;
uniform mat4 VP;
uniform vec3 eye_pos;

void main ()
{
	vec4 model_space;
	vec3 eye_vector;
	
	model_space = model_mat * vec4(obj_vertex, 1.0);
	eye_vector = eye_pos - model_space.xyz;
	
	color_scale_factor = clamp(dot(eye_vector,obj_normal), 0.0, 1.0);
	
	gl_Position =  VP * model_space;
	UV = obj_texcoord;
}

