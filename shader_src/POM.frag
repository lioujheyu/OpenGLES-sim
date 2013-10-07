#version 330 core

uniform vec4 fvDiffuse;
//uniform float fSpecularPower;

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

vec2 TraceRay(in vec2 coords, in vec3 dir)
{
	vec2 NewCoords = coords;
	vec2 dUV = dir.xy / dir.z * heightScale * step; 
	float SearchHeight = 1.0;
	float curHeight;
	float hitHeight = 0.0;
	vec2 hitCoord = coords;
	float touch;
	
	for (int i=0; i<sampleNum; i++) {
		SearchHeight+=step;
		NewCoords += dUV;
		curHeight = texture2D(NM_height_Map,NewCoords).w;
		//touch = (SearchHeight < curHeight)? 1.0 : 0.0;
		touch = clamp((curHeight - SearchHeight) * 499999.0, 0.0, 1.0);

		if (touch == 1.0 && hitHeight == 0.0) {
			hitHeight = SearchHeight;
			hitCoord = NewCoords;
		}
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
	return hitCoord;
}

vec3 TraceRay4(in float height, in vec2 coords, in vec3 dir){
	vec2 NewCoords = coords;
	vec2 dUV = dir.xy * height * 0.1;
	float SearchHeight = 1.0;
	float prev_hits = 0.0;
	float hit_h = 0.0;
	
	for(int i=0;i<10;i++){
		SearchHeight -= 0.1;
		NewCoords += dUV;
		float CurrentHeight = texture2D(NM_height_Map,NewCoords.xy).w;
		float first_hit = clamp((CurrentHeight - SearchHeight - prev_hits) * 499999.0,0.0,1.0);
		hit_h += first_hit * SearchHeight;
		prev_hits += first_hit;
	}

	NewCoords = coords + dUV * (1.0-hit_h) * 10.0 - dUV;
	vec2 Temp = NewCoords;
	SearchHeight = hit_h+0.1;
	float Start = SearchHeight;
	dUV *= 0.2;
	prev_hits = 0.0;
	hit_h = 0.0;
	for(int i=0;i<5;i++){
		SearchHeight -= 0.02;
		NewCoords += dUV;
		float CurrentHeight = texture2D(NM_height_Map,NewCoords.xy).w;
		float first_hit = clamp((CurrentHeight - SearchHeight - prev_hits) * 499999.0,0.0,1.0);
		hit_h += first_hit * SearchHeight ;
		prev_hits += first_hit;    
	}
	NewCoords = Temp + dUV * (Start - hit_h) * 50.0;
	return vec3(NewCoords,hit_h);
}

void main( void )
{
	vec3 fvLightDirection = normalize( lightVector_tangent );
	vec3 fvViewDirection  = normalize( eyeVector_tangent );
	
	//vec3 NewCoord = TraceRay4(0.2,TexCoord,fvViewDirection);
	vec2 NewCoord = TraceRay(TexCoord,fvViewDirection);
	//vec2 NewCoord = TexCoord;
	
	vec3  fvNormal		= normalize(texture2D(NM_height_Map, NewCoord.xy).xyz * 2.0 - 1.0);
	float lightIntensity	= dot( fvNormal, fvLightDirection ); 
	
	float Shadow = 1.0;
	
	vec3  fvReflection     = reflect(-fvLightDirection, fvNormal); 
	float fRDotV           = max( 0.0, dot( fvReflection, fvViewDirection ) );
	
	vec4  fvBaseColor      = texture2D( colorMap, NewCoord.xy);
	
	vec4  fvTotalAmbient   = 0.25f * fvBaseColor; 
	vec4  fvTotalDiffuse   = max(lightIntensity, 0.0) * fvBaseColor; 
	vec4  fvTotalSpecular  = vec4(0.6, 0.6, 0.6, 1.0) * pow(fRDotV, 20);
	
	color = clamp ( fvTotalAmbient + (fvTotalDiffuse + fvTotalSpecular)*Shadow, 0.0, 1.0);
	//color = (vec4(fvNormal, 1.0) + 1.0)/2;
	//color = fvTotalSpecular;
}       