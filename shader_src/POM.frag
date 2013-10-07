#version 330 core

uniform sampler2D colorMap;
uniform sampler2D NM_height_Map;

in vec2 TexCoord;
in vec3 eyeVector_tangent;
in vec3 lightVector_tangent;

out vec4 color;

const int sampleNum = 35;
const int sampleNum2nd = 5;

const float step = -1.0 / sampleNum;

const float heightScale = 0.2;

vec3 TraceRay(in vec2 coords, in vec3 dir)
{
	vec2 NewCoords = coords;
	vec2 dUV = dir.xy / dir.z * heightScale * step; 
	float SearchHeight = 1.0;
	float curHeight;
	float hitHeight = 0.0;
	vec2 hitCoord = vec2(0.0f);
	float touch;
	
	for (int i=0; i<sampleNum; i++) {
		SearchHeight+=step;
		NewCoords += dUV;
		curHeight = texture2D(NM_height_Map,NewCoords).w;
		
		//touch = (SearchHeight < curHeight)? 1.0 : 0.0;
		touch = clamp((curHeight - SearchHeight) * 499999.0, 0.0, 1.0);

		//if (touch == 1.0 && hitHeight == 0.0) {
		//	hitHeight = SearchHeight;
		//	hitCoord = NewCoords;
		//}
		hitCoord += touch*clamp((1.0-hitHeight*499999.0),0.0,1.0)*NewCoords;
		hitHeight += touch*clamp((1.0-hitHeight*499999.0),0.0,1.0)*SearchHeight;
	}
	
	NewCoords = (hitHeight == 0.0)? NewCoords : hitCoord;
	NewCoords -= dUV;
	SearchHeight = hitHeight - step;
	hitHeight = 0.0;
	dUV = dUV / sampleNum2nd;
	
	for (int i=0; i<sampleNum2nd; i++) {
		SearchHeight+=(step / sampleNum2nd);
		NewCoords += dUV;
		curHeight = texture2D(NM_height_Map,NewCoords).w;
		touch = clamp((curHeight - SearchHeight) * 499999.0, 0.0, 1.0);
    
		if (touch==1.0 && hitHeight == 0.0) {
			hitHeight = SearchHeight;
			hitCoord = NewCoords;
		}
	}
	return vec3(hitCoord, hitHeight);
}

float TraceShadow(in vec3 coords, in vec3 dir)
{
	vec2 NewCoords = coords.xy;
	float SearchHeight;
	float curHeight;
	float touch;
	float shadow = 0.0;
	
	//SearchHeight = coords.z;
	SearchHeight = texture2D(NM_height_Map,NewCoords.xy).w;
	float diff = (1.0 - SearchHeight) / 20;
	vec2 dUV = dir.xy / dir.z * heightScale * diff; 
	
	for (int i=0; i<20; i++) {
		SearchHeight+=diff;
		NewCoords += dUV;
		curHeight = texture2D(NM_height_Map,NewCoords).w;
		touch = clamp((curHeight - SearchHeight) * 499999.0, 0.0, 1.0);

		shadow += clamp(touch + shadow, 0.0, 1.0)*0.07;
	}
	
	return shadow;
}

void main( void )
{
	vec3 fvLightDirection = normalize( lightVector_tangent );
	vec3 fvViewDirection  = normalize( eyeVector_tangent );
	
	vec3 NewCoord = TraceRay(TexCoord,fvViewDirection);
	//vec2 NewCoord = TexCoord;
	
	vec3  fvNormal		= normalize(texture2D(NM_height_Map, NewCoord.xy).xyz * 2.0 - 1.0);
	float lightIntensity	= dot( fvNormal, fvLightDirection ); 
	
	float Shadow = TraceShadow(NewCoord, fvLightDirection);
	//float Shadow = 0.0f;
	
	vec3  fvReflection     = reflect(-fvLightDirection, fvNormal); 
	float fRDotV           = max( 0.0, dot( fvReflection, fvViewDirection ) );
	
	vec4  fvBaseColor      = texture2D( colorMap, NewCoord.xy);
	
	vec4  fvTotalAmbient   = 0.25f * fvBaseColor; 
	vec4  fvTotalDiffuse   = max(lightIntensity, 0.0) * fvBaseColor; 
	vec4  fvTotalSpecular  = vec4(0.6, 0.6, 0.6, 1.0) * pow(fRDotV, 20);
	
	color = clamp ( fvTotalAmbient + (fvTotalDiffuse + fvTotalSpecular)*(1-Shadow), 0.0, 1.0);
}       