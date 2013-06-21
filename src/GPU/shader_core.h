#ifndef SHADER_CORE_H_INCLUDED
#define SHADER_CORE_H_INCLUDED

#include "gpu_type.h"
#include "gpu_config.h"

class ShaderCore {
public:

	int shaderType; ///< Vertex/Fragment Shader
	void *input;
	int instCnt; ///<Program Length
	instruction const *instPool;
	floatVec4 const *uniformPool;


	///statitic

	ShaderCore();
	void Init();

	void Exec();
	void Print();
	void FetchData();
	void WriteBack();
	floatVec4 ReadByMask(floatVec4 in, char *mask);
	void WriteByMask(floatVec4 val, floatVec4* fvdst, char *mask);

private:
	int PC; ///<Program Counter
	instruction	curInst;
	vertex *vtxPtr;
	pixel *pixPtr;

	floatVec4 reg[MAX_SHADER_REG_VECTOR];
	floatVec4 dst, src[3];
	int tid, tType;
};


#endif // SHADER_CORE_H_INCLUDED
