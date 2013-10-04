/*
 * Copyright (c) 2013, Liou Jhe-Yu <lioujheyu@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *	@file rasterizer.cpp
 *  @brief  The Rasterizer related function implementation for GPU class
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#include "gpu_core.h"

void GPU_Core::tileSplit(int x, int y, int level)
{
	int lc; //loop counter

/*
 * c - central
 * n - corner
 *                                  5 6 7
 * The hierachy can be presented as 3 c 4
 *                                  0 1 2
 * Zone[0] = box of 013c, zone[1] = 12c4, zone[2] = 3c56, zone[3] = c467
 */
	float centralTest[3];
	float cornerTest[8][3];
	bool Zone[4][3];

/*
 * pixel stamp: 2 3
 *              0 1
 * We need to calculate 4 pixels in quad concurrently for the DDX/Y instruction
 * and texture scale factor calculation later time in shader core.
 */
	pixel pixelStamp[4];

	tileSplitCnt++;


	PIXPRINTF("-------(%d,%d),Level:%d-----\n",x,y,level);

	centralTest[0] = (x+(1<<level)-prim.v[1].attr[0].x)*Edge[0][0]-
					 (y+(1<<level)-prim.v[1].attr[0].y)*Edge[0][1];
	centralTest[1] = (x+(1<<level)-prim.v[2].attr[0].x)*Edge[1][0]-
					 (y+(1<<level)-prim.v[2].attr[0].y)*Edge[1][1];
	centralTest[2] = (x+(1<<level)-prim.v[0].attr[0].x)*Edge[2][0]-
					 (y+(1<<level)-prim.v[0].attr[0].y)*Edge[2][1];

	if (level == 0) {

/*
 * When split level is 0, the cornerTests are now for each pixel's center test,
 * and not for corner test anymore.
 *
 * cornerTest: 5 7 for pixel stamp: 2 3
 *             0 2                  0 1
 */
		for(lc=0; lc<3; lc++) {
			cornerTest[0][lc] = centralTest[lc] + (-Edge[lc][0]+Edge[lc][1])*0.5;
			cornerTest[2][lc] = centralTest[lc] + ( Edge[lc][0]+Edge[lc][1])*0.5;
			cornerTest[5][lc] = centralTest[lc] + (-Edge[lc][0]-Edge[lc][1])*0.5;
			cornerTest[7][lc] = centralTest[lc] + ( Edge[lc][0]-Edge[lc][1])*0.5;
		}

		pixelStamp[0].attr[0].x = x;
		pixelStamp[0].attr[0].y = y;
		pixelStamp[0].baryCenPos3[0] = cornerTest[0][2]*area2Reciprocal;
		pixelStamp[0].baryCenPos3[1] = cornerTest[0][0]*area2Reciprocal;
		pixelStamp[1].attr[0].x = x+1;
		pixelStamp[1].attr[0].y = y;
		pixelStamp[1].baryCenPos3[0] = cornerTest[2][2]*area2Reciprocal;
		pixelStamp[1].baryCenPos3[1] = cornerTest[2][0]*area2Reciprocal;
		pixelStamp[2].attr[0].x = x;
		pixelStamp[2].attr[0].y = y+1;
		pixelStamp[2].baryCenPos3[0] = cornerTest[5][2]*area2Reciprocal;
		pixelStamp[2].baryCenPos3[1] = cornerTest[5][0]*area2Reciprocal;
		pixelStamp[3].attr[0].x = x+1;
		pixelStamp[3].attr[0].y = y+1;
		pixelStamp[3].baryCenPos3[0] = cornerTest[7][2]*area2Reciprocal;
		pixelStamp[3].baryCenPos3[1] = cornerTest[7][0]*area2Reciprocal;

		//Interpolate the all 4 pixel's attributes, then perform perspective correction

		floatVec4 invW;
		for (int i=0;i<4;i++){
			pixelStamp[i].attr[0].z =
				prim.v[0].attr[0].z +
				pixelStamp[i].baryCenPos3[0]*( prim.v[1].attr[0].z - prim.v[0].attr[0].z ) +
				pixelStamp[i].baryCenPos3[1]*( prim.v[2].attr[0].z - prim.v[0].attr[0].z );
			pixelStamp[i].attr[0].w =
				prim.v[0].attr[0].w +
				pixelStamp[i].baryCenPos3[0]*( prim.v[1].attr[0].w - prim.v[0].attr[0].w ) +
				pixelStamp[i].baryCenPos3[1]*( prim.v[2].attr[0].w - prim.v[0].attr[0].w );

			invW = fvrcp(floatVec4(pixelStamp[i].attr[0].w));

			for (int attrCnt=1;attrCnt<MAX_ATTRIBUTE_NUMBER;attrCnt++){
				if (!varyEnable[attrCnt])
					continue;

				pixelStamp[i].attr[attrCnt] =
					prim.v[0].attr[attrCnt] +
					( prim.v[1].attr[attrCnt] - prim.v[0].attr[attrCnt] )*pixelStamp[i].baryCenPos3[0] +
					( prim.v[2].attr[attrCnt] - prim.v[0].attr[attrCnt] )*pixelStamp[i].baryCenPos3[1];
				pixelStamp[i].attr[attrCnt] =
					pixelStamp[i].attr[attrCnt] * invW;
			}
		}

        /* Drop their ghost flag if they are pass the edge test. But those ghost
         * pixels will be still pushed into shader core.
		 */
		if (cornerTest[0][0]>=0 && cornerTest[0][1]>=0 && cornerTest[0][2]>=0)
            pixelStamp[0].isGhost = false;

		if (cornerTest[2][0]>=0 && cornerTest[2][1]>=0 && cornerTest[2][2]>=0)
            pixelStamp[1].isGhost = false;

		if (cornerTest[5][0]>=0 && cornerTest[5][1]>=0 && cornerTest[5][2]>=0)
            pixelStamp[2].isGhost = false;

		if (cornerTest[7][0]>=0 && cornerTest[7][1]>=0 && cornerTest[7][2]>=0)
            pixelStamp[3].isGhost = false;

		if (pixelStamp[0].isGhost && pixelStamp[1].isGhost &&
			pixelStamp[2].isGhost && pixelStamp[3].isGhost ) {
			return;
		}
		else {
			pixBuffer[pixBufferP  ] = pixelStamp[0];
			pixBuffer[pixBufferP++].threadId = totalProcessingPix++;
			pixBuffer[pixBufferP  ] = pixelStamp[1];
			pixBuffer[pixBufferP++].threadId = totalProcessingPix++;
			pixBuffer[pixBufferP  ] = pixelStamp[2];
			pixBuffer[pixBufferP++].threadId = totalProcessingPix++;
			pixBuffer[pixBufferP  ] = pixelStamp[3];
			pixBuffer[pixBufferP++].threadId = totalProcessingPix++;
//			PIXPRINTF("P:(%3d,%3d)\t \n", (int)pixBuffer[pixBufferP].attr[0].x,
//										  (int)pixBuffer[pixBufferP].attr[0].y);
		}
	}
	else {
		for(lc=0; lc<3; lc++) {
			cornerTest[0][lc] = centralTest[lc] + (-Edge[lc][0]+Edge[lc][1])*(1<<level);
			cornerTest[1][lc] = centralTest[lc] + (            +Edge[lc][1])*(1<<level);
			cornerTest[2][lc] = centralTest[lc] + ( Edge[lc][0]+Edge[lc][1])*(1<<level);
			cornerTest[3][lc] = centralTest[lc] + (-Edge[lc][0]            )*(1<<level);
			cornerTest[4][lc] = centralTest[lc] + ( Edge[lc][0]            )*(1<<level);
			cornerTest[5][lc] = centralTest[lc] + (-Edge[lc][0]-Edge[lc][1])*(1<<level);
			cornerTest[6][lc] = centralTest[lc] + (            -Edge[lc][1])*(1<<level);
			cornerTest[7][lc] = centralTest[lc] + ( Edge[lc][0]-Edge[lc][1])*(1<<level);
		}

		for(lc=0; lc<3; lc++) {
			Zone[0][lc] = (cornerTest[0][lc]>=0) | (cornerTest[1][lc]>=0) | (cornerTest[3][lc]>=0) | (centralTest[lc]>=0);
			Zone[1][lc] = (cornerTest[1][lc]>=0) | (cornerTest[2][lc]>=0) | (centralTest[lc]>=0) | (cornerTest[4][lc]>=0);
			Zone[2][lc] = (cornerTest[3][lc]>=0) | (centralTest[lc]>=0) | (cornerTest[5][lc]>=0) | (cornerTest[6][lc]>=0);
			Zone[3][lc] = (centralTest[lc]>=0) | (cornerTest[4][lc]>=0) | (cornerTest[6][lc]>=0) | (cornerTest[7][lc]>=0);
		}

		if (Zone[0][0] == true && Zone[0][1] == true && Zone[0][2] == true )
			tileSplit(x, y, level-1);

		if (Zone[1][0] == true && Zone[1][1] == true && Zone[1][2] == true )
			if ( (x + (1<<level)) <= RX )
				tileSplit(x+(1<<level), y, level-1);

		if (Zone[2][0] == true && Zone[2][1] == true && Zone[2][2] == true )
			if ( (y + (1<<level)) <= HY )
				tileSplit(x, y+(1<<level), level-1);

		if (Zone[3][0] == true && Zone[3][1] == true && Zone[3][2] == true )
			if ( ((x + (1<<level)) <= RX) && ((y + (1<<level)) <= HY) )
				tileSplit(x+(1<<level), y+(1<<level), level-1);
	}
}

/**
 *	Invoke specified Shader Core for fragment shader processing
 *
 *	@param sid Which shader core id will be used.
 *	@param pixIn Input pixel's pointer.
 */
void GPU_Core::FragmentShaderEXE(int sid, pixel* pixIn0,
										  pixel* pixIn1,
										  pixel* pixIn2,
										  pixel* pixIn3 )
{
	sCore[sid].instPool = FSinstPool;
	sCore[sid].instCnt = FSinstCnt;
	sCore[sid].uniformPool = uniformPool;

	sCore[sid].Init();
	sCore[sid].isEnable[0] = sCore[sid].isEnable[1] =
		sCore[sid].isEnable[2] = sCore[sid].isEnable[3] = true;
	sCore[sid].threadPtr[0] = pixIn0;
	sCore[sid].threadPtr[1] = pixIn1;
	sCore[sid].threadPtr[2] = pixIn2;
	sCore[sid].threadPtr[3] = pixIn3;
	sCore[sid].Run();
}

void GPU_Core::PerFragmentOp(const pixel &pixInput)
{
	bool DepthPass = true;
	int bufOffset;

	if (pixInput.isGhost) {
		totalGhostPix++;
		return;
	}

	if (pixInput.isKilled)
		return;

	bufOffset = (int)pixInput.attr[0].y*viewPortW + (int)pixInput.attr[0].x;

    //Depth test
    if (depthTestEnable){
        if (depthTestMode == GL_NEVER)
            DepthPass = false;
        else if (depthTestMode == GL_LESS)
            DepthPass = pixInput.attr[0].z  < *(dBufPtr + bufOffset);
        else if (depthTestMode == GL_EQUAL)
            DepthPass = pixInput.attr[0].z == *(dBufPtr + bufOffset);
        else if (depthTestMode == GL_LEQUAL)
            DepthPass = pixInput.attr[0].z <= *(dBufPtr + bufOffset);
        else if (depthTestMode == GL_GREATER)
            DepthPass = pixInput.attr[0].z  > *(dBufPtr + bufOffset);
        else if (depthTestMode == GL_NOTEQUAL)
            DepthPass = pixInput.attr[0].z != *(dBufPtr + bufOffset);
        else if (depthTestMode == GL_GEQUAL)
            DepthPass = pixInput.attr[0].z >= *(dBufPtr + bufOffset);
        else if (depthTestMode == GL_ALWAYS)
            DepthPass = true;

        if (DepthPass == false)
            return;
        else
            *(dBufPtr + bufOffset) = pixInput.attr[0].z;
    }

    //Alpha blending
    if (blendEnable){

    }

    //Color buffer write back
    fixColor4 color;
    color = fv2bv(pixInput.attr[1]);

    *(cBufPtr + bufOffset*4 + 0) = color.r;// R
    *(cBufPtr + bufOffset*4 + 1) = color.g;// G
    *(cBufPtr + bufOffset*4 + 2) = color.b;// B
    *(cBufPtr + bufOffset*4 + 3) = color.a;// A

    totalLivePix++;
}

void GPU_Core::ClearBuffer(unsigned int mask)
{
	int i;
	if (mask & GL_COLOR_BUFFER_BIT) {
		for (i = 0; i<viewPortW*viewPortH; i++){
			*(cBufPtr + i*4 + 0) = clearColor.r*255;
			*(cBufPtr + i*4 + 1) = clearColor.g*255;
			*(cBufPtr + i*4 + 2) = clearColor.b*255;
			*(cBufPtr + i*4 + 3) = clearColor.a*255;
		}
	}

	if (mask & GL_DEPTH_BUFFER_BIT)
		for (i = 0; i<viewPortW*viewPortH; i++)
			*(dBufPtr + i) = clearDepth;

//        if (mask & GL_STENCIL_BUFFER_BIT)
//            for (int i = 0; i<TILEHEIGHT*2; i++)
//                for (int j = 0; j<TILEWIDTH*2; j++)
//                    TStencilBuffer[i][j] = StencilClearVal;
}

