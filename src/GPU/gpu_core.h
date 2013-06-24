/**
 *	@file gpu_core.h
 *  @brief The GPU TOP module simulator header
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef GPU_CORE_H_INCLUDED
#define GPU_CORE_H_INCLUDED

#include <GLES3/gl3.h>

#include "gpu_config.h"
#include "gpu_type.h"
#include "shader_core.h"
#include "texture_unit.h"

class GPU_Core
{
public:
	GPU_Core()
	{
		for (int i=0; i<MAX_ATTRIBUTE_NUMBER; i++)
			attrEnable[i] = false;

		depthRangeN = 0.0;
		depthRangeF = 1.0;
		viewPortLX = viewPortLY = 0.0;

		DepthRef = 255;
		depthTestMode = GL_LESS;
		depthTestEnable = false;
		blendEnable = false;
	}

	FILE *GPUINFOfp;
	FILE *PIXELINFOfp;
	FILE *TEXELINFOfp;

    int         	vtxCount;
    int         	vtxFirst;
    const void  	*vtxPointer[MAX_ATTRIBUTE_NUMBER];
    int         	attrSize[MAX_ATTRIBUTE_NUMBER];
    bool        	attrEnable[MAX_ATTRIBUTE_NUMBER];
	GLenum			drawMode;
    float       	depthRangeN, depthRangeF;
    int         	viewPortLX, viewPortLY,
					viewPortW, viewPortH;

    bool            blendEnable, depthTestEnable;
    GLenum			depthTestMode;
    GLenum			blendingMode;
    float           DepthRef;

	GLenum 			minFilter[MAX_TEXTURE_UNIT], ///<Texture min filtering mode
					magFilter[MAX_TEXTURE_UNIT]; ///<Texture mag filtering mode
    GLenum 			wrapS[MAX_TEXTURE_UNIT],
					wrapT[MAX_TEXTURE_UNIT];
	textureImage 	texImage[MAX_TEXTURE_UNIT];
	unsigned char	*cBufPtr;
    float			*dBufPtr;

    floatVec4		uniformPool[MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS];
    int				VSinstCnt, FSinstCnt;
    instruction		*VSinstPool, *FSinstPool;

    unsigned int	clearMask;
    bool			clearStat;
	floatVec4		clearColor;
    float			clearDepth;

    void        	Run();
    void 			PassConfig2SubModule();

private:
	ShaderCore		sCore[2];

	//Geometry
	vertex      	curVtx;
	primitive   	prim;

    int         	vtxCntDwn;///<How many vertex are insufficient to form a primitive.
    int         	stripCnt;
    bool        	fanCnt;
    bool        	primitiveRdy;
	//Rasterizer
	float           Edge[3][3]; ///< Edge equation's coinfficient
    float           area2Reciprocal;
    int             LX, RX, LY, HY; ///< Boundary Box
    pixel           pixBuffer[256];
    int             pixBufferP;


    void 			VertexShaderEXE(int sid, void *input);
    void 			FragmentShaderEXE(int sid, void *input);
    //Geometry
    void        	PerspectiveCorrection();
    void        	ViewPort();
    void        	InitPrimitiveAssembly();
    void        	PrimitiveAssembly();
	/// @todo (elvis#1#): Clipping
    void        	Clipping();
    /// @todo (elvis#1#): Culling
    void        	Culling();
    //Rasterizer
	void            TriangleSetup();
    void            pixelSplit(int x, int y, int level);
    void            PerFragmentOp(pixel pixInput);

    void 			ClearBuffer(unsigned int mask);

};

extern GPU_Core gpu;

#endif // GPU_CORE_H_INCLUDED
