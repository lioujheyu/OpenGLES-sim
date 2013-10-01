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
void GPU_Core::VertexShaderEXE(int sid, vertex *vtx)
{
	sCore[sid].instPool = VSinstPool;
	sCore[sid].instCnt = VSinstCnt;
	sCore[sid].uniformPool = uniformPool;

	sCore[sid].Init();
	sCore[sid].isEnable[0] = true;
	sCore[sid].threadPtr[0] = vtx;
	sCore[sid].Run();
}

void GPU_Core::PerspectiveDivision(vertex *vtx)
{
//	float w = 1.0/vtx->attr[0].w;
	float w = fabs(1.0/vtx->attr[0].w);

	vtx->attr[0].w = 1.0;

	for (int i=0; i<MAX_ATTRIBUTE_NUMBER; i++) {
		if (varyEnable[i] == false)
			continue;
		else
			vtx->attr[i] = vtx->attr[i] * w;
	}
}

void GPU_Core::ViewPort(vertex *vtx)
{
    float x,y,z;

    x = vtx->attr[0].x;
    y = vtx->attr[0].y;
    z = vtx->attr[0].z;

    x = x*viewPortW/2 + viewPortLX + viewPortW/2;
    y = y*viewPortH/2 + viewPortLY + viewPortH/2;
    z = z*(depthRangeF-depthRangeN)/2 + (depthRangeF+depthRangeN)/2;

    vtx->attr[0].x = x;
    vtx->attr[0].y = y;
    vtx->attr[0].z = z;
}

void GPU_Core::PrimitiveAssembly()
{
    switch (drawMode) {
    case GL_TRIANGLES:
            curPrim.v[vtxCntDwn-1] = curVtx;
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
				curPrim.v[0] = curVtx;
				stripIndicator = true;
			}
			else {
				curPrim.v[2] = curPrim.v[1];
				curPrim.v[1] = curVtx;
				stripIndicator = false;
			}
		}
    	else if (vtxCntDwn == 3)
			curPrim.v[0] = curVtx;
		else if (vtxCntDwn == 2)
			curPrim.v[1] = curVtx;
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
			curPrim.v[0] = curVtx;
        }
        else if (vtxCntDwn == 3)
			curPrim.v[2] = curVtx;
		else if (vtxCntDwn == 2)
            curPrim.v[0] = curVtx;
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
        primFIFO.push(curPrim);

        switch (drawMode) {
        case GL_TRIANGLES:
            vtxCntDwn = 3;
            break;
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN:
            vtxCntDwn = 1;
            break;
        default:
        	fprintf(stderr,
				"GPU_Core: Nonsupport draw mode: %x",drawMode);
			exit(1);
            break;
        }
    }
}

void GPU_Core::Clipping()
{
	bool outsideClipVolume = false;
	int next;
	float outRatio, outPart, inPart;
	bool outsideZNear[3];

	primitive newPrim;
	vertex newVtx;
	std::stack<vertex> vtxStack;

	outsideZNear[0] = outsideZNear[1] = outsideZNear[2] = false;

	//Check if the primitive is completely outside the clip volume.
	outsideClipVolume = ((prim.v[0].attr[0].x > prim.v[0].attr[0].w) &&
						 (prim.v[1].attr[0].x > prim.v[1].attr[0].w) &&
						 (prim.v[2].attr[0].x > prim.v[2].attr[0].w)
						) ||
						((prim.v[0].attr[0].y > prim.v[0].attr[0].w) &&
						 (prim.v[1].attr[0].y > prim.v[1].attr[0].w) &&
						 (prim.v[2].attr[0].y > prim.v[2].attr[0].w)
						) ||
						((prim.v[0].attr[0].z > prim.v[0].attr[0].w) &&
						 (prim.v[1].attr[0].z > prim.v[1].attr[0].w) &&
						 (prim.v[2].attr[0].z > prim.v[2].attr[0].w)
						) ||
						((prim.v[0].attr[0].x < -prim.v[0].attr[0].w) &&
						 (prim.v[1].attr[0].x < -prim.v[1].attr[0].w) &&
						 (prim.v[2].attr[0].x < -prim.v[2].attr[0].w)
						) ||
						((prim.v[0].attr[0].y < -prim.v[0].attr[0].w) &&
						 (prim.v[1].attr[0].y < -prim.v[1].attr[0].w) &&
						 (prim.v[2].attr[0].y < -prim.v[2].attr[0].w)
						) ||
						((prim.v[0].attr[0].z < -prim.v[0].attr[0].w) &&
						 (prim.v[1].attr[0].z < -prim.v[1].attr[0].w) &&
						 (prim.v[2].attr[0].z < -prim.v[2].attr[0].w)
						);

	if (outsideClipVolume) { //Completely outside the clip volume
		totalCulledPrimitive++;
		prim.iskilled = true;
		return;
	}

	//Check if this primitive intersects zNear plane.
	for (int i=0; i<3; i++) {
		if ( prim.v[i].attr[0].z < -prim.v[i].attr[0].w )
			outsideZNear[i] = true;
	}

	//Clip the primitive if one of the previous tests is true.
	if (outsideZNear[0] || outsideZNear[1] || outsideZNear[2]) {
		totalClippedPrimitive++;

		newPrim.isGenerated = true;

		for (int i=0; i<3; i++) {
			next = (i+1) % 3;
/*
 *	Sutherland-Hodgman Polygon Clipping Algorithm
 */
			// in-to-in
			if (outsideZNear[i]==false && outsideZNear[next]==false)
				vtxStack.push(prim.v[next]);
			// out-to-out
			else if (outsideZNear[i]==true && outsideZNear[next]==true)
				continue;
			// in-to-out (i:in, next:out)
			else if (outsideZNear[i]==false && outsideZNear[next]==true) {
//				outPart = prim.v[next].attr[0].w - prim.v[next].attr[0].z;
//				inPart = prim.v[i].attr[0].w - prim.v[i].attr[0].z;
				outPart = fabs(prim.v[next].attr[0].w + prim.v[next].attr[0].z);
				inPart = fabs(prim.v[i].attr[0].w + prim.v[i].attr[0].z);
				outRatio = outPart / (outPart + inPart);

				for (int j=0; j<MAX_ATTRIBUTE_NUMBER; j++) {
					if (varyEnable[j])
						newVtx.attr[j] = prim.v[next].attr[j]*(1-outRatio) +
										 prim.v[i].attr[j]*outRatio;
				}

				newVtx.threadId = totalProcessingVtx;
				totalProcessingVtx++;
				vtxStack.push(newVtx);
			}
			// out-to-in (i:out, next:in)
			else {
//				outPart = prim.v[i].attr[0].w - prim.v[i].attr[0].z;
//				inPart = prim.v[next].attr[0].w - prim.v[next].attr[0].z;
				outPart = fabs(prim.v[i].attr[0].w + prim.v[i].attr[0].z);
				inPart = fabs(prim.v[next].attr[0].w + prim.v[next].attr[0].z);
				outRatio = outPart / (outPart + inPart);

				for (int j=0; j<MAX_ATTRIBUTE_NUMBER; j++)
					newVtx.attr[j] = prim.v[i].attr[j]*(1-outRatio) +
									 prim.v[next].attr[j]*outRatio;

				newVtx.threadId = totalProcessingVtx;
				totalProcessingVtx++;
				vtxStack.push(newVtx);
				vtxStack.push(prim.v[next]);
			}
		}

		//Assemble vertex into primitive from vtxStack (GL_TRIANGLE_FAN mode)
		newPrim.v[2] = vtxStack.top(); vtxStack.pop();
		newPrim.v[0] = vtxStack.top();	vtxStack.pop();
		while (!vtxStack.empty()) {
			newPrim.v[1] = newPrim.v[0];
			newPrim.v[0] = vtxStack.top(); vtxStack.pop();

			primFIFO.push(newPrim);
			totalGeneratedPrimitive++;
		}

		prim.iskilled = true;
	}
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

	area2Reciprocal = 1/doubleArea;

	LY = MIN3(prim.v[0].attr[0].y, prim.v[1].attr[0].y, prim.v[2].attr[0].y);
	LY = CLAMP(LY, viewPortLY, viewPortLY+viewPortH-1);
/*	Align boundary box to even coordinate to make sure the tile split will not
 *	output any pixel outside the HY and RX boundary.
 */
	LY = LY & 0xfffe;
	LX = MIN3(prim.v[0].attr[0].x, prim.v[1].attr[0].x, prim.v[2].attr[0].x);
	LX = CLAMP(LX, viewPortLX, viewPortLX+viewPortW-1);
	LX = LX & 0xfffe;
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
			fprintf(stderr,
				"Culling: Undefined culling mode %x\n", cullFaceMode);
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

