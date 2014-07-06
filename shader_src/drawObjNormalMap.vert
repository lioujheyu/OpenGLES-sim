#version 330 core

in vec3 obj_vertex;
in vec3 obj_normal;
in vec4 obj_tangent;
in vec2 obj_texcoord;

out vec2 UV;
out float lightIntensity;
out vec3 specular_color;
out vec3 eyeVector_tangent;

uniform mat4 model_mat;
uniform mat4 VP;
uniform vec3 light_pos;
uniform vec3 eye_pos;

void main ()
{
	vec4 model_space;
	vec3 light_vector, reflect_vector, view_vector;
	vec3 bitangent;
	float distance, specular_factor;
	
	bitangent = cross(obj_normal, obj_tangent.xyz) * obj_tangent.w;
	
	mat3 tangent_mat = mat3(obj_tangent.xyz, bitangent, obj_normal);
	
	model_space = model_mat * vec4(obj_vertex, 1.0);
	distance = length(light_pos - model_space.xyz);
	
	light_vector = normalize((model_mat*vec4(light_pos, 1.0f)).xyz - model_space.xyz);
	//light_vector = normalize(light_pos - model_space.xyz);
	view_vector = normalize(eye_pos - model_space.xyz);
	
	eyeVector_tangent = tangent_mat * view_vector;
		
	lightIntensity = dot(light_vector,obj_normal);
	
	reflect_vector = normalize(2*lightIntensity*obj_normal - light_vector);
	
	
	if (lightIntensity > 0.0) {
		specular_factor = dot(reflect_vector,view_vector);
		specular_factor = (specular_factor>0.0)?specular_factor:0.0;
		specular_factor = pow(specular_factor,5);
		//specular_factor = specular_factor / ( 1 + distance*distance*0.001);
		specular_color = specular_factor * vec3(0.4, 0.4, 0.4)*2;
	}
	else
		specular_color = vec3(0.0f,0.0f,0.0f);
	
	lightIntensity = (lightIntensity>0.0)?lightIntensity:0.0;
	lightIntensity = (lightIntensity + 0.25f) / ( 1 + distance*distance*0.002);
	
	gl_Position =  VP * model_space;
	UV = obj_texcoord;
}