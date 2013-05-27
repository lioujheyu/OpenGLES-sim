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
	int lc;
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

		//Interpolate the 4 pixel's all attributes, include perspective correction
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
		//Caculate 4 pixel's attributes' scale factor
		for (int attrCnt=1;attrCnt<MAX_ATTRIBUTE_NUMBER;attrCnt++){
			if (!attrEnable[attrCnt])
				continue;
			pixelStamp[0].scaleFacDX[attrCnt].s = pixelStamp[1].scaleFacDX[attrCnt].s
												= pixelStamp[1].attr[attrCnt].s-pixelStamp[0].attr[attrCnt].s;
			pixelStamp[0].scaleFacDX[attrCnt].t = pixelStamp[1].scaleFacDX[attrCnt].t
												= pixelStamp[1].attr[attrCnt].t-pixelStamp[0].attr[attrCnt].t;
			pixelStamp[0].scaleFacDX[attrCnt].p = pixelStamp[1].scaleFacDX[attrCnt].p
												= pixelStamp[1].attr[attrCnt].p-pixelStamp[0].attr[attrCnt].p;
			pixelStamp[0].scaleFacDX[attrCnt].q = pixelStamp[1].scaleFacDX[attrCnt].q
												= pixelStamp[1].attr[attrCnt].q-pixelStamp[0].attr[attrCnt].q;

			pixelStamp[2].scaleFacDX[attrCnt].s = pixelStamp[3].scaleFacDX[attrCnt].s
												= pixelStamp[3].attr[attrCnt].s-pixelStamp[2].attr[attrCnt].s;
			pixelStamp[2].scaleFacDX[attrCnt].t = pixelStamp[3].scaleFacDX[attrCnt].t
												= pixelStamp[3].attr[attrCnt].t-pixelStamp[2].attr[attrCnt].t;
			pixelStamp[2].scaleFacDX[attrCnt].p = pixelStamp[3].scaleFacDX[attrCnt].p
												= pixelStamp[3].attr[attrCnt].p-pixelStamp[2].attr[attrCnt].p;
			pixelStamp[2].scaleFacDX[attrCnt].q = pixelStamp[3].scaleFacDX[attrCnt].q
												= pixelStamp[3].attr[attrCnt].q-pixelStamp[2].attr[attrCnt].q;

			pixelStamp[0].scaleFacDY[attrCnt].s = pixelStamp[2].scaleFacDY[attrCnt].s
												= pixelStamp[2].attr[attrCnt].s-pixelStamp[0].attr[attrCnt].s;
			pixelStamp[0].scaleFacDY[attrCnt].t = pixelStamp[2].scaleFacDY[attrCnt].t
												= pixelStamp[2].attr[attrCnt].t-pixelStamp[0].attr[attrCnt].t;
			pixelStamp[0].scaleFacDY[attrCnt].p = pixelStamp[2].scaleFacDY[attrCnt].p
												= pixelStamp[2].attr[attrCnt].p-pixelStamp[0].attr[attrCnt].p;
			pixelStamp[0].scaleFacDY[attrCnt].q = pixelStamp[2].scaleFacDY[attrCnt].q
												= pixelStamp[2].attr[attrCnt].q-pixelStamp[0].attr[attrCnt].q;

			pixelStamp[1].scaleFacDY[attrCnt].s = pixelStamp[3].scaleFacDY[attrCnt].s
												= pixelStamp[3].attr[attrCnt].s-pixelStamp[1].attr[attrCnt].s;
			pixelStamp[1].scaleFacDY[attrCnt].t = pixelStamp[3].scaleFacDY[attrCnt].t
												= pixelStamp[3].attr[attrCnt].t-pixelStamp[1].attr[attrCnt].t;
			pixelStamp[1].scaleFacDY[attrCnt].p = pixelStamp[3].scaleFacDY[attrCnt].p
												= pixelStamp[3].attr[attrCnt].p-pixelStamp[1].attr[attrCnt].p;
			pixelStamp[1].scaleFacDY[attrCnt].q = pixelStamp[3].scaleFacDY[attrCnt].q
												= pixelStamp[3].attr[attrCnt].q-pixelStamp[1].attr[attrCnt].q;
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

		for (int i = 0; i < pixBufferP; i++)
            pixBuffer[i] = ShaderEXE(pixBuffer[i]);

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

/*
 * u,v - Texture coodinate in 2 dimension directions.
 * s,b,o - 3 block-based hirachy level, Super block, Block, Offset, in textrue coordinate.
 *
 * The following two function are to calculate 1D address and fetch data
 * in system memory from 6D block-based texture address.
 */
int Rasterizer::CalcTexAdd(short int us,
                           short int ub,
                           short int uo,
                           short int vs,
                           short int vb,
                           short int vo,
                           int width,
                           int level)
{
	return (vs*TEX_CACHE_BLOCK_SIZE_ROOT*TEX_CACHE_ENTRY_Y+vb*TEX_CACHE_BLOCK_SIZE_ROOT+vo)*(width>>level)+
		   us*TEX_CACHE_BLOCK_SIZE_ROOT*TEX_CACHE_ENTRY_X+ub*TEX_CACHE_BLOCK_SIZE_ROOT+uo;
}

fixColor4 Rasterizer::GetTexColor(const unsigned short u, const unsigned short v, const unsigned int level, unsigned char id)
{
	int i,j;
	unsigned short tag, pos_cache, pos_block, U_Block, V_Block, U_Offset, V_Offset, U_Super, V_Super;
	unsigned char *texTmpPtr = NULL;
	unsigned char texel[4];

#ifdef MIPMAPLEVELTEST
	fixColor4 mipmaplevel;
	mipmaplevel = fixColor4(0xff-level*30, 0xff-level*30, 0xff-level*30, 0xff);
	return mipmaplevel;
#endif //MIPMAPLEVELTEST

	U_Super = u >> (TEX_CACHE_BLOCK_SIZE_ROOT_LOG + TEX_CACHE_ENTRY_X_LOG);
	V_Super = v >> (TEX_CACHE_BLOCK_SIZE_ROOT_LOG + TEX_CACHE_ENTRY_Y_LOG);
	U_Block = u >> (TEX_CACHE_BLOCK_SIZE_ROOT_LOG) & (TEX_CACHE_ENTRY_X - 1);
	V_Block = v >> (TEX_CACHE_BLOCK_SIZE_ROOT_LOG) & (TEX_CACHE_ENTRY_Y - 1);
	U_Offset = u & (TEX_CACHE_BLOCK_SIZE_ROOT - 1);
	V_Offset = v & (TEX_CACHE_BLOCK_SIZE_ROOT - 1);
	tag = (int)( (V_Super << 8) | (U_Super&0x00ff) );
    /// @fixme (elvis#1#): Simply append level and texture_id after tag bit to tell the differece of texture address
	tag = (tag << 4) | (level&0xf);
	tag = (tag << 1) | (id&0x1);

	pos_cache = V_Block * TEX_CACHE_ENTRY_X + U_Block;
	pos_block = V_Offset * TEX_CACHE_BLOCK_SIZE_ROOT + U_Offset;

	///*************** Texture cache hit *************
	if ((TexCache.valid[pos_cache] == true) && (TexCache.pos[pos_cache] == tag)) {
		TexCache.TexCacheHit++;
		return TexCache.color[pos_cache][pos_block];
	} else { ///*********** Texture cache miss *************
		TexCache.TexCacheMiss++;

		if (TexCache.valid[pos_cache] == false)
			TexCache.TexCacheColdMiss++;

		TexCache.valid[pos_cache] = true;
		TexCache.pos[pos_cache] = tag;

		fprintf(TEXDEBUGfp,"Texture Cache miss!! \n");

		for (j = 0; j < TEX_CACHE_BLOCK_SIZE_ROOT; j++) {
			for (i = 0; i < TEX_CACHE_BLOCK_SIZE_ROOT; i++) {
				texTmpPtr = texImage[id].data[level] + CalcTexAdd(U_Super,U_Block,i,
                                                                  V_Super,V_Block,j,
                                                                  texImage[id].width, level) * 4;

				//printf("%d %x (%d,%d)\n",level,texImage.data[level],u,v);

				TexCache.color[pos_cache][j*TEX_CACHE_BLOCK_SIZE_ROOT+i].r = *texTmpPtr++;
				TexCache.color[pos_cache][j*TEX_CACHE_BLOCK_SIZE_ROOT+i].g = *texTmpPtr++;
				TexCache.color[pos_cache][j*TEX_CACHE_BLOCK_SIZE_ROOT+i].b = *texTmpPtr++;
				TexCache.color[pos_cache][j*TEX_CACHE_BLOCK_SIZE_ROOT+i].a = *texTmpPtr++;
			}
		}
		return TexCache.color[pos_cache][pos_block];
	}
}

fixColor4 Rasterizer::BilinearFilter(float texU,float texV,int level, unsigned char id)
{
	float texULevel, texVLevel;
	unsigned short texUC, texVC;
	float u_ratio, v_ratio;
	fixColor4 color;
	fixColor4 TexColor[4];

	texULevel = texU / (1<<level);
	texULevel = (texULevel - 0.5)>0?texULevel - 0.5:0;
	texVLevel = texV / (1<<level);
	texVLevel = (texVLevel - 0.5)>0?texVLevel - 0.5:0;

	texUC = (unsigned short)floor(texULevel);
	texVC = (unsigned short)floor(texVLevel);

	u_ratio = texULevel - texUC;
	v_ratio = texVLevel - texVC;

	TexColor[0] = GetTexColor(texUC, texVC, level, id);
	TexColor[1] = GetTexColor((texUC+1>=texImage[id].width>>level)?texUC:texUC+1, texVC, level, id);
	TexColor[2] = GetTexColor(texUC, (texVC+1>=texImage[id].height>>level)?texVC:texVC+1, level, id);
	TexColor[3] = GetTexColor((texUC+1>=texImage[id].width>>level)?texUC:texUC+1, (texVC+1>=texImage[id].height>>level)?texVC:texVC+1, level, id);

	color = (TexColor[0]*(1-u_ratio) + TexColor[1]*u_ratio)*(1-v_ratio) + (TexColor[2]*(1-u_ratio) + TexColor[3]*u_ratio)*v_ratio;

	return color;
}

fixColor4  Rasterizer::TrilinearFilter(float texU, float texV, int level, float w_ratio, unsigned char id)
{
	fixColor4 color[2];
	color[0] = BilinearFilter(texU, texV, level, id);
	color[1] = BilinearFilter(texU, texV, (level+1)<texImage[id].maxLevel?level+1:texImage[id].maxLevel, id);

	color[0] = color[0]*(1-w_ratio) + color[1]*w_ratio;

	return color[0];
}

fixColor4 Rasterizer::TextureMapping(float TexUin, float TexVin, int attrIndx, pixel pixelInput, unsigned char id)
{
	float TexU, TexV;
	unsigned short TexUC, TexVC;
	float u_ratio, v_ratio, w_ratio;
	float maxScaleFac;
	fixColor4 TexColor[8];  // 1st level 2 3  2nd level 6 7
							//           0 1            4 5
	fixColor4 color, colorNextLevel;
	int LoD;

#ifdef TEXDEBUG
	fprintf(TEXDEBUGfp,"\nXXX--YYY--UUU.UU--VVV.VV----------------\n");
#endif
	//find absolutely position in texture image
	TexU = TexUin*texImage[id].width;
	TexV = TexVin*texImage[id].height;

	maxScaleFac = std::max(
					std::max(pixelInput.scaleFacDX[attrIndx].s*texImage[id].width , pixelInput.scaleFacDX[attrIndx].t*texImage[id].height),
					std::max(pixelInput.scaleFacDY[attrIndx].s*texImage[id].width , pixelInput.scaleFacDY[attrIndx].t*texImage[id].height)
				);

	w_ratio = frexp(maxScaleFac, &LoD);
	w_ratio = w_ratio*2-1;
	LoD--;


///********* Texture Wrap mode ***************************
	if (wrapS[id] == GL_REPEAT)
		TexU = fmod(TexU,texImage[id].width);
	//fmod: mod in floating point format, %(mod) can only be used under integer format
	else if (wrapS[id] == GL_CLAMP_TO_EDGE)
		TexU = (TexU < texImage[id].width-1)?((TexU > 0)?TexU:0):texImage[id].width-1;
	//0 <= TexU <= TexWidth-1
	else
		fprintf(stderr,"Wrong Texture Wrap mode in x-axis!!\n");

	if (wrapT[id] == GL_REPEAT)
		TexV = fmod(TexV,texImage[id].height);
	else if (wrapT[id] == GL_CLAMP_TO_EDGE)
		TexV = (TexV < texImage[id].height-1)?((TexV > 0)?TexV:0):texImage[id].height-1;
	//0 <= TexV <= TexHeight-1
	else
		fprintf(stderr,"Wrong Texture Wrap mode  in y-axis!!\n");
///*******************************************************

	TexUC = (unsigned short)floor(TexU);// floor: Round down value
	TexVC = (unsigned short)floor(TexV);

	///Prevent LoD exceed the maximum allowable LoD.
    LoD = (LoD > texImage[id].maxLevel)?texImage[id].maxLevel:LoD;

	if(LoD>0) {
		switch (minFilter[id]) {
		case GL_NEAREST:    //u,v nearest filter
			TexColor[0] = GetTexColor(TexUC, TexVC, 0, id);
			color = TexColor[0];
			break;
		case GL_LINEAR:     //u,v bilinear filter
			color = BilinearFilter(TexU, TexV, 0, id);
			break;
		case GL_NEAREST_MIPMAP_NEAREST: //u,v,w nearest filter
			TexColor[0] = GetTexColor(TexUC>>LoD, TexVC>>LoD, LoD, id);
			color = TexColor[0];
			break;
		case GL_LINEAR_MIPMAP_NEAREST:  //u,v bilinear, w nearest filter
			color = BilinearFilter(TexU,TexV,LoD, id);
			break;
		case GL_NEAREST_MIPMAP_LINEAR:  //u,v nearest, w linear filter
			TexColor[0] = GetTexColor(TexUC>>LoD, TexVC>>LoD, LoD, id);

			LoD = (LoD+1 <= texImage[id].maxLevel)?LoD+1:texImage[id].maxLevel;
			TexColor[1] = GetTexColor(TexUC>>LoD, TexVC>>LoD, LoD, id);

			color = TexColor[0]*(1-w_ratio) + TexColor[1]*w_ratio;
			break;
		case GL_LINEAR_MIPMAP_LINEAR:   //u,v,w trilinear filter
			color = TrilinearFilter(TexU, TexV, LoD, w_ratio, id);
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
		switch (magFilter[id]) {
		case GL_NEAREST:    //u,v nearest filter
			TexColor[0] = GetTexColor(TexUC, TexVC ,0, id);
			color = TexColor[0];
			break;

		case GL_LINEAR:     //u,v bilinear filter
			color = BilinearFilter(TexU,TexV,0, id);
			break;

		case GL_NEAREST_MIPMAP_NEAREST: //u,v,w nearest filter
			TexColor[0] = GetTexColor(TexUC>>LoD, TexVC>>LoD ,LoD, id);
			color = TexColor[0];
			break;
		}
	}

	return color;

#ifdef TEXDEBUG
	fprintf(TEXDEBUGfp,"%3d  %3d  %6.2f  %6.2f",(int)pixBuffer[i].pos4[0],(int)pixBuffer[i].pos4[1],TexU,TexV);
	fprintf(TEXDEBUGfp,"  %2x %2x %2x %2x",color.r,color.g,color.b,color.a);
	fprintf(TEXDEBUGfp,"  %2d %3.2f\n",LoD, w_ratio);
#endif
}

// @fixme (elvis#1#): Dirty Shader simulator
pixel Rasterizer::ShaderEXE(pixel pixInput)
{
    texIndx = 4;

	fixColor4 texColor0 = TextureMapping(pixInput.attr[texIndx].s, pixInput.attr[texIndx].t, texIndx, pixInput, 0);
	fixColor4 texColor1 = TextureMapping(pixInput.attr[texIndx].s, pixInput.attr[texIndx].t, texIndx, pixInput, 1);

	pixInput.attr[colIndx].r = texColor0.r;
	pixInput.attr[colIndx].g = texColor0.g;
	pixInput.attr[colIndx].b = texColor0.b;

//	pixInput.attr[colIndx].r = texColor0.r * texColor1.r / 256;
//	pixInput.attr[colIndx].g = texColor0.g * texColor1.g / 256;
//	pixInput.attr[colIndx].b = texColor0.b * texColor1.b / 256;

	return pixInput;
}

void Rasterizer::PerFragmentOp()
{
	int i;
	bool DepthTest = true;
	int bufOffset;

	for (i = 0; i < pixBufferP; i++) {
		bufOffset = (int)pixBuffer[i].attr[0].y*viewPortW + (int)pixBuffer[i].attr[0].x;

        ///Depth test
		if (depthTestEnable){
            if (DepthTestMode == GL_NEVER)
                DepthTest = false;
            else if (DepthTestMode == GL_LESS)
                DepthTest = pixBuffer[i].attr[0].z  < *(dBufPtr + bufOffset);
            else if (DepthTestMode == GL_EQUAL)
                DepthTest = pixBuffer[i].attr[0].z == *(dBufPtr + bufOffset);
            else if (DepthTestMode == GL_LEQUAL)
                DepthTest = pixBuffer[i].attr[0].z <= *(dBufPtr + bufOffset);
            else if (DepthTestMode == GL_GREATER)
                DepthTest = pixBuffer[i].attr[0].z  > *(dBufPtr + bufOffset);
            else if (DepthTestMode == GL_NOTEQUAL)
                DepthTest = pixBuffer[i].attr[0].z != *(dBufPtr + bufOffset);
            else if (DepthTestMode == GL_GEQUAL)
                DepthTest = pixBuffer[i].attr[0].z >= *(dBufPtr + bufOffset);
            else if (DepthTestMode == GL_ALWAYS)
                DepthTest = true;
            else
                fprintf(stderr,"Wrong Depth Test mode!!\n");
            if (DepthTest == false)
                continue;
            else
                *(dBufPtr + bufOffset) = pixBuffer[i].attr[0].z;
		}

		///Alpha blending
		if (blendEnable){

		}

		///Color buffer write back
		*(cBufPtr + bufOffset*4 + 0) = (unsigned char)pixBuffer[i].attr[colIndx].r;// R
		*(cBufPtr + bufOffset*4 + 1) = (unsigned char)pixBuffer[i].attr[colIndx].g;// G
		*(cBufPtr + bufOffset*4 + 2) = (unsigned char)pixBuffer[i].attr[colIndx].b;// B
		*(cBufPtr + bufOffset*4 + 3) = (unsigned char)pixBuffer[i].attr[colIndx].a;// A
	}
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

Rasterizer::Rasterizer()
{
	int i;

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

#ifdef TEXDEBUG
	TEXDEBUGfp = fopen("Result/TexDebug.txt","w");
#endif

#ifdef PIXEL_GENERATE_DEBUG
	PIXEL_GENERATE_DEBUGfp = fopen("Result/PixelGenerateDebug.txt","w");
#endif
}
