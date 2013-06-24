#include "texture_unit.h"

void TextureUnit::ClearTexCache()
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
	hit = 0;
	miss = 0;
	coldMiss = 0;
}

/**
 * u,v - Texture coodinate in 2 dimension directions.
 * s,b,o - 3 block-based hirachy level, Super block, Block, Offset, in textrue
 * coordinate.
 *
 * The following two function are to calculate 1D address and fetch data in
 * system memory from 6D block-based texture address.
 */
int TextureUnit::CalcTexAdd(short int us,
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

floatVec4 TextureUnit::GetTexColor(floatVec4 coordIn, int level, int tid)
{
	int i,j;
	unsigned short u, v;
	unsigned short tag, entry, offset, U_Block, V_Block, U_Offset, V_Offset, U_Super, V_Super;
	unsigned char *texTmpPtr = NULL;
	unsigned char tWay = 0;
	unsigned char LRUbiggest = 0;
#ifdef SHOW_TEXCACHE_COLD_MISS
    bool isColdMiss = false;
#endif // SHOW_TEXCACHE_COLD_MISS

	u = (unsigned short)coordIn.s;
	v = (unsigned short)coordIn.t;

#ifdef SHOW_MIPMAP_LEVEL
	floatVec4 mipmaplevel;
	mipmaplevel = floatVec4(1.0-level*0.1, 1.0-level*0.1, 1.0-level*0.1, 1.0);
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
				hit++;
				TexCache.LRU[entry][i] = 0;

				return TexCache.color[entry][offset][i];
			}
		}
#ifdef SHOW_TEXCACHE_COLD_MISS
		else
			isColdMiss = true;
#endif// SHOW_TEXCACHE_COLD_MISS
	}

	///*********** Texture cache miss ****************
	miss++;

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

			TexCache.color[entry][j*TEX_CACHE_BLOCK_SIZE_ROOT+i][tWay].r = ((float)(*texTmpPtr++)/255);
			TexCache.color[entry][j*TEX_CACHE_BLOCK_SIZE_ROOT+i][tWay].g = ((float)(*texTmpPtr++)/255);
			TexCache.color[entry][j*TEX_CACHE_BLOCK_SIZE_ROOT+i][tWay].b = ((float)(*texTmpPtr++)/255);
			TexCache.color[entry][j*TEX_CACHE_BLOCK_SIZE_ROOT+i][tWay].a = ((float)(*texTmpPtr++)/255);
		}
	}
#ifdef SHOW_TEXCACHE_COLD_MISS
	if (isColdMiss)
		return floatVec4(1.0, 0.0, 0.0, 1.0);
#endif //SHOW_TEXCACHE_COLD_MISS
#ifdef SHOW_TEXCACHE_MISS
	return floatVec4(0.0, 1.0, 0.0, 1.0);
#endif //SHOW_TEXCACHE_MISS

	return TexCache.color[entry][offset][tWay];
}

floatVec4 TextureUnit::TexCoordWrap(floatVec4 coordIn, int level, int tid)
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

floatVec4 TextureUnit::BilinearFilter(floatVec4 coordIn,int level, int tid)
{
	/// coord[4]: 2 3
	///			  0 1
	floatVec4 coordLOD[4];

	unsigned short texUC, texVC;
	float u_ratio, v_ratio;
	floatVec4 color;
	floatVec4 TexColor[4];

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

floatVec4 TextureUnit::TrilinearFilter(floatVec4 coordIn,
									   int level,
									   float w_ratio,
									   int tid )
{
	floatVec4 color[2];
	int maxLevel = texImage[tid].maxLevel;
	color[0] = BilinearFilter(coordIn, level, tid);
	color[1] = BilinearFilter(coordIn, std::min(level+1, maxLevel), tid);

	color[0] = color[0]*(1-w_ratio) + color[1]*w_ratio;

	return color[0];
}

floatVec4 TextureUnit::TextureSample(floatVec4 coordIn,
									 int level,
									 floatVec4 scaleFacDX,
									 floatVec4 scaleFacDY,
									 int tid )
{
	floatVec4 coord;
	float w_ratio;
	float maxScaleFac;
	floatVec4 TexColor[2];
	floatVec4 color;
//	floatVec4 colorNextLevel;
	int LoD, maxLevel;

	//find absolutely coord in texture image
	coord.s = coordIn.s*texImage[tid].widthLevel[0];
	coord.t = coordIn.t*texImage[tid].heightLevel[0];
	coord.p = coordIn.p;
	coord.q = coordIn.q;

	maxScaleFac = std::max(
					std::max(scaleFacDX.s*texImage[tid].widthLevel[0],
							 scaleFacDX.t*texImage[tid].heightLevel[0]),
					std::max(scaleFacDY.s*texImage[tid].widthLevel[0],
							 scaleFacDY.t*texImage[tid].heightLevel[0])
				);

	w_ratio = frexp(maxScaleFac, &LoD);
	w_ratio = w_ratio*2-1;
	LoD--;

	maxLevel = texImage[tid].maxLevel;

	if (level == -1)
		LoD = std::min(LoD, maxLevel);
	else
		LoD = level;

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
			  scaleFacDX.s*texImage[tid].widthLevel[0],
			  scaleFacDX.t*texImage[tid].heightLevel[0],
			  scaleFacDY.s*texImage[tid].widthLevel[0],
			  scaleFacDY.t*texImage[tid].heightLevel[0]);

	return color;
}
