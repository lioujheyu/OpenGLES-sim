#version 330 core

in vec3 obj_vertex;
in vec2 obj_texCoord;

uniform vec3 light_pos;
uniform vec3 eye_pos;
uniform vec3 obj_normal;
uniform vec3 obj_Binormal;
uniform vec3 obj_Tangent;

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 project_mat;

out vec2 TexCoord;
out vec3 eyeVector_tangent;
flat centroid out vec3 lightVector_tangent;
   
void main( void )
{
	vec4 eye_space, view_space;
	vec3 light_vector, reflect_vector, view_vector;
	float distance, specular_factor;
	
	eye_space = view_mat * model_mat * vec4(obj_vertex, 1.0);
   
	light_vector = (view_mat * vec4(light_pos, 1.0) - eye_space).xyz;
	view_vector = (view_mat * vec4(eye_pos, 1.0) - eye_space).xyz;
	
	vec3 fvBinormal	= (view_mat* model_mat * vec4(obj_Binormal, 0.0f)).xyz;
	vec3 fvTangent	= (view_mat* model_mat * vec4(obj_Tangent, 0.0f)).xyz;
	vec3 fvNormal	= (view_mat* model_mat * vec4(obj_normal, 0.0f)).xyz;

	eyeVector_tangent.x  = dot( fvTangent, view_vector );
	eyeVector_tangent.y  = dot( fvBinormal, view_vector );
	eyeVector_tangent.z  = dot( fvNormal, view_vector );

	lightVector_tangent.x  = dot( fvTangent, light_vector );
	lightVector_tangent.y  = dot( fvBinormal, light_vector );
	lightVector_tangent.z  = dot( fvNormal, light_vector );

	gl_Position =  project_mat * eye_space;
	TexCoord = obj_texCoord;
}