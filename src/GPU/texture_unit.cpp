/**
 *	@file texture_unit.h
 *  @brief Texture unit class implementation
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#include "texture_unit.h"

void TextureUnit::ClearTexCache()
{
	for(int i=0; i<TEX_CACHE_ENTRY_SIZE; i++) {
		TexCache.valid[i][0] =
		TexCache.valid[i][1] =
		TexCache.valid[i][2] =
		TexCache.valid[i][3] = false;
		TexCache.RRFlag[i] = 0;
	}
	hit = 0;
	miss = 0;
	coldMiss = 0;
}

/**
 *	This function is to convert 6D block-based texture address and return 1D
 *	address and fetch data in system memory.
 *
 *	@param u,v 		Texture coordinate in 2 dimension directions.
 *	@param s,b,o 	3 block-based hierarchy level, Super block, Block, Offset,
 *	in texture coordinate.
 *
 *	@return 1D address
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

/**
 *	Get the texel's color in the specified texture coordinate. You can toggle
 *	\ref NO_TEX_CACHE in \ref gpu_config.h to determine whether this function
 *	use texture cache or not.
 *
 *	@param coordIn 	The target texture coordinate.
 *	@param level 	This target coordinate is belongs to which level.
 *	@param tid 		This target coordinate is belongs to which texContext.
 *
 *	@return the target texel's color
 */

floatVec4 TextureUnit::GetTexColor(floatVec4 coordIn, int level, int tid)
{
	unsigned char *texTmpPtr = NULL;
	unsigned short u,v;
#ifdef NO_TEX_CACHE
	floatVec4 color;

	u = (unsigned short)coordIn.s;
	v = (unsigned short)coordIn.t;

	texTmpPtr = texImage[tid].data[level] +
				(v*texImage[tid].widthLevel[level] + u)*4;

	color.r = ((float)(*texTmpPtr++)/255);
	color.g = ((float)(*texTmpPtr++)/255);
	color.b = ((float)(*texTmpPtr++)/255);
	color.a = ((float)(*texTmpPtr++)/255);

	return color;
#else
	int i,j; //loop counter
	unsigned int tag;
	unsigned short entry, offset, U_Block, V_Block, U_Offset, V_Offset, U_Super, V_Super;
	unsigned char tWay = 0;
	unsigned char LRUbiggest = 0;
    bool isColdMiss = false;

	if (level > texImage[tid].maxLevel) {
		fprintf(stderr,
				"TexUnit: %d exceed maximum level %d\n",
				level,
				texImage[tid].maxLevel );
		return floatVec4(0.0, 0.0, 0.0, 0.0);
	}

	u = (unsigned short)coordIn.s;
	v = (unsigned short)coordIn.t;

	if (u > texImage[tid].widthLevel[level] ||
		v > texImage[tid].heightLevel[level]) {
		fprintf(stderr,
				"TexUnit: (%d,%d)Out of the texture image's bound(%d,%d)\n",
				u, v,
				texImage[tid].widthLevel[level],
				texImage[tid].heightLevel[level] );
		return floatVec4(0.0, 0.0, 0.0, 0.0);
	}

	U_Super = u >> (TEX_CACHE_BLOCK_SIZE_ROOT_LOG + TEX_CACHE_ENTRY_SIZE_ROOT_LOG);
	V_Super = v >> (TEX_CACHE_BLOCK_SIZE_ROOT_LOG + TEX_CACHE_ENTRY_SIZE_ROOT_LOG);
	U_Block = u >> (TEX_CACHE_BLOCK_SIZE_ROOT_LOG) & (TEX_CACHE_ENTRY_SIZE_ROOT - 1);
	V_Block = v >> (TEX_CACHE_BLOCK_SIZE_ROOT_LOG) & (TEX_CACHE_ENTRY_SIZE_ROOT - 1);
	U_Offset = u & (TEX_CACHE_BLOCK_SIZE_ROOT - 1);
	V_Offset = v & (TEX_CACHE_BLOCK_SIZE_ROOT - 1);
	tag = (int)( (V_Super << 12) | (U_Super&0x0fff) );

	///@note Simply append level and texture_id after tag bit
	tag = (tag << 4) | (level&0xf);
	tag = (tag << 1) | (tid&0x1);

	entry = V_Block * TEX_CACHE_ENTRY_SIZE_ROOT + U_Block;
	offset = V_Offset * TEX_CACHE_BLOCK_SIZE_ROOT + U_Offset;

	for (i=0; i<TEX_WAY_ASSOCIATION; i++) {
		if (TexCache.valid[entry][i] == true) {
			if (TexCache.tag[entry][i] == tag) {
			//*************** Texture cache hit *************
				hit++;
				return TexCache.color[entry][offset][i];
			}
		}
		else
			isColdMiss = true;
	}

	//*********** Texture cache miss ****************
	miss++;

	tWay = TexCache.RRFlag[entry] % TEX_WAY_ASSOCIATION;
	TexCache.RRFlag[entry]++;
	TexCache.tag[entry][tWay] = tag;

	if (TexCache.valid[entry][tWay] == false)
		TexCache.valid[entry][tWay] = true;

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
#	ifdef SHOW_TEXCACHE_COLD_MISS
	if (isColdMiss)
		return floatVec4(1.0, 0.0, 0.0, 1.0);
#	endif //SHOW_TEXCACHE_COLD_MISS

#	if defined(SHOW_TEXCACHE_MISS)
	return floatVec4(0.0, 1.0, 0.0, 1.0);
#	else
	return TexCache.color[entry][offset][tWay];
#	endif

#endif // NO_TEX_CACHE
}

/**
 *	Perform texture wrap operation on texture coordinate.
 *
 *	@param coordIn 	The target texture coordinate.
 *	@param level 	This target coordinate is belongs to which level.
 *	@param tid 		This target coordinate is belongs to which texContext.
 *
 *	@return "Wrapped" texture coordinate.
 */
floatVec4 TextureUnit::TexCoordWrap(floatVec4 coordIn, int level, int tid)
{
	floatVec4 temp;

	switch (wrapS[tid]){
	case GL_REPEAT:
		/*	The function's behavior of "fmod" in C++ is not matched
		 *	with OpenGL.
		 *	fmod(x,y) in C++: x - y * trunc(x/y);
		 *	fmod(x,y) in OpenGL: x - y * floor(x/y);
		 */
//		temp.s = fmod(coordIn.s,texImage[tid].widthLevel[level]);
		temp.s = coordIn.s - texImage[tid].widthLevel[level] *
				 floor(coordIn.s/texImage[tid].widthLevel[level]);
		break;
	case GL_CLAMP_TO_EDGE:
		temp.s = std::min(coordIn.s, (float)texImage[tid].widthLevel[level]-1);
		break;
	default:
		fprintf(stderr, "TexUnit: Unknown Texture Wrap mode in x-axis!!\n");
		break;
	}

	switch (wrapT[tid]){
	case GL_REPEAT:
//		temp.t = fmod(coordIn.t,texImage[tid].heightLevel[level]);
		temp.t = coordIn.t - texImage[tid].heightLevel[level] *
				 floor(coordIn.t/texImage[tid].heightLevel[level]);
		break;
	case GL_CLAMP_TO_EDGE:
		temp.t = std::min(coordIn.t, (float)texImage[tid].heightLevel[level]-1);
		break;
	default:
		fprintf(stderr, "TexUnit: Unknown Texture Wrap mode in y-axis!!\n");
		break;
	}

	return temp;
}

/**
 *	Perform Bi-linear filter on specified texture coordinate.
 *
 *	@param coordIn The target texture coordinate.
 *	@param level This target coordinate is belongs to which level.
 *	@param tid This target coordinate is belongs to which texture unit.
 *
 *	@return The final color.
 */
floatVec4 TextureUnit::BilinearFilter(floatVec4 coordIn,int level, int tid)
{
	// coord[4]: 2 3
	//			 0 1
	floatVec4 coordLOD[4];

	float u_ratio, v_ratio;
	floatVec4 color;
	floatVec4 TexColor[4];

	double intPart; //No use

	coordLOD[0].s = coordIn.s / (1<<level) - 0.5;
	coordLOD[0].t = coordIn.t / (1<<level) - 0.5;

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

	u_ratio = modf(coordLOD[0].s, &intPart);
	v_ratio = modf(coordLOD[0].t, &intPart);

	color = (TexColor[0]*(1-u_ratio) + TexColor[1]*u_ratio)*(1-v_ratio) +
			(TexColor[2]*(1-u_ratio) + TexColor[3]*u_ratio)*v_ratio;

	return color;
}

/**
 *	Perform Tri-linear filter on specified texture coordinate, this operation is
 *	actually invokes TextureUnit::BilinearFilter() twice.
 *
 *	@param coordIn 	The target texture coordinate.
 *	@param level 	This target coordinate is belongs to which level.
 *	@param w_ratio 	The target coordinate's w-axis ratio for color interpolation.
 *	@param tid 		This target coordinate is belongs to which texContext.
 *
 *	@return The final color.
 */
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
									 int targetType,
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
		LoD = CLAMP(LoD, 0, maxLevel);
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
			coord = TexCoordWrap(coord, 0, tid);
			color = GetTexColor(coord ,0, tid);
			break;

		case GL_LINEAR:     //u,v bilinear filter
			color = BilinearFilter(coord,0, tid);
			break;
		}
	}

	TEXPRINTF("%7.2f %7.2f\t", coord.s,  coord.t);
	//TEXPRINTF("  %2x %2x %2x %2x",color.r,color.g,color.b,color.a);
	TEXPRINTF("%2d %3.2f\t\t",LoD, w_ratio);
	TEXPRINTF("%3.2f %3.2f %3.2f %3.2f\n",
			  scaleFacDX.s*texImage[tid].widthLevel[LoD],
			  scaleFacDX.t*texImage[tid].heightLevel[LoD],
			  scaleFacDY.s*texImage[tid].widthLevel[LoD],
			  scaleFacDY.t*texImage[tid].heightLevel[LoD]);

	return color;
}
