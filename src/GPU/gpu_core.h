/**
 *	@file gpu_core.h
 *  @brief The GPU TOP module simulator header
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef GPU_CORE_H_INCLUDED
#define GPU_CORE_H_INCLUDED

#include "gpu_config.h"
#include "gpu_type.h"
#include "shader_core.h"
#include "texture_unit.h"

class GPU_Core
{
public:

	FILE *GPUINFOfp;
	FILE *PIXELINFOfp;
	FILE *TEXELINFOfp;

    int         	vtxCount;
    int         	vtxFirst;
    const void  	*vtxPointer[MAX_ATTRIBUTE_NUMBER];
    int         	attrSize[MAX_ATTRIBUTE_NUMBER];
    bool        	attrEnable[MAX_ATTRIBUTE_NUMBER];
	GLenum      	drawMode;
    float       	depthRangeN, depthRangeF;
    int         	viewPortLX, viewPortLY,
					viewPortW, viewPortH;

    bool            blendEnable, depthTestEnable;
    int             AlphaTestMode,DepthTestMode;
    int             AlphaBlendingMode;
    float           AlphaRef,DepthRef;

	int 			minFilter[MAX_TEXTURE_UNIT], ///<Texture filtering mode
					magFilter[MAX_TEXTURE_UNIT]; ///<Texture filtering mode
    int 			wrapS[MAX_TEXTURE_UNIT],
					wrapT[MAX_TEXTURE_UNIT];
	textureImage 	texImage[MAX_TEXTURE_UNIT];
	unsigned char * cBufPtr;
    float *         dBufPtr;

    floatVec4		uniformPool[MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS];
    int				VSinstCnt , FSinstCnt;
    instruction		*VSinstPool, *FSinstPool;

    unsigned int	clearMask;
    bool			clearStat;
	floatVec4		clearColor;
    float			clearDepth;

    void        	Run();

private:
	ShaderCore		sCore[2];
	TextureUnit 	tUnit;

	//Geometry
	vertex      	curVtx;
	primitive   	prim;

	///How many vertex are insufficient to form a primitive.
    int         	vtxCntDwn;
    int         	stripCnt;
    bool        	fanCnt;
    bool        	primitiveRdy;
	//Rasterizer
	float           Edge[3][3]; ///< Edge equation's coinfficient
    float           area2Reciprocal;
    int             LX, RX, LY, HY; ///< Boundary Box
    pixel           pixBuffer[256];
    int             pixBufferP;
    int             texIndx;


    void 			VertexShaderEXE(int sid);
    void 			FragmentShaderEXE(int sid);
    //Geometry
    void        	PerspectiveCorrection();
    void        	ViewPort();
    void        	InitPrimitiveAssembly();
    void        	PrimitiveAssembly();
    void        	Clipping();
    void        	Culling();
    //Rasterizer
	void            TriangleSetup();
    void            PixelGenerate();
    void            pixelSplit(int x, int y, int level);
    pixel           ShaderEXE(pixel pixInput);
    void            PerFragmentOp(pixel pixInput);

    void 			ClearBuffer(unsigned int mask);

};

extern GPU_Core gpu;

#endif // GPU_CORE_H_INCLUDED
