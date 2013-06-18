#ifndef SHADER_CORE_H_INCLUDED
#define SHADER_CORE_H_INCLUDED

#include "gpu_type.h"

struct ShaderCore{

	inline ShaderCore()
	{
		PC = 0;
		shaderType = 0;
	}

	char *asmSrc;

	int PC;
	floatVec4 attrIn[8];
	floatVec4 attrOut[8];
	int shaderType;
	floatVec4 R[16];
	floatVec4 U[16];

	void exec();
};


#endif // SHADER_CORE_H_INCLUDED
