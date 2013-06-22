/**
 *	@file rasterizer.cpp
 *  @brief  The Rasterizer related GPU function module implmentation
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#include "gpu_core.h"

void GPU_Core::TriangleSetup()
{
	float constantC;

	Edge[0][0] = prim.v[0].attr[0].y - prim.v[1].attr[0].y;
	Edge[0][1] = prim.v[0].attr[0].x - prim.v[1].attr[0].x;
	Edge[1][0] = prim.v[1].attr[0].y - prim.v[2].attr[0].y;
	Edge[1][1] = prim.v[1].attr[0].x - prim.v[2].attr[0].x;
	Edge[2][0] = prim.v[2].attr[0].y - prim.v[0].attr[0].y;
	Edge[2][1] = prim.v[2].attr[0].x - prim.v[0].attr[0].x;

	constantC = Edge[0][1]*Edge[1][0] - Edge[0][0]*Edge[1][1];
	area2Reciprocal = 1/constantC;

	LY = MIN3(prim.v[0].attr[0].y, prim.v[1].attr[0].y, prim.v[2].attr[0].y);
	LX = MIN3(prim.v[0].attr[0].x, prim.v[1].attr[0].x, prim.v[2].attr[0].x);
	HY = MAX3(prim.v[0].attr[0].y, prim.v[1].attr[0].y, prim.v[2].attr[0].y);
	RX = MAX3(prim.v[0].attr[0].x, prim.v[1].attr[0].x, prim.v[2].attr[0].x);
}

void GPU_Core::pixelSplit(int x, int y, int level)
{
	int lc;
	float centralTest[3];
	float cornerTest[8][3];
	bool Zone[4][3];

	pixel pixelStamp[4];


	PIXPRINTF("-------(%d,%d),Level:%d-----\n",x,y,level);
	TEXPRINTF("XXXX-YYYY-UUUU.UU-VVVV.VV----------------\n");

	centralTest[0] = (x+(1<<level)-prim.v[1].attr[0].x)*Edge[0][0]-
					 (y+(1<<level)-prim.v[1].attr[0].y)*Edge[0][1];
	centralTest[1] = (x+(1<<level)-prim.v[2].attr[0].x)*Edge[1][0]-
					 (y+(1<<level)-prim.v[2].attr[0].y)*Edge[1][1];
	centralTest[2] = (x+(1<<level)-prim.v[0].attr[0].x)*Edge[2][0]-
					 (y+(1<<level)-prim.v[0].attr[0].y)*Edge[2][1];

	if (level == 0) {
		/**
		 * pixel stamp: 2 3
		 *              0 1
		 * We need to calculating 4 pixels in quad concurrently nomatter if
		 * they are both falling into a triangle or not for scale factor calculation
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

		///Interpolate the all 4 pixel's attributes, then perform perspective correction
		for (int i=0;i<4;i++){
			pixelStamp[i].attr[0].z = prim.v[0].attr[0].z +
								pixelStamp[i].baryCenPos3[0]*(prim.v[1].attr[0].z - prim.v[0].attr[0].z) +
								pixelStamp[i].baryCenPos3[1]*(prim.v[2].attr[0].z - prim.v[0].attr[0].z);
			pixelStamp[i].attr[0].w = prim.v[0].attr[0].w +
								pixelStamp[i].baryCenPos3[0]*(prim.v[1].attr[0].w - prim.v[0].attr[0].w) +
								pixelStamp[i].baryCenPos3[1]*(prim.v[2].attr[0].w - prim.v[0].attr[0].w);

			for (int attrCnt=1;attrCnt<MAX_ATTRIBUTE_NUMBER;attrCnt++){
				if (!attrEnable[attrCnt])
					continue;
				pixelStamp[i].attr[attrCnt].s = prim.v[0].attr[attrCnt].s +
												pixelStamp[i].baryCenPos3[0]*(prim.v[1].attr[attrCnt].s - prim.v[0].attr[attrCnt].s) +
												pixelStamp[i].baryCenPos3[1]*(prim.v[2].attr[attrCnt].s - prim.v[0].attr[attrCnt].s);
				pixelStamp[i].attr[attrCnt].s = pixelStamp[i].attr[attrCnt].s / pixelStamp[i].attr[0].w;

				pixelStamp[i].attr[attrCnt].t = prim.v[0].attr[attrCnt].t +
												pixelStamp[i].baryCenPos3[0]*(prim.v[1].attr[attrCnt].t - prim.v[0].attr[attrCnt].t) +
												pixelStamp[i].baryCenPos3[1]*(prim.v[2].attr[attrCnt].t - prim.v[0].attr[attrCnt].t);
				pixelStamp[i].attr[attrCnt].t = pixelStamp[i].attr[attrCnt].t / pixelStamp[i].attr[0].w;

				pixelStamp[i].attr[attrCnt].p = prim.v[0].attr[attrCnt].p +
												pixelStamp[i].baryCenPos3[0]*(prim.v[1].attr[attrCnt].p - prim.v[0].attr[attrCnt].s) +
												pixelStamp[i].baryCenPos3[1]*(prim.v[2].attr[attrCnt].p - prim.v[0].attr[attrCnt].s);
				pixelStamp[i].attr[attrCnt].p = pixelStamp[i].attr[attrCnt].p / pixelStamp[i].attr[0].w;

				pixelStamp[i].attr[attrCnt].q = prim.v[0].attr[attrCnt].q +
												pixelStamp[i].baryCenPos3[0]*(prim.v[1].attr[attrCnt].q - prim.v[0].attr[attrCnt].q) +
												pixelStamp[i].baryCenPos3[1]*(prim.v[2].attr[attrCnt].q - prim.v[0].attr[attrCnt].q);
				pixelStamp[i].attr[attrCnt].q = pixelStamp[i].attr[attrCnt].q / pixelStamp[i].attr[0].w;
			}
		}
		///each attribute needs to get its scale factor, and all 4 pixels' attribute will get theirs here.
		for (int attrCnt=1; attrCnt<MAX_ATTRIBUTE_NUMBER; attrCnt++){
			if (!attrEnable[attrCnt])
				continue;
			pixelStamp[0].scaleFacDX[attrCnt].s = pixelStamp[1].scaleFacDX[attrCnt].s
												= fabs(pixelStamp[1].attr[attrCnt].s-pixelStamp[0].attr[attrCnt].s);
			pixelStamp[0].scaleFacDX[attrCnt].t = pixelStamp[1].scaleFacDX[attrCnt].t
												= fabs(pixelStamp[1].attr[attrCnt].t-pixelStamp[0].attr[attrCnt].t);
			pixelStamp[0].scaleFacDX[attrCnt].p = pixelStamp[1].scaleFacDX[attrCnt].p
												= fabs(pixelStamp[1].attr[attrCnt].p-pixelStamp[0].attr[attrCnt].p);
			pixelStamp[0].scaleFacDX[attrCnt].q = pixelStamp[1].scaleFacDX[attrCnt].q
												= fabs(pixelStamp[1].attr[attrCnt].q-pixelStamp[0].attr[attrCnt].q);

			pixelStamp[2].scaleFacDX[attrCnt].s = pixelStamp[3].scaleFacDX[attrCnt].s
												= fabs(pixelStamp[3].attr[attrCnt].s-pixelStamp[2].attr[attrCnt].s);
			pixelStamp[2].scaleFacDX[attrCnt].t = pixelStamp[3].scaleFacDX[attrCnt].t
												= fabs(pixelStamp[3].attr[attrCnt].t-pixelStamp[2].attr[attrCnt].t);
			pixelStamp[2].scaleFacDX[attrCnt].p = pixelStamp[3].scaleFacDX[attrCnt].p
												= fabs(pixelStamp[3].attr[attrCnt].p-pixelStamp[2].attr[attrCnt].p);
			pixelStamp[2].scaleFacDX[attrCnt].q = pixelStamp[3].scaleFacDX[attrCnt].q
												= fabs(pixelStamp[3].attr[attrCnt].q-pixelStamp[2].attr[attrCnt].q);

			pixelStamp[0].scaleFacDY[attrCnt].s = pixelStamp[2].scaleFacDY[attrCnt].s
												= fabs(pixelStamp[2].attr[attrCnt].s-pixelStamp[0].attr[attrCnt].s);
			pixelStamp[0].scaleFacDY[attrCnt].t = pixelStamp[2].scaleFacDY[attrCnt].t
												= fabs(pixelStamp[2].attr[attrCnt].t-pixelStamp[0].attr[attrCnt].t);
			pixelStamp[0].scaleFacDY[attrCnt].p = pixelStamp[2].scaleFacDY[attrCnt].p
												= fabs(pixelStamp[2].attr[attrCnt].p-pixelStamp[0].attr[attrCnt].p);
			pixelStamp[0].scaleFacDY[attrCnt].q = pixelStamp[2].scaleFacDY[attrCnt].q
												= fabs(pixelStamp[2].attr[attrCnt].q-pixelStamp[0].attr[attrCnt].q);

			pixelStamp[1].scaleFacDY[attrCnt].s = pixelStamp[3].scaleFacDY[attrCnt].s
												= fabs(pixelStamp[3].attr[attrCnt].s-pixelStamp[1].attr[attrCnt].s);
			pixelStamp[1].scaleFacDY[attrCnt].t = pixelStamp[3].scaleFacDY[attrCnt].t
												= fabs(pixelStamp[3].attr[attrCnt].t-pixelStamp[1].attr[attrCnt].t);
			pixelStamp[1].scaleFacDY[attrCnt].p = pixelStamp[3].scaleFacDY[attrCnt].p
												= fabs(pixelStamp[3].attr[attrCnt].p-pixelStamp[1].attr[attrCnt].p);
			pixelStamp[1].scaleFacDY[attrCnt].q = pixelStamp[3].scaleFacDY[attrCnt].q
												= fabs(pixelStamp[3].attr[attrCnt].q-pixelStamp[1].attr[attrCnt].q);
		}

        ///Write valid fragment into waiting buffer if they are truly pass the edge test.
		if ((cornerTest[0][0]>=0 && cornerTest[0][1]>=0 && cornerTest[0][2]>=0)|
            (cornerTest[0][0]<=0 && cornerTest[0][1]<=0 && cornerTest[0][2]<=0)) {
			pixBuffer[pixBufferP] = pixelStamp[0];

			PIXPRINTF("P:(%3d,%3d)\t \n",
					   (int)pixBuffer[pixBufferP].attr[0].x,
					   (int)pixBuffer[pixBufferP].attr[0].y);

			pixBufferP++;
		}

		if ((cornerTest[2][0]>=0 && cornerTest[2][1]>=0 && cornerTest[2][2]>=0)|
            (cornerTest[2][0]<=0 && cornerTest[2][1]<=0 && cornerTest[2][2]<=0)) {
			pixBuffer[pixBufferP] = pixelStamp[1];

			PIXPRINTF("P:(%3d,%3d)\t \n",
					   (int)pixBuffer[pixBufferP].attr[0].x,
					   (int)pixBuffer[pixBufferP].attr[0].y);

			pixBufferP++;
		}

		if ((cornerTest[5][0]>=0 && cornerTest[5][1]>=0 && cornerTest[5][2]>=0)|
            (cornerTest[5][0]<=0 && cornerTest[5][1]<=0 && cornerTest[5][2]<=0)) {
			pixBuffer[pixBufferP] = pixelStamp[2];

			PIXPRINTF("P:(%3d,%3d)\t \n",
					   (int)pixBuffer[pixBufferP].attr[0].x,
					   (int)pixBuffer[pixBufferP].attr[0].y);

			pixBufferP++;
		}

		if ((cornerTest[7][0]>=0 && cornerTest[7][1]>=0 && cornerTest[7][2]>=0)|
            (cornerTest[7][0]<=0 && cornerTest[7][1]<=0 && cornerTest[7][2]<=0)) {
			pixBuffer[pixBufferP] = pixelStamp[3];

			PIXPRINTF("P:(%3d,%3d)\t \n",
					   (int)pixBuffer[pixBufferP].attr[0].x,
					   (int)pixBuffer[pixBufferP].attr[0].y);
			pixBufferP++;
		}
	}
	else {
		/**
		 * c - central
		 * n - corner
		 *                                  5 6 7
		 * The hierachy can be presented as 3 c 4
		 *                                  0 1 2
		 * Zone1 = box of 012c, zone2 = 12c4, zone3 = 3c56, zone4 = c467
		 */
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

		if (area2Reciprocal>=0) {
            for(lc=0; lc<3; lc++) {
                Zone[0][lc] = (cornerTest[0][lc]>=0) | (cornerTest[1][lc]>=0) | (cornerTest[3][lc]>=0) | (centralTest[lc]>=0);
                Zone[1][lc] = (cornerTest[1][lc]>=0) | (cornerTest[2][lc]>=0) | (centralTest[lc]>=0) | (cornerTest[4][lc]>=0);
                Zone[2][lc] = (cornerTest[3][lc]>=0) | (centralTest[lc]>=0) | (cornerTest[5][lc]>=0) | (cornerTest[6][lc]>=0);
                Zone[3][lc] = (centralTest[lc]>=0) | (cornerTest[4][lc]>=0) | (cornerTest[6][lc]>=0) | (cornerTest[7][lc]>=0);
            }
        }
        else{
            for(lc=0; lc<3; lc++) {
                Zone[0][lc] = (cornerTest[0][lc]<=0) | (cornerTest[1][lc]<=0) | (cornerTest[3][lc]<=0) | (centralTest[lc]<=0);
                Zone[1][lc] = (cornerTest[1][lc]<=0) | (cornerTest[2][lc]<=0) | (centralTest[lc]<=0) | (cornerTest[4][lc]<=0);
                Zone[2][lc] = (cornerTest[3][lc]<=0) | (centralTest[lc]<=0) | (cornerTest[5][lc]<=0) | (cornerTest[6][lc]<=0);
                Zone[3][lc] = (centralTest[lc]<=0) | (cornerTest[4][lc]<=0) | (cornerTest[6][lc]<=0) | (cornerTest[7][lc]<=0);
            }
        }

		if (Zone[0][0] == true && Zone[0][1] == true && Zone[0][2] == true )    pixelSplit(x           ,y           ,level-1);
		if (Zone[1][0] == true && Zone[1][1] == true && Zone[1][2] == true )    pixelSplit(x+(1<<level),y           ,level-1);
		if (Zone[2][0] == true && Zone[2][1] == true && Zone[2][2] == true )    pixelSplit(x           ,y+(1<<level),level-1);
		if (Zone[3][0] == true && Zone[3][1] == true && Zone[3][2] == true )    pixelSplit(x+(1<<level),y+(1<<level),level-1);
	}
}

void GPU_Core::FragmentShaderEXE(int sid, void *input)
{
	sCore[sid].Init();
	sCore[sid].input = input;
	sCore[sid].Exec();
}

void GPU_Core::PerFragmentOp(pixel pixInput)
{
	bool DepthTest = true;
	int bufOffset;

	bufOffset = (int)pixInput.attr[0].y*viewPortW + (int)pixInput.attr[0].x;

    ///Depth test
    if (depthTestEnable){
        if (DepthTestMode == GL_NEVER)
            DepthTest = false;
        else if (DepthTestMode == GL_LESS)
            DepthTest = pixInput.attr[0].z  < *(dBufPtr + bufOffset);
        else if (DepthTestMode == GL_EQUAL)
            DepthTest = pixInput.attr[0].z == *(dBufPtr + bufOffset);
        else if (DepthTestMode == GL_LEQUAL)
            DepthTest = pixInput.attr[0].z <= *(dBufPtr + bufOffset);
        else if (DepthTestMode == GL_GREATER)
            DepthTest = pixInput.attr[0].z  > *(dBufPtr + bufOffset);
        else if (DepthTestMode == GL_NOTEQUAL)
            DepthTest = pixInput.attr[0].z != *(dBufPtr + bufOffset);
        else if (DepthTestMode == GL_GEQUAL)
            DepthTest = pixInput.attr[0].z >= *(dBufPtr + bufOffset);
        else if (DepthTestMode == GL_ALWAYS)
            DepthTest = true;

        if (DepthTest == false)
            return;
        else
            *(dBufPtr + bufOffset) = pixInput.attr[0].z;
    }

    ///Alpha blending
    if (blendEnable){

    }

    ///Color buffer write back
    *(cBufPtr + bufOffset*4 + 0) = pixInput.attr[1].r*255;// R
    *(cBufPtr + bufOffset*4 + 1) = pixInput.attr[1].g*255;// G
    *(cBufPtr + bufOffset*4 + 2) = pixInput.attr[1].b*255;// B
    *(cBufPtr + bufOffset*4 + 3) = pixInput.attr[1].a*255;// A
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

