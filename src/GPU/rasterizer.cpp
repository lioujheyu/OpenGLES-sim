/**********************************************************
//  The rendering module simulator
//  Writed by Liou Jhe-Yu
//  Email: lioujheyu@gmail.com
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

	LY = MIN3(prim.v[0].attr[posIndx].y, prim.v[1].attr[posIndx].y, prim.v[2].attr[posIndx].y);
	LX = MIN3(prim.v[0].attr[posIndx].x, prim.v[1].attr[posIndx].x, prim.v[2].attr[posIndx].x);
	HY = MAX3(prim.v[0].attr[posIndx].y, prim.v[1].attr[posIndx].y, prim.v[2].attr[posIndx].y);
	RX = MAX3(prim.v[0].attr[posIndx].x, prim.v[1].attr[posIndx].x, prim.v[2].attr[posIndx].x);
}

void Rasterizer::PixelGenerateHiber()
{
	int x,y;

	for(y=LY; y<HY; y+=16)
		for(x=LX; x<RX; x+=16) {
			pixBufferP = 0;

			PIXPRINTF("Recursive Entry:-------(%d,%d)-----\n",x,y);

			pixelSplit(x,y,3);
		}
}

void Rasterizer::pixelSplit(int x, int y, int level)
{
	int lc;
	float centralTest[3];
	float cornerTest[8][3];
	bool Zone[4][3];

	pixel pixelStamp[4];


	PIXPRINTF("-------(%d,%d),Level:%d-----\n",x,y,level);
	TEXPRINTF("XXXX-YYYY-UUUU.UU-VVVV.VV----------------\n");

	centralTest[0] = (x+(1<<level)-prim.v[1].attr[posIndx].x)*Edge[0][0]-
					 (y+(1<<level)-prim.v[1].attr[posIndx].y)*Edge[0][1];
	centralTest[1] = (x+(1<<level)-prim.v[2].attr[posIndx].x)*Edge[1][0]-
					 (y+(1<<level)-prim.v[2].attr[posIndx].y)*Edge[1][1];
	centralTest[2] = (x+(1<<level)-prim.v[0].attr[posIndx].x)*Edge[2][0]-
					 (y+(1<<level)-prim.v[0].attr[posIndx].y)*Edge[2][1];

	if (level == 0) {
		/**
		 * pixel stamp: 2 3
		 *              0 1
		 * We need to calculating 4 pixels in quad concurrently nomatter if
		 * they are both falling into a triangle or not for scale factor calculation
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
			pixelStamp[i].attr[0].z = prim.v[0].attr[posIndx].z +
								pixelStamp[i].baryCenPos3[0]*(prim.v[1].attr[posIndx].z - prim.v[0].attr[posIndx].z) +
								pixelStamp[i].baryCenPos3[1]*(prim.v[2].attr[posIndx].z - prim.v[0].attr[posIndx].z);
			pixelStamp[i].attr[0].w = prim.v[0].attr[posIndx].w +
								pixelStamp[i].baryCenPos3[0]*(prim.v[1].attr[posIndx].w - prim.v[0].attr[posIndx].w) +
								pixelStamp[i].baryCenPos3[1]*(prim.v[2].attr[posIndx].w - prim.v[0].attr[posIndx].w);

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
		for (int attrCnt=1;attrCnt<MAX_ATTRIBUTE_NUMBER;attrCnt++){
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

		for (int i = 0; i < pixBufferP; i++) {
			//std::thread s1(&Rasterizer::ShaderEXE, pixBuffer[i], std::ref(pixBuffer[i]));
			//s1.join();
			pixBuffer[i] = ShaderEXE(pixBuffer[i]);
			PerFragmentOp(pixBuffer[i]);
//			if ((i+1)<pixBufferP) {
//				i++;
//				std::thread s2(ShaderEXE, pixBuffer[i], std::ref(pixBuffer[i]));
//				PerFragmentOp(pixBuffer[i]);
//			}
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

/**
 * u,v - Texture coodinate in 2 dimension directions.
 * s,b,o - 3 block-based hirachy level, Super block, Block, Offset, in textrue
 * coordinate.
 *
 * The following two function are to calculate 1D address and fetch data in
 * system memory from 6D block-based texture address.
 */
int Rasterizer::CalcTexAdd(short int us,
                           short int ub,
                           short int uo,
                           short int vs,
                           short int vb,
                           short int vo,
                           int width)
{
	return (vs*TEX_CACHE_BLOCK_SIZE_ROOT*TEX_CACHE_ENTRY_SIZE_ROOT
			+ vb*TEX_CACHE_BLOCK_SIZE_ROOT
			+ vo ) * width
			+ us*TEX_CACHE_BLOCK_SIZE_ROOT*TEX_CACHE_ENTRY_SIZE_ROOT
			+ ub*TEX_CACHE_BLOCK_SIZE_ROOT
			+ uo;
}

fixColor4 Rasterizer::GetTexColor(floatVec4 coordIn, const unsigned int level, unsigned char tid)
{
	int i,j;
	unsigned short u, v;
	unsigned short tag, entry, offset, U_Block, V_Block, U_Offset, V_Offset, U_Super, V_Super;
	unsigned char *texTmpPtr = NULL;
	bool isColdMiss = false;
	unsigned char tWay = 0;
	unsigned char LRUbiggest = 0;

	u = (unsigned short)coordIn.s;
	v = (unsigned short)coordIn.t;

#ifdef SHOW_MIPMAP_LEVEL
	fixColor4 mipmaplevel;
	mipmaplevel = fixColor4(255-level*30, 255-level*30, 255-level*30, 255);
	return mipmaplevel;
#endif //SHOW_MIPMAP_LEVEL

	U_Super = u >> (TEX_CACHE_BLOCK_SIZE_ROOT_LOG + TEX_CACHE_ENTRY_SIZE_ROOT_LOG);
	V_Super = v >> (TEX_CACHE_BLOCK_SIZE_ROOT_LOG + TEX_CACHE_ENTRY_SIZE_ROOT_LOG);
	U_Block = u >> (TEX_CACHE_BLOCK_SIZE_ROOT_LOG) & (TEX_CACHE_ENTRY_SIZE_ROOT - 1);
	V_Block = v >> (TEX_CACHE_BLOCK_SIZE_ROOT_LOG) & (TEX_CACHE_ENTRY_SIZE_ROOT - 1);
	U_Offset = u & (TEX_CACHE_BLOCK_SIZE_ROOT - 1);
	V_Offset = v & (TEX_CACHE_BLOCK_SIZE_ROOT - 1);
	tag = (int)( (V_Super << 8) | (U_Super&0x00ff) );

	///@note (elvis#1#): Simply append level and texture_id after tag bit
	tag = (tag << 4) | (level&0xf);
	tag = (tag << 1) | (tid&0x1);

	entry = V_Block * TEX_CACHE_ENTRY_SIZE_ROOT + U_Block;
	offset = V_Offset * TEX_CACHE_BLOCK_SIZE_ROOT + U_Offset;

	for (i=0; i<TEX_WAY_ASSOCIATION; i++) {
		if (TexCache.valid[entry][i] == true) {
			if (TexCache.tag[entry][i] == tag) {
			///*************** Texture cache hit *************
				TexCache.hit++;
				TexCache.LRU[entry][i] = 0;

				return TexCache.color[entry][offset][i];
			}
		}
		else
			isColdMiss = true;
	}

	///*********** Texture cache miss ****************
	TexCache.miss++;

	for (i=0; i<TEX_WAY_ASSOCIATION; i++) {
		if (LRUbiggest < TexCache.LRU[entry][i]) {
			LRUbiggest = TexCache.LRU[entry][i];
			tWay = i;
		}
		TexCache.LRU[entry][i]++;
	}

	if (TexCache.valid[entry][tWay] == false)
		TexCache.valid[entry][tWay] = true;
	TexCache.LRU[entry][tWay] = 0;
	TexCache.tag[entry][tWay] = tag;

	for (j=0; j<TEX_CACHE_BLOCK_SIZE_ROOT; j++) {
		for (i=0; i<TEX_CACHE_BLOCK_SIZE_ROOT; i++) {
			texTmpPtr = texImage[tid].data[level] +
						CalcTexAdd(U_Super,U_Block,i,
								   V_Super,V_Block,j,
								   texImage[tid].widthLevel[level]) * 4;

			TexCache.color[entry][j*TEX_CACHE_BLOCK_SIZE_ROOT+i][tWay].r = *texTmpPtr++;
			TexCache.color[entry][j*TEX_CACHE_BLOCK_SIZE_ROOT+i][tWay].g = *texTmpPtr++;
			TexCache.color[entry][j*TEX_CACHE_BLOCK_SIZE_ROOT+i][tWay].b = *texTmpPtr++;
			TexCache.color[entry][j*TEX_CACHE_BLOCK_SIZE_ROOT+i][tWay].a = *texTmpPtr++;
		}
	}
#ifdef SHOW_TEXCACHE_COLD_MISS
	if (isColdMiss)
		return fixColor4(255,0,0,255);
#endif //SHOW_TEXCACHE_COLD_MISS

#ifdef SHOW_TEXCACHE_MISS
	return fixColor4(0,255,0,255);
#endif //SHOW_TEXCACHE_MISS

	return TexCache.color[entry][offset][tWay];
}

floatVec4 Rasterizer::TexCoordWrap(floatVec4 coordIn, unsigned int level, unsigned char tid)
{
	floatVec4 temp;

	switch (wrapS[tid]){
	case GL_REPEAT:
		temp.s = fmod(coordIn.s,texImage[tid].widthLevel[level]);
		break;
	case GL_CLAMP_TO_EDGE:
		temp.s = std::min(coordIn.s, (float)texImage[tid].widthLevel[level]-1);
		break;
	default:
		//DPRINTF(stderr,"Wrong Texture Wrap mode in x-axis!!\n");
		break;
	}

	switch (wrapT[tid]){
	case GL_REPEAT:
		temp.t = fmod(coordIn.t,texImage[tid].heightLevel[level]);
		break;
	case GL_CLAMP_TO_EDGE:
		temp.t = std::min(coordIn.t, (float)texImage[tid].heightLevel[level]-1);
		break;
	default:
		//DPRINTF(stderr,"Wrong Texture Wrap mode in y-axis!!\n");
		break;
	}

	return temp;
}

fixColor4 Rasterizer::BilinearFilter(floatVec4 coordIn,int level, unsigned char tid)
{
	/// coord[4]: 2 3
	///			  0 1
	floatVec4 coordLOD[4];

	unsigned short texUC, texVC;
	float u_ratio, v_ratio;
	fixColor4 color;
	fixColor4 TexColor[4];

	coordLOD[0].s = coordIn.s / (1<<level);
	coordLOD[0].s = std::max(coordLOD[0].s - 0.5, 0.0);
	coordLOD[0].t = coordIn.t / (1<<level);
	coordLOD[0].t = std::max(coordLOD[0].t - 0.5, 0.0);

	coordLOD[1] =  coordLOD[2] = coordLOD[3] = coordLOD[0];
	coordLOD[1].s = coordLOD[1].s + 1;
	coordLOD[2].t = coordLOD[2].t + 1;
	coordLOD[3].s = coordLOD[3].s + 1;
	coordLOD[3].t = coordLOD[3].t + 1;
	coordLOD[0] = TexCoordWrap(coordLOD[0], level, tid);
	coordLOD[1] = TexCoordWrap(coordLOD[1], level, tid);
	coordLOD[2] = TexCoordWrap(coordLOD[2], level, tid);
	coordLOD[3] = TexCoordWrap(coordLOD[3], level, tid);


	TexColor[0] = GetTexColor(coordLOD[0], level, tid);
	TexColor[1] = GetTexColor(coordLOD[1], level, tid);
	TexColor[2] = GetTexColor(coordLOD[2], level, tid);
	TexColor[3] = GetTexColor(coordLOD[3], level, tid);

	texUC = (unsigned short)floor(coordLOD[0].s);
	texVC = (unsigned short)floor(coordLOD[0].t);
	u_ratio = coordLOD[0].s - texUC;
	v_ratio = coordLOD[0].t - texVC;

	color = (TexColor[0]*(1-u_ratio) + TexColor[1]*u_ratio)*(1-v_ratio) +
			(TexColor[2]*(1-u_ratio) + TexColor[3]*u_ratio)*v_ratio;

	return color;
}

fixColor4 Rasterizer::TrilinearFilter(floatVec4 coordIn, int level, float w_ratio, unsigned char tid)
{
	fixColor4 color[2];
	int maxLevel = texImage[tid].maxLevel;
	color[0] = BilinearFilter(coordIn, level, tid);
	color[1] = BilinearFilter(coordIn, ((level+1)<maxLevel)?level+1:maxLevel, tid);

	color[0] = color[0]*(1-w_ratio) + color[1]*w_ratio;

	return color[0];
}

fixColor4 Rasterizer::TextureMapping(floatVec4 coordIn, int attrIndx, pixel pixelInput, unsigned char tid)
{
	floatVec4 coord;
	float w_ratio;
	float maxScaleFac;
	fixColor4 TexColor[2];
	fixColor4 color, colorNextLevel;
	int LoD, maxLevel;

	//find absolutely coord in texture image
	coord.s = coordIn.s*texImage[tid].widthLevel[0];
	coord.t = coordIn.t*texImage[tid].heightLevel[0];
	coord.p = coordIn.p;
	coord.q = coordIn.q;

	maxScaleFac = std::max(
					std::max(pixelInput.scaleFacDX[attrIndx].s*texImage[tid].widthLevel[0],
							 pixelInput.scaleFacDX[attrIndx].t*texImage[tid].heightLevel[0]),
					std::max(pixelInput.scaleFacDY[attrIndx].s*texImage[tid].widthLevel[0],
							 pixelInput.scaleFacDY[attrIndx].t*texImage[tid].heightLevel[0])
				);

	w_ratio = frexp(maxScaleFac, &LoD);
	w_ratio = w_ratio*2-1;
	LoD--;

	maxLevel = texImage[tid].maxLevel;

	///Prevent LoD exceeds the maximum allowable level.
    LoD = std::min(LoD, maxLevel);

	if(maxScaleFac>1) {
		switch (minFilter[tid]) {
		case GL_NEAREST:    //u,v nearest filter
			coord = TexCoordWrap(coord, 0, tid);
			color = GetTexColor(coord, 0, tid);
			break;

		case GL_LINEAR:     //u,v bilinear filter
			color = BilinearFilter(coord, 0, tid);
			break;

		case GL_NEAREST_MIPMAP_NEAREST: //u,v,w nearest filter
			coord = TexCoordWrap(coord, 0, tid);
			coord.s = coord.s / (1<<LoD);
			coord.t = coord.t / (1<<LoD);
			color = GetTexColor(coord, LoD, tid);
			break;

		case GL_LINEAR_MIPMAP_NEAREST:  //u,v bilinear, w nearest filter
			color = BilinearFilter(coord, LoD, tid);
			break;

		case GL_NEAREST_MIPMAP_LINEAR:  //u,v nearest, w linear filter
			coord = TexCoordWrap(coord, 0, tid);
			coord.s = coord.s / (1<<LoD);
			coord.t = coord.t / (1<<LoD);
			TexColor[0] = GetTexColor(coord, LoD, tid);

			if (LoD+1 < maxLevel) {
				coord.s = coord.s / 2;
				coord.t = coord.t / 2;
				TexColor[1] = GetTexColor(coord, LoD, tid);
				color = TexColor[0]*(1-w_ratio) + TexColor[1]*w_ratio;
			}
			else
				color = TexColor[0];
			break;

		case GL_LINEAR_MIPMAP_LINEAR:   //u,v,w trilinear filter
			color = TrilinearFilter(coord, LoD, w_ratio, tid);
			break;

//		case GL_ANISOTROPIC:
//			float r1,r2,r3,r4;
//
//			r1 = sqrt(pixBuffer[i].scaleFactorDuDx[0]*pixBuffer[i].scaleFactorDuDx[0]+pixBuffer[i].scaleFactorDvDx[0]*pixBuffer[i].scaleFactorDvDx[0]);
//			r2 = sqrt(pixBuffer[i].scaleFactorDuDy[0]*pixBuffer[i].scaleFactorDuDy[0]+pixBuffer[i].scaleFactorDvDy[0]*pixBuffer[i].scaleFactorDvDy[0]);
//
//			r3 = max(r1,r2);
//			r4 = min(r1,r2);
//			if ((r3/r4) > 2.0f) {
//				LoD = (LoD - 1)>0?LoD - 1:0;
//
//				color = TrilinearFilter(fabs(TexU-(pixBuffer[i].scaleFactorDuDx[0]+pixBuffer[i].scaleFactorDuDy[0])/2),
//										fabs(TexV-(pixBuffer[i].scaleFactorDvDx[0]+pixBuffer[i].scaleFactorDvDy[0])/2),LoD,w_ratio);
//				colorNextLevel = TrilinearFilter(fabs(TexU+(pixBuffer[i].scaleFactorDuDx[0]+pixBuffer[i].scaleFactorDuDy[0])/2),
//												 fabs(TexV+(pixBuffer[i].scaleFactorDvDx[0]+pixBuffer[i].scaleFactorDvDy[0])/2),LoD,w_ratio);
//
//				color = color/2 + colorNextLevel/2;
//			} else
//				color = TrilinearFilter(TexU, TexV, LoD, w_ratio);
//
//			break;

		}
	} else {
		switch (magFilter[tid]) {
		case GL_NEAREST:    //u,v nearest filter
			color = GetTexColor(coord ,0, tid);
			break;

		case GL_LINEAR:     //u,v bilinear filter
			color = BilinearFilter(coord,0, tid);
			break;
		}
	}

	TEXPRINTF("%4d %4d %7.2f %7.2f\t",
			  (int)pixelInput.attr[0].x,
			  (int)pixelInput.attr[0].y,
			  coord.s,
			  coord.t);
	//TEXPRINTF("  %2x %2x %2x %2x",color.r,color.g,color.b,color.a);
	TEXPRINTF("%2d %3.2f\t\t",LoD, w_ratio);
	TEXPRINTF("%3.2f %3.2f %3.2f %3.2f\n",
			  pixelInput.scaleFacDX[attrIndx].s*texImage[tid].widthLevel[0],
			  pixelInput.scaleFacDX[attrIndx].t*texImage[tid].heightLevel[0],
			  pixelInput.scaleFacDY[attrIndx].s*texImage[tid].widthLevel[0],
			  pixelInput.scaleFacDY[attrIndx].t*texImage[tid].heightLevel[0]);

	return color;
}

/// @fixme (elvis#1#): Dirty Shader simulator
pixel Rasterizer::ShaderEXE(pixel pixInput)
{
    texIndx = 4;

    floatVec4 temp;
    float eyevector[] = {0.0, 0.0, 1,0};
    float dotresult;

	fixColor4 texColor0 = TextureMapping(pixInput.attr[texIndx], texIndx, pixInput, 0);
	fixColor4 texColor1 = TextureMapping(pixInput.attr[texIndx], texIndx, pixInput, 1);

//	pixInput.attr[colIndx].r = texColor0.r;
//	pixInput.attr[colIndx].g = texColor0.g;
//	pixInput.attr[colIndx].b = texColor0.b;

	temp.r = ((float)texColor1.r / 255)*2 - 1;
	temp.g = ((float)texColor1.g / 255)*2 - 1;
	temp.b = ((float)texColor1.b / 255)*2 - 1;

	dotresult = eyevector[0]*temp.r + eyevector[1]*temp.g + eyevector[2]*temp.b;

	pixInput.attr[colIndx].r = texColor0.r * dotresult;
	pixInput.attr[colIndx].g = texColor0.g * dotresult;
	pixInput.attr[colIndx].b = texColor0.b * dotresult;

//	pixInput.attr[colIndx].r = texColor0.r + texColor1.r;
//	pixInput.attr[colIndx].g = texColor0.g + texColor1.g;
//	pixInput.attr[colIndx].b = texColor0.b + texColor1.b;

}

void Rasterizer::PerFragmentOp(pixel pixInput)
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
    *(cBufPtr + bufOffset*4 + 0) = (unsigned char)pixInput.attr[colIndx].r;// R
    *(cBufPtr + bufOffset*4 + 1) = (unsigned char)pixInput.attr[colIndx].g;// G
    *(cBufPtr + bufOffset*4 + 2) = (unsigned char)pixInput.attr[colIndx].b;// B
    *(cBufPtr + bufOffset*4 + 3) = (unsigned char)pixInput.attr[colIndx].a;// A
}

void Rasterizer::ClearBuffer(unsigned int mask)
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

void Rasterizer::ClearTexCache()
{
	for(int i=0; i<TEX_CACHE_ENTRY_SIZE; i++) {
		TexCache.valid[i][0] =
		TexCache.valid[i][1] =
		TexCache.valid[i][2] =
		TexCache.valid[i][3] = false;
		TexCache.LRU[i][0] =
		TexCache.LRU[i][1] =
		TexCache.LRU[i][2] =
		TexCache.LRU[i][3] = 0;
	}
	TexCache.hit = 0;
	TexCache.miss = 0;
	TexCache.coldMiss = 0;
}

Rasterizer::Rasterizer()
{
	AlphaRef = 0;
	DepthRef = 255;

	minFilter[0] = minFilter[1] = GL_NEAREST_MIPMAP_LINEAR;
	magFilter[0] = magFilter[1] = GL_LINEAR;
	wrapS[0] = wrapS[1] = GL_REPEAT;
	wrapT[0] = wrapT[1] = GL_REPEAT;
	AlphaTestMode = GL_ALWAYS;
	DepthTestMode = GL_LESS;

	depthTestEnable = false;
	blendEnable = false;

	posIndx = 0;
	colIndx = 1;
	texIndx = 4;

	ClearTexCache();
}

