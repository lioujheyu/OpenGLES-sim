/**********************************************************
//  The rendering module simulator
//  Writed by Jhe-Yu Liu
//  Email: elvis@casmail.ee.ncku.edu.tw
//
//  Basically it has four function for rendering.
//  They are <TriangleSetup>, <PixelGenerate>, <TextureMapping>,
//  and <PerfragmentOP>.
//
//
**********************************************************/
#include "rasterizer.h"

Rasterizer rm;

void Rasterizer::TriangleSetup()
{
	float constantC;

	Edge[0][0] = prim.v[0].attr[posIndx].y - prim.v[1].attr[posIndx].y;
	Edge[0][1] = prim.v[0].attr[posIndx].x - prim.v[1].attr[posIndx].x;
	Edge[1][0] = prim.v[1].attr[posIndx].y - prim.v[2].attr[posIndx].y;
	Edge[1][1] = prim.v[1].attr[posIndx].x - prim.v[2].attr[posIndx].x;
	Edge[2][0] = prim.v[2].attr[posIndx].y - prim.v[0].attr[posIndx].y;
	Edge[2][1] = prim.v[2].attr[posIndx].x - prim.v[0].attr[posIndx].x;

	constantC = Edge[0][1]*Edge[1][0] - Edge[0][0]*Edge[1][1];
	area2Reciprocal = 1/constantC;

	LY = min3(prim.v[0].attr[posIndx].y, prim.v[1].attr[posIndx].y, prim.v[2].attr[posIndx].y);
	LX = min3(prim.v[0].attr[posIndx].x, prim.v[1].attr[posIndx].x, prim.v[2].attr[posIndx].x);
	HY = max3(prim.v[0].attr[posIndx].y, prim.v[1].attr[posIndx].y, prim.v[2].attr[posIndx].y);
	RX = max3(prim.v[0].attr[posIndx].x, prim.v[1].attr[posIndx].x, prim.v[2].attr[posIndx].x);
}

void Rasterizer::PixelGenerateHiber()
{
	int x,y;

	for(y=LY; y<HY; y+=16)
		for(x=LX; x<RX; x+=16) {
			pixBufferP = 0;
#ifdef PIXEL_GENERATE_DEBUG
			fprintf(PIXEL_GENERATE_DEBUGfp,"Recursive Entry:-------(%d,%d)-----\n",x,y);
#endif
			pixelSplit(x,y,3);
		}
}

void Rasterizer::pixelSplit(int x, int y, int level)
{
	int lcX, lcY, lc;
	float centralTest[3];
	float cornerTest[8][3];
	bool Zone[4][3];
	float texUdX, texUdY, texVdX, texVdY, WdX, WdY;

	pixel pixelStamp[4];

#ifdef PIXEL_GENERATE_DEBUG
	fprintf(PIXEL_GENERATE_DEBUGfp,"-------(%d,%d),Level:%d-----\n",x,y,level);
#endif

	centralTest[0] = (x+(1<<level)-prim.v[1].attr[posIndx].x)*Edge[0][0]-
					 (y+(1<<level)-prim.v[1].attr[posIndx].y)*Edge[0][1];
	centralTest[1] = (x+(1<<level)-prim.v[2].attr[posIndx].x)*Edge[1][0]-
					 (y+(1<<level)-prim.v[2].attr[posIndx].y)*Edge[1][1];
	centralTest[2] = (x+(1<<level)-prim.v[0].attr[posIndx].x)*Edge[2][0]-
					 (y+(1<<level)-prim.v[0].attr[posIndx].y)*Edge[2][1];

	if (level == 0) {
		/*m
		 * pixel stamp: 2 3
		 *              0 1
		 */
		pixBufferP = 0;

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
		pixelStamp[0].baryCenPos3[2] = cornerTest[0][1]*area2Reciprocal;
		pixelStamp[0].attr[0].z = prim.v[0].attr[posIndx].z +
                               pixelStamp[0].baryCenPos3[0]*(prim.v[1].attr[posIndx].z - prim.v[0].attr[posIndx].z) +
                               pixelStamp[0].baryCenPos3[1]*(prim.v[2].attr[posIndx].z - prim.v[0].attr[posIndx].z);
		pixelStamp[0].attr[0].w = prim.v[0].attr[posIndx].w +
                               pixelStamp[0].baryCenPos3[0]*(prim.v[1].attr[posIndx].w - prim.v[0].attr[posIndx].w) +
                               pixelStamp[0].baryCenPos3[1]*(prim.v[2].attr[posIndx].w - prim.v[0].attr[posIndx].w);
        for (int attrCnt=1;attrCnt<MAX_ATTRIBUTE_NUMBER;attrCnt++){
            if (!attrEnable[attrCnt])
                continue;
            pixelStamp[0].attr[attrCnt].s = prim.v[0].attr[attrCnt].s +
                                            pixelStamp[0].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].s - prim.v[0].attr[attrCnt+1].s) +
                                            pixelStamp[0].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].s - prim.v[0].attr[attrCnt+1].s);
            pixelStamp[0].attr[attrCnt].t = prim.v[0].attr[attrCnt].t +
                                            pixelStamp[0].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].t - prim.v[0].attr[attrCnt+1].t) +
                                            pixelStamp[0].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].t - prim.v[0].attr[attrCnt+1].t);
            pixelStamp[0].attr[attrCnt].p = prim.v[0].attr[attrCnt].p +
                                            pixelStamp[0].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].p - prim.v[0].attr[attrCnt+1].s) +
                                            pixelStamp[0].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].p - prim.v[0].attr[attrCnt+1].s);
            pixelStamp[0].attr[attrCnt].q = prim.v[0].attr[attrCnt].q +
                                            pixelStamp[0].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].q - prim.v[0].attr[attrCnt+1].q) +
                                            pixelStamp[0].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].q - prim.v[0].attr[attrCnt+1].q);
        }

		pixelStamp[1].attr[0].x = x+1;
		pixelStamp[1].attr[0].y = y;
		pixelStamp[1].baryCenPos3[0] = cornerTest[0][2]*area2Reciprocal;
		pixelStamp[1].baryCenPos3[1] = cornerTest[0][0]*area2Reciprocal;
		pixelStamp[1].baryCenPos3[2] = cornerTest[0][1]*area2Reciprocal;
		pixelStamp[1].attr[0].z = prim.v[0].attr[posIndx].z +
                               pixelStamp[1].baryCenPos3[0]*(prim.v[1].attr[posIndx].z - prim.v[0].attr[posIndx].z) +
                               pixelStamp[1].baryCenPos3[1]*(prim.v[2].attr[posIndx].z - prim.v[0].attr[posIndx].z);
		pixelStamp[1].attr[0].w = prim.v[0].attr[posIndx].w +
                               pixelStamp[1].baryCenPos3[0]*(prim.v[1].attr[posIndx].w - prim.v[0].attr[posIndx].w) +
                               pixelStamp[1].baryCenPos3[1]*(prim.v[2].attr[posIndx].w - prim.v[0].attr[posIndx].w);
        for (int attrCnt=1;attrCnt<MAX_ATTRIBUTE_NUMBER;attrCnt++){
            if (!attrEnable[attrCnt])
                continue;
            pixelStamp[1].attr[attrCnt].s = prim.v[0].attr[attrCnt].s +
                                            pixelStamp[1].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].s - prim.v[0].attr[attrCnt+1].s) +
                                            pixelStamp[1].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].s - prim.v[0].attr[attrCnt+1].s);
            pixelStamp[1].attr[attrCnt].t = prim.v[0].attr[attrCnt].t +
                                            pixelStamp[1].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].t - prim.v[0].attr[attrCnt+1].t) +
                                            pixelStamp[1].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].t - prim.v[0].attr[attrCnt+1].t);
            pixelStamp[1].attr[attrCnt].p = prim.v[0].attr[attrCnt].p +
                                            pixelStamp[1].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].p - prim.v[0].attr[attrCnt+1].s) +
                                            pixelStamp[1].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].p - prim.v[0].attr[attrCnt+1].s);
            pixelStamp[1].attr[attrCnt].q = prim.v[0].attr[attrCnt].q +
                                            pixelStamp[1].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].q - prim.v[0].attr[attrCnt+1].q) +
                                            pixelStamp[1].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].q - prim.v[0].attr[attrCnt+1].q);
        }

		pixelStamp[2].attr[0].x = x;
		pixelStamp[2].attr[0].y = y+1;
		pixelStamp[2].baryCenPos3[0] = cornerTest[0][2]*area2Reciprocal;
		pixelStamp[2].baryCenPos3[1] = cornerTest[0][0]*area2Reciprocal;
		pixelStamp[2].baryCenPos3[2] = cornerTest[0][1]*area2Reciprocal;
		pixelStamp[2].attr[0].z = prim.v[0].attr[posIndx].z +
                               pixelStamp[2].baryCenPos3[0]*(prim.v[1].attr[posIndx].z - prim.v[0].attr[posIndx].z) +
                               pixelStamp[2].baryCenPos3[1]*(prim.v[2].attr[posIndx].z - prim.v[0].attr[posIndx].z);
		pixelStamp[2].attr[0].w = prim.v[0].attr[posIndx].w +
                               pixelStamp[2].baryCenPos3[0]*(prim.v[1].attr[posIndx].w - prim.v[0].attr[posIndx].w) +
                               pixelStamp[2].baryCenPos3[1]*(prim.v[2].attr[posIndx].w - prim.v[0].attr[posIndx].w);
        for (int attrCnt=1;attrCnt<MAX_ATTRIBUTE_NUMBER;attrCnt++){
            if (!attrEnable[attrCnt])
                continue;
            pixelStamp[2].attr[attrCnt].s = prim.v[0].attr[attrCnt].s +
                                            pixelStamp[2].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].s - prim.v[0].attr[attrCnt+1].s) +
                                            pixelStamp[2].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].s - prim.v[0].attr[attrCnt+1].s);
            pixelStamp[2].attr[attrCnt].t = prim.v[0].attr[attrCnt].t +
                                            pixelStamp[2].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].t - prim.v[0].attr[attrCnt+1].t) +
                                            pixelStamp[2].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].t - prim.v[0].attr[attrCnt+1].t);
            pixelStamp[2].attr[attrCnt].p = prim.v[0].attr[attrCnt].p +
                                            pixelStamp[2].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].p - prim.v[0].attr[attrCnt+1].s) +
                                            pixelStamp[2].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].p - prim.v[0].attr[attrCnt+1].s);
            pixelStamp[2].attr[attrCnt].q = prim.v[0].attr[attrCnt].q +
                                            pixelStamp[2].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].q - prim.v[0].attr[attrCnt+1].q) +
                                            pixelStamp[2].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].q - prim.v[0].attr[attrCnt+1].q);
        }

		pixelStamp[3].attr[0].x = x+1;
		pixelStamp[3].attr[0].y = y+1;
		pixelStamp[3].baryCenPos3[0] = cornerTest[0][2]*area2Reciprocal;
		pixelStamp[3].baryCenPos3[1] = cornerTest[0][0]*area2Reciprocal;
		pixelStamp[3].baryCenPos3[2] = cornerTest[0][1]*area2Reciprocal;
		pixelStamp[3].attr[0].z = prim.v[0].attr[posIndx].z +
                               pixelStamp[3].baryCenPos3[0]*(prim.v[1].attr[posIndx].z - prim.v[0].attr[posIndx].z) +
                               pixelStamp[3].baryCenPos3[1]*(prim.v[2].attr[posIndx].z - prim.v[0].attr[posIndx].z);
		pixelStamp[3].attr[0].w = prim.v[0].attr[posIndx].w +
                               pixelStamp[3].baryCenPos3[0]*(prim.v[1].attr[posIndx].w - prim.v[0].attr[posIndx].w) +
                               pixelStamp[3].baryCenPos3[1]*(prim.v[2].attr[posIndx].w - prim.v[0].attr[posIndx].w);
        for (int attrCnt=1;attrCnt<MAX_ATTRIBUTE_NUMBER;attrCnt++){
            if (!attrEnable[attrCnt])
                continue;
            pixelStamp[3].attr[attrCnt].s = prim.v[0].attr[attrCnt].s +
                                            pixelStamp[3].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].s - prim.v[0].attr[attrCnt+1].s) +
                                            pixelStamp[3].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].s - prim.v[0].attr[attrCnt+1].s);
            pixelStamp[3].attr[attrCnt].t = prim.v[0].attr[attrCnt].t +
                                            pixelStamp[3].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].t - prim.v[0].attr[attrCnt+1].t) +
                                            pixelStamp[3].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].t - prim.v[0].attr[attrCnt+1].t);
            pixelStamp[3].attr[attrCnt].p = prim.v[0].attr[attrCnt].p +
                                            pixelStamp[3].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].p - prim.v[0].attr[attrCnt+1].s) +
                                            pixelStamp[3].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].p - prim.v[0].attr[attrCnt+1].s);
            pixelStamp[3].attr[attrCnt].q = prim.v[0].attr[attrCnt].q +
                                            pixelStamp[3].baryCenPos3[0]*(prim.v[1].attr[attrCnt+1].q - prim.v[0].attr[attrCnt+1].q) +
                                            pixelStamp[3].baryCenPos3[1]*(prim.v[2].attr[attrCnt+1].q - prim.v[0].attr[attrCnt+1].q);
        }

		if ((cornerTest[0][0]>=0 && cornerTest[0][1]>=0 && cornerTest[0][2]>=0)|
            (cornerTest[0][0]<=0 && cornerTest[0][1]<=0 && cornerTest[0][2]<=0)) {
			pixBuffer[pixBufferP] = pixelStamp[0];
#ifdef PIXEL_GENERATE_DEBUG
			fprintf(PIXEL_GENERATE_DEBUGfp,"P:(%3d,%3d) \n",
					(int)pixBuffer[pixBufferP].attr[0].x,(int)pixBuffer[pixBufferP].attr[0].y);
#endif
			pixBufferP++;
		}

		if ((cornerTest[2][0]>=0 && cornerTest[2][1]>=0 && cornerTest[2][2]>=0)|
            (cornerTest[2][0]<=0 && cornerTest[2][1]<=0 && cornerTest[2][2]<=0)) {
			pixBuffer[pixBufferP] = pixelStamp[1];
#ifdef PIXEL_GENERATE_DEBUG
			fprintf(PIXEL_GENERATE_DEBUGfp,"P:(%3d,%3d) \n",
					(int)pixBuffer[pixBufferP].attr[0].x,(int)pixBuffer[pixBufferP].attr[0].y);
#endif
			pixBufferP++;
		}

		if ((cornerTest[5][0]>=0 && cornerTest[5][1]>=0 && cornerTest[5][2]>=0)|
            (cornerTest[5][0]<=0 && cornerTest[5][1]<=0 && cornerTest[5][2]<=0)) {
			pixBuffer[pixBufferP] = pixelStamp[2];
#ifdef PIXEL_GENERATE_DEBUG
			fprintf(PIXEL_GENERATE_DEBUGfp,"P:(%3d,%3d) \n",
					(int)pixBuffer[pixBufferP].attr[0].x,(int)pixBuffer[pixBufferP].attr[0].y);
#endif
			pixBufferP++;
		}

		if ((cornerTest[7][0]>=0 && cornerTest[7][1]>=0 && cornerTest[7][2]>=0)|
            (cornerTest[7][0]<=0 && cornerTest[7][1]<=0 && cornerTest[7][2]<=0)) {
			pixBuffer[pixBufferP] = pixelStamp[3];
#ifdef PIXEL_GENERATE_DEBUG
			fprintf(PIXEL_GENERATE_DEBUGfp,"P:(%3d,%3d) \n",
					(int)pixBuffer[pixBufferP].attr[0].x,(int)pixBuffer[pixBufferP].attr[0].y);
#endif
			pixBufferP++;
		}

		PerFragmentOp();
	} else {
		/*
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
                Zone[0][lc] = cornerTest[0][lc]>=0 | cornerTest[1][lc]>=0 | cornerTest[3][lc]>=0 | centralTest[lc]>=0;
                Zone[1][lc] = cornerTest[1][lc]>=0 | cornerTest[2][lc]>=0 | centralTest[lc]>=0 | cornerTest[4][lc]>=0;
                Zone[2][lc] = cornerTest[3][lc]>=0 | centralTest[lc]>=0 | cornerTest[5][lc]>=0 | cornerTest[6][lc]>=0;
                Zone[3][lc] = centralTest[lc]>=0 | cornerTest[4][lc]>=0 | cornerTest[6][lc]>=0 | cornerTest[7][lc]>=0;
            }
        }
        else{
            for(lc=0; lc<3; lc++) {
                Zone[0][lc] = cornerTest[0][lc]<=0 | cornerTest[1][lc]<=0 | cornerTest[3][lc]<=0 | centralTest[lc]<=0;
                Zone[1][lc] = cornerTest[1][lc]<=0 | cornerTest[2][lc]<=0 | centralTest[lc]<=0 | cornerTest[4][lc]<=0;
                Zone[2][lc] = cornerTest[3][lc]<=0 | centralTest[lc]<=0 | cornerTest[5][lc]<=0 | cornerTest[6][lc]<=0;
                Zone[3][lc] = centralTest[lc]<=0 | cornerTest[4][lc]<=0 | cornerTest[6][lc]<=0 | cornerTest[7][lc]<=0;
            }
        }

		if (Zone[0][0] == true && Zone[0][1] == true && Zone[0][2] == true )    pixelSplit(x           ,y           ,level-1);
		if (Zone[1][0] == true && Zone[1][1] == true && Zone[1][2] == true )    pixelSplit(x+(1<<level),y           ,level-1);
		if (Zone[2][0] == true && Zone[2][1] == true && Zone[2][2] == true )    pixelSplit(x           ,y+(1<<level),level-1);
		if (Zone[3][0] == true && Zone[3][1] == true && Zone[3][2] == true )    pixelSplit(x+(1<<level),y+(1<<level),level-1);
	}
}

void Rasterizer::PerFragmentOp()
{
	int i;
	bool AlphaTest = true;
	bool DepthTest = true;
	for (i = 0; i < pixBufferP; i++) {
		///**********Fog**********************
		if (FogEn) {

		}

		///**********Alpha Test*****************
		if (AlphaTestMode == GL_NEVER)
			AlphaTest = false;
		else if (AlphaTestMode == GL_LESS)
			AlphaTest = pixBuffer[i].attr[colIndx].a < AlphaRef;
		else if (AlphaTestMode == GL_EQUAL)
			AlphaTest = pixBuffer[i].attr[colIndx].a == AlphaRef;
		else if (AlphaTestMode == GL_LEQUAL)
			AlphaTest = pixBuffer[i].attr[colIndx].a <= AlphaRef;
		else if (AlphaTestMode == GL_GREATER)
			AlphaTest = pixBuffer[i].attr[colIndx].a > AlphaRef;
		else if (AlphaTestMode == GL_NOTEQUAL)
			AlphaTest = pixBuffer[i].attr[colIndx].a != AlphaRef;
		else if (AlphaTestMode == GL_GEQUAL)
			AlphaTest = pixBuffer[i].attr[colIndx].a >= AlphaRef;
		else if (AlphaTestMode == GL_ALWAYS)
			AlphaTest = true;
		else
			fprintf(stderr,"Wrong Alpha Test mode!!\n");
		if (AlphaTest == false)
			continue;

		///****************Depth test*********************
		if (DepthTestMode == GL_NEVER)
			DepthTest = false;
		else if (DepthTestMode == GL_LESS)
			DepthTest = pixBuffer[i].attr[0].z  < DepthBuffer[(int)pixBuffer[i].attr[0].y][(int)pixBuffer[i].attr[0].x];
		else if (DepthTestMode == GL_EQUAL)
			DepthTest = pixBuffer[i].attr[0].z == DepthBuffer[(int)pixBuffer[i].attr[0].y][(int)pixBuffer[i].attr[0].x];
		else if (DepthTestMode == GL_LEQUAL)
			DepthTest = pixBuffer[i].attr[0].z <= DepthBuffer[(int)pixBuffer[i].attr[0].y][(int)pixBuffer[i].attr[0].x];
		else if (DepthTestMode == GL_GREATER)
			DepthTest = pixBuffer[i].attr[0].z  > DepthBuffer[(int)pixBuffer[i].attr[0].y][(int)pixBuffer[i].attr[0].x];
		else if (DepthTestMode == GL_NOTEQUAL)
			DepthTest = pixBuffer[i].attr[0].z != DepthBuffer[(int)pixBuffer[i].attr[0].y][(int)pixBuffer[i].attr[0].x];
		else if (DepthTestMode == GL_GEQUAL)
			DepthTest = pixBuffer[i].attr[0].z >= DepthBuffer[(int)pixBuffer[i].attr[0].y][(int)pixBuffer[i].attr[0].x];
		else if (DepthTestMode == GL_ALWAYS)
			DepthTest = true;
		else
			fprintf(stderr,"Wrong Depth Test mode!!\n");
		if (DepthTest == false)
			continue;
		else
			DepthBuffer[(int)pixBuffer[i].attr[0].y][(int)pixBuffer[i].attr[0].x] = pixBuffer[i].attr[0].z;

		//Alpha blending

		ColorBuffer[(int)pixBuffer[i].attr[0].y][(int)pixBuffer[i].attr[0].x][0]
			= (int)pixBuffer[i].attr[colIndx].r;// R
		ColorBuffer[(int)pixBuffer[i].attr[0].y][(int)pixBuffer[i].attr[0].x][1]
			= (int)pixBuffer[i].attr[colIndx].g;// G
		ColorBuffer[(int)pixBuffer[i].attr[0].y][(int)pixBuffer[i].attr[0].x][2]
			= (int)pixBuffer[i].attr[colIndx].b;// B
	}
}

Rasterizer::Rasterizer()
{
	int i,j;

	for (j = 0; j < 512; j++)
		for (i = 0; i < 1024; i++) {
			ColorBuffer[j][i][0] = 0;
			ColorBuffer[j][i][1] = 0;
			ColorBuffer[j][i][2] = 0;
			ColorBuffer[j][i][3] = 0;
			DepthBuffer[j][i] = 255;
		}

	for (i = 0; i < 4; i++) {
		FogColor[i] = 0;
		ColorClearVal[i] = 0;
	}

	AlphaRef = 0;
	DepthRef = 255;

	TexMinFilterMode = GL_NEAREST;
	TexMaxFilterMode = GL_NEAREST;
	TexWrapModeS = GL_REPEAT;
	TexWrapModeT = GL_REPEAT;
	AlphaTestMode = GL_ALWAYS;
	DepthTestMode = GL_LESS;
	TexMappingEn = false;
	AlphaBlendingEn = false;
	FogEn = false;

	posIndx = 0;
	colIndx = 1;

#ifdef TEXDEBUG
	TEXDEBUGfp = fopen("Result/TexDebug.txt","w");
#endif

#ifdef PIXEL_GENERATE_DEBUG
	PIXEL_GENERATE_DEBUGfp = fopen("Result/PixelGenerateDebug.txt","w");
#endif
}

//this bmp format doesn't include compression method and palette
void Rasterizer::DumpImage()
{
	FILE *CLRfp;
	CLRfp = fopen("Result/colormap.bmp","wb");

	int x,y,i;

	for (i=0; i<54; i++) {
		switch (i) {
		default:
			putc (0x00, CLRfp);
			break;
		case 0:
			putc (0x42, CLRfp);
			break;
		case 1:
			putc (0x4D, CLRfp);
			break;
		case 2:
			putc (0x38, CLRfp);
			break;
		case 3:
			putc (0x10, CLRfp);
			break;
		case 0xA:
			putc (0x36, CLRfp);
			break;
		case 0xE:
			putc (0x28, CLRfp);
			break;
		case 0x12:
			putc (1024&0x000000FF, CLRfp);
			break;
		case 0x13:
			putc ((1024>>8)&0x000000FF, CLRfp);
			break;
		case 0x14:
			putc ((1024>>16)&0x000000FF, CLRfp);
			break;
		case 0x15:
			putc ((1024>>24)&0x000000FF, CLRfp);
			break;
		case 0x16:
			putc (512&0x000000FF, CLRfp);
			break;
		case 0x17:
			putc ((512>>8)&0x000000FF, CLRfp);
			break;
		case 0x18:
			putc ((512>>16)&0x000000FF, CLRfp);
			break;
		case 0x19:
			putc ((512>>24)&0x000000FF, CLRfp);
			break;
		case 0x1A:
			putc (0x01, CLRfp);
			break;
		case 0x1C:
			putc (0x18, CLRfp);
			break;
		case 0x26:
			putc (0x12, CLRfp);
			break;
		case 0x27:
			putc (0x0B, CLRfp);
			break;
		case 0x2A:
			putc (0x12, CLRfp);
			break;
		case 0x2B:
			putc (0x0B, CLRfp);
			break;
		}
	}

	for (y=0; y<512; y++)
		for (x=0; x<1024; x++) {
			putc((int)ColorBuffer[y][x][2], CLRfp);// B
			putc((int)ColorBuffer[y][x][1], CLRfp);// G
			putc((int)ColorBuffer[y][x][0], CLRfp);// R
		}

	fclose(CLRfp);
}

