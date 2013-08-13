#version 330 core

in vec3 obj_vertex;
in vec3 obj_normal;
in vec2 obj_texcoord;

out vec2 UV;
out float color_scale_factor;

uniform mat4 model_mat;
uniform mat4 VP;
uniform vec3 light_pos;

void main ()
{
	vec4 model_space;
	vec3 light_vector;
	
	model_space = model_mat * vec4(obj_vertex, 1.0);
	light_vector = normalize(light_pos - model_space.xyz);
	
	color_scale_factor = clamp( dot(light_vector,obj_normal), 0.0, 1.0) + 0.15f;
	color_scale_factor = (color_scale_factor > 1.0f)?1.0f:color_scale_factor;
	
	gl_Position =  VP * model_space;
	UV = obj_texcoord;
}