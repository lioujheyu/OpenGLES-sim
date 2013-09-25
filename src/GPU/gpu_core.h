/**
 *	@file gpu_core.h
 *  @brief The GPU TOP module simulator header
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef GPU_CORE_H_INCLUDED
#define GPU_CORE_H_INCLUDED

#include <GLES3/gl3.h>
#include <string>
#include <utility>
#include <algorithm>

#include "gpu_config.h"
#include "gpu_type.h"
#include "shader_core.h"

#ifdef GPU_INFO
#	define GPUPRINTF(fmt, ...) \
		do { if (DBG_ON) fprintf(GPU_INFO_PTR, fmt, ##__VA_ARGS__); } while (0)
#else
#	define GPUPRINTF(fmt, ...)
#endif //GPU_INFO
#ifdef GPU_INFO_FILE
#	define GPU_INFO_PTR GPUINFOfp
#else
#	define GPU_INFO_PTR stderr
#endif

#ifdef PIXEL_INFO
#	define PIXPRINTF(fmt, ...) \
		do { if (DBG_ON) fprintf(PIXEL_INFO_PTR, fmt, ##__VA_ARGS__); } while (0)
#else
#	define PIXPRINTF(fmt, ...)
#endif //PIXEL_INFO
#ifdef PIXEL_INFO_FILE
#	define PIXEL_INFO_PTR PIXELINFOfp
#else
#	define PIXEL_INFO_PTR stderr
#endif


/**
 *	@brief The major class for whole GPU hardware design
 */
class GPU_Core
{
public:
	GPU_Core();
	~GPU_Core();

    GLenum			drawMode;
    int         	vtxCount;
    int				vtxIndicesType;
    int         	vtxFirst;
    const void  	*vtxPointer[MAX_ATTRIBUTE_NUMBER];
    const void  	*vtxIndicesPointer;
    int				vtxInputMode; //0: DrawArray, 1:DrawElements
    int         	attrSize[MAX_ATTRIBUTE_NUMBER];
    bool        	attrEnable[MAX_ATTRIBUTE_NUMBER];
    bool        	varyEnable[MAX_ATTRIBUTE_NUMBER];
    float       	depthRangeN, depthRangeF;
    int         	viewPortLX, viewPortLY,
					viewPortW, viewPortH;

    bool            blendEnable, depthTestEnable, cullingEnable;
    GLenum			cullFaceMode, frontFace;
    GLenum			depthTestMode;
    GLenum			blendingMode;
    float           DepthRef;

	///Texture min/mag filter for each texture unit
	///@{
	GLenum 			minFilter[MAX_TEXTURE_CONTEXT],
					magFilter[MAX_TEXTURE_CONTEXT];
	///@}

    GLenum 			wrapS[MAX_TEXTURE_CONTEXT],
					wrapT[MAX_TEXTURE_CONTEXT];
	textureImage 	tex2D[MAX_TEXTURE_CONTEXT];
	textureImage 	texCubeNX[MAX_TEXTURE_CONTEXT];
	textureImage 	texCubeNY[MAX_TEXTURE_CONTEXT];
	textureImage 	texCubeNZ[MAX_TEXTURE_CONTEXT];
	textureImage 	texCubePX[MAX_TEXTURE_CONTEXT];
	textureImage 	texCubePY[MAX_TEXTURE_CONTEXT];
	textureImage 	texCubePZ[MAX_TEXTURE_CONTEXT];
	unsigned char	*cBufPtr;
    float			*dBufPtr;

    floatVec4		uniformPool[MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS];
    int				VSinstCnt, FSinstCnt;
    instruction		*VSinstPool, *FSinstPool;

    unsigned int	clearMask;
    bool			clearStat;
	floatVec4		clearColor;
    float			clearDepth;

    /// @name Statistic
    ///@{
    FILE 			*GPUINFOfp;
	FILE 			*PIXELINFOfp;
    int				totalProcessingPrimitive,
					totalCulledPrimitive,
					totalProcessingVtx,
					totalProcessingPix,
					totalGhostPix,
					totalLivePix;
	int 			tileSplitCnt;
    ///@}

    void        	Run();
    void 			PassConfig2SubModule();

private:
	ShaderCore		sCore[MAX_SHADER_CORE];

	//Geometry
	vertex      	curVtx;
	floatVec4		curClipCoord;

	primitive   	prim, curPrim;
	std::stack<primitive> primStack;

	/// @name Primitive Assembly related member
	///@{
	///How many vertex are insufficient to form a primitive.
    int         	vtxCntDwn;
    bool         	stripIndicator;
    ///@}

	//Rasterizer
	float           Edge[3][3]; ///< Edge equation's coefficient
    float           area2Reciprocal;

    ///@name Boundary Box
    ///@{
    int             LX,	RX, LY,	HY;
    ///@}

    pixel           pixBuffer[256];
    int             pixBufferP;


	/// @name Invoke Shader Core
	///@{
    void 			VertexShaderEXE(int sid, void *input);
    void 			FragmentShaderEXE(int sid,
									  void *input0,
									  void *input1,
									  void *input2,
									  void *input3);
	///@}

    /// @name Geometry
    ///@{
    void			FetchVertexData(unsigned int);
    void        	PerspectiveDivision();
    void        	ViewPort();
    void        	InitPrimitiveAssembly();
    void        	PrimitiveAssembly();
    void        	Clipping();
    void            TriangleSetup();
    void        	Culling();
    ///@}

    /// @name Rasterizer
    ///@{
    void            tileSplit(int x, int y, int level);
    void            PerFragmentOp(pixel pixInput);
    void 			ClearBuffer(unsigned int mask);
    ///@}

};

extern GPU_Core gpu;

#endif // GPU_CORE_H_INCLUDED
