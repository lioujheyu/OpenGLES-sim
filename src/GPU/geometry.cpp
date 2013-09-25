/**
 *	@file geometry.cpp
 *  @brief The Geometry related GPU function module
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#include "gpu_core.h"

void GPU_Core::InitPrimitiveAssembly()
{
    stripIndicator = false;

    switch (drawMode) {
    case GL_TRIANGLES:
    case GL_TRIANGLE_FAN:
    case GL_TRIANGLE_STRIP:
        vtxCntDwn = 3;
        break;
    case GL_LINES:
    case GL_LINE_LOOP:
    case GL_LINE_STRIP:
        vtxCntDwn = 2;
        break;
    default:
        vtxCntDwn = 1;
    }
}

/****** Grahphic Related Function ******/

/**
 *	Invoke specified Shader Core for vertex shader processing
 *
 *	@param sid Which shader core id will be used.
 *	@param input Input pointer
 */

///@todo Raise the usage of 4 exec units.
void GPU_Core::VertexShaderEXE(int sid, void *input)
{
	sCore[sid].instPool = VSinstPool;
	sCore[sid].instCnt = VSinstCnt;
	sCore[sid].uniformPool = uniformPool;
	sCore[sid].shaderType = VERTEX_SHADER;

	sCore[sid].Init();
	sCore[sid].isEnable[0] = true;
	sCore[sid].input[0] = input;
	sCore[sid].Run();
}

void GPU_Core::PerspectiveDivision()
{
	float w = 1.0/curVtx.attr[0].w;
	curVtx.attr[0].w = 1.0;

	for (int i=0; i<MAX_ATTRIBUTE_NUMBER; i++) {
		if (varyEnable[i] == false)
			continue;
		else
			curVtx.attr[i] = curVtx.attr[i] * w;
	}
}

void GPU_Core::ViewPort()
{
    float x,y,z;

    x = curVtx.attr[0].x;
    y = curVtx.attr[0].y;
    z = curVtx.attr[0].z;

    x = x*viewPortW/2 + viewPortLX + viewPortW/2;
    y = y*viewPortH/2 + viewPortLY + viewPortH/2;
    z = z*(depthRangeF-depthRangeN)/2 + (depthRangeF+depthRangeN)/2;

    curVtx.attr[0].x = x;
    curVtx.attr[0].y = y;
    curVtx.attr[0].z = z;
}

void GPU_Core::PrimitiveAssembly()
{
    switch (drawMode) {
    case GL_TRIANGLES:
            curPrim.v[vtxCntDwn-1] = curVtx;
            curPrim.clipCoord[vtxCntDwn-1] = curClipCoord;
        break;

	/*	Vertex order in Strip mode
	 *	-1, 0, 1
	 *	 0, 2, 1
	 *	 1, 2, 3
	 *	 2, 4, 3
	 *	 3, 4, 5
	 *	 4, 6, 5
	 */
    case GL_TRIANGLE_STRIP:
    	if (vtxCntDwn == 1) {
			if (stripIndicator == false) {
				curPrim.v[2] = curPrim.v[0];
				curPrim.clipCoord[2] = curPrim.clipCoord[0];
				curPrim.v[0] = curVtx;
				curPrim.clipCoord[0] = curClipCoord;
				stripIndicator = true;
			}
			else {
				curPrim.v[2] = curPrim.v[1];
				curPrim.clipCoord[2] = curPrim.clipCoord[1];
				curPrim.v[1] = curVtx;
				curPrim.clipCoord[1] = curClipCoord;
				stripIndicator = false;
			}
		}
    	else if (vtxCntDwn == 3) {
			curPrim.v[0] = curVtx;
			curPrim.clipCoord[0] = curClipCoord;
    	}
		else if (vtxCntDwn == 2) {
			curPrim.v[1] = curVtx;
			curPrim.clipCoord[1] = curClipCoord;
		}
        break;

	/*	Vertex order in Fan mode
	 *	1, 0, 0
	 *	1, 0, 2
	 *	1, 2, 3
	 *	1, 3, 4
	 *	1, 4, 5
	 *	1, 5, 6
	 */
    case GL_TRIANGLE_FAN:
        if (vtxCntDwn == 1) {
			curPrim.v[1] = curPrim.v[0];
			curPrim.clipCoord[1] = curPrim.clipCoord[0];
			curPrim.v[0] = curVtx;
			curPrim.clipCoord[0] = curClipCoord;
        }
        else if (vtxCntDwn == 3) {
			curPrim.v[2] = curVtx;
			curPrim.clipCoord[2] = curClipCoord;
        }
		else if (vtxCntDwn == 2) {
            curPrim.v[0] = curVtx;
            curPrim.clipCoord[0] = curClipCoord;
		}
        break;
    default:
    	printf("GPU_Core: Nonsupport draw mode: %x\n",drawMode);
    	exit(1);
        break;
    }

    vtxCntDwn--;

    if (vtxCntDwn == 0)
    {
		totalProcessingPrimitive++;
        primStack.push(curPrim);

        switch (drawMode) {
        case GL_TRIANGLES:
            vtxCntDwn = 3;
            break;
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN:
            vtxCntDwn = 1;
            break;
        default:
        	printf("GPU_Core: Nonsupport draw mode: %x",drawMode);
			exit(1);
            break;
        }
    }
}

/// @todo Clipping
void GPU_Core::Clipping()
{
	int outsideGrade = 0;

	for (int i=0; i<3; i++) {
		if (prim.clipCoord[i].x > fabs(prim.clipCoord[i].w) ||
			prim.clipCoord[i].y > fabs(prim.clipCoord[i].w) ||
			prim.clipCoord[i].z > fabs(prim.clipCoord[i].w)  )
			outsideGrade++;
	}

	if (outsideGrade == 3)
		prim.iskilled = true;
}

void GPU_Core::TriangleSetup()
{
	float doubleArea;

	Edge[0][0] = prim.v[0].attr[0].y - prim.v[1].attr[0].y;
	Edge[0][1] = prim.v[0].attr[0].x - prim.v[1].attr[0].x;
	Edge[1][0] = prim.v[1].attr[0].y - prim.v[2].attr[0].y;
	Edge[1][1] = prim.v[1].attr[0].x - prim.v[2].attr[0].x;
	Edge[2][0] = prim.v[2].attr[0].y - prim.v[0].attr[0].y;
	Edge[2][1] = prim.v[2].attr[0].x - prim.v[0].attr[0].x;

	doubleArea = Edge[0][1]*Edge[1][0] - Edge[0][0]*Edge[1][1];

//	if (fabs(doubleArea) > 1000000)
//		printf("What the fuck!!\n");

	area2Reciprocal = 1/doubleArea;

	LY = MIN3(prim.v[0].attr[0].y, prim.v[1].attr[0].y, prim.v[2].attr[0].y);
	LY = CLAMP(LY, viewPortLY, viewPortLY+viewPortH-1);
	LX = MIN3(prim.v[0].attr[0].x, prim.v[1].attr[0].x, prim.v[2].attr[0].x);
	LX = CLAMP(LX, viewPortLX, viewPortLX+viewPortW-1);
	HY = MAX3(prim.v[0].attr[0].y, prim.v[1].attr[0].y, prim.v[2].attr[0].y);
	HY = CLAMP(HY, viewPortLY, viewPortLY+viewPortH-1);
	RX = MAX3(prim.v[0].attr[0].x, prim.v[1].attr[0].x, prim.v[2].attr[0].x);
	RX = CLAMP(RX, viewPortLX, viewPortLX+viewPortW-1);
}

void GPU_Core::Culling()
{
	float tmp1, tmp2;

	if (cullingEnable) {
		switch (cullFaceMode) {
		case GL_BACK:
			if (area2Reciprocal > 0)
				prim.iskilled = true;
			break;
		case GL_FRONT:
			if (area2Reciprocal < 0)
				prim.iskilled = true;
			break;
		case GL_FRONT_AND_BACK:
			prim.iskilled = false;
			break;
		default:
			fprintf(stderr, "Culling: Undefined culling mode %x\n", cullFaceMode);
			break;
		}
	}

	/* Eliminate all (area < 0) condition to simplify the operation in
	 * tile split and interpolation.
	 */
	if (area2Reciprocal < 0) {
		std::swap(prim.v[1], prim.v[2]);

		Edge[1][0] = -Edge[1][0];
		Edge[1][1] = -Edge[1][1];
		tmp1 = Edge[0][0];
		tmp2 = Edge[0][1];
		Edge[0][0] = -Edge[2][0];
		Edge[0][1] = -Edge[2][1];
		Edge[2][0] = -tmp1;
		Edge[2][1] = -tmp2;

		area2Reciprocal = -area2Reciprocal;
	}
}

