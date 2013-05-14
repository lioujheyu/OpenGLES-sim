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

	Edge[0][0] = vtxPrimitive[0].varying[vtxPosIndx].b - vtxPrimitive[1].varying[vtxPosIndx].b;
	Edge[0][1] = vtxPrimitive[0].varying[vtxPosIndx].a - vtxPrimitive[1].varying[vtxPosIndx].a;
	Edge[1][0] = vtxPrimitive[1].varying[vtxPosIndx].b - vtxPrimitive[2].varying[vtxPosIndx].b;
	Edge[1][1] = vtxPrimitive[1].varying[vtxPosIndx].a - vtxPrimitive[2].varying[vtxPosIndx].a;
	Edge[2][0] = vtxPrimitive[2].varying[vtxPosIndx].b - vtxPrimitive[0].varying[vtxPosIndx].b;
	Edge[2][1] = vtxPrimitive[2].varying[vtxPosIndx].a - vtxPrimitive[0].varying[vtxPosIndx].a;

	constantC = Edge[0][1]*Edge[1][0] - Edge[0][0]*Edge[1][1];
	area2Reciprocal = 1/constantC;

	LY = std::min(vtxPrimitive[0].varying[vtxPosIndx].b, std::min(vtxPrimitive[1].varying[vtxPosIndx].b, vtxPrimitive[2].varying[vtxPosIndx].b));
	LX = std::min(vtxPrimitive[0].varying[vtxPosIndx].a, std::min(vtxPrimitive[1].varying[vtxPosIndx].a, vtxPrimitive[2].varying[vtxPosIndx].a));
	HY = std::max(vtxPrimitive[0].varying[vtxPosIndx].b, std::max(vtxPrimitive[1].varying[vtxPosIndx].b, vtxPrimitive[2].varying[vtxPosIndx].b));
	RX = std::max(vtxPrimitive[0].varying[vtxPosIndx].a, std::max(vtxPrimitive[1].varying[vtxPosIndx].a, vtxPrimitive[2].varying[vtxPosIndx].a));
}


void Rasterizer::PixelGenerate()
{
	int a = 0;

	int x,y;
	float EdgeTest[3];
	bool effectStatus;

	// Bondary Box in tile

	pixBufferP = 0;

	for (y = LY; y <= HY; y++) {
		for (x = LX; x <= RX; x++) {

			//First edge test
			EdgeTest[0] = (x + 0.5 - vertexREG[1].pos4[0]) * Edge[0][0]-
						  (y + 0.5 - vertexREG[1].pos4[1]) * Edge[0][1];
			//Second edge test
			EdgeTest[1] = (x + 0.5 - vertexREG[2].pos4[0]) * Edge[1][0]-
						  (y + 0.5 - vertexREG[2].pos4[1]) * Edge[1][1];
			//Third edge test
			EdgeTest[2] = (x + 0.5 - vertexREG[0].pos4[0]) * Edge[2][0]-
						  (y + 0.5 - vertexREG[0].pos4[1]) * Edge[2][1];

			effectStatus = (EdgeTest[0]>=0) & (EdgeTest[1]>=0) & (EdgeTest[2]>=0);

			if (effectStatus == true) {
				//Interpolation
				pixBuffer[pixBufferP].pos4[0] = x;
				pixBuffer[pixBufferP].pos4[1] = y;
				pixBuffer[pixBufferP].baryCentricPos3[0] = EdgeTest[2]*area2Reciprocal;
				pixBuffer[pixBufferP].baryCentricPos3[1] = EdgeTest[0]*area2Reciprocal;
				pixBuffer[pixBufferP].baryCentricPos3[2] = EdgeTest[1]*area2Reciprocal;

				pixBuffer[pixBufferP].pos4[2] = vertexREG[0].pos4[2]
                                                + pixBuffer[pixBufferP].baryCentricPos3[0] * (vertexREG[1].pos4[2] - vertexREG[0].pos4[2])
                                                + pixBuffer[pixBufferP].baryCentricPos3[1] * (vertexREG[2].pos4[2] - vertexREG[0].pos4[2]);
				pixBuffer[pixBufferP].pos4[3] = vertexREG[0].pos4[3]
                                                + pixBuffer[pixBufferP].baryCentricPos3[0] * (vertexREG[1].pos4[3] - vertexREG[0].pos4[3])
												+ pixBuffer[pixBufferP].baryCentricPos3[1] * (vertexREG[2].pos4[3] - vertexREG[0].pos4[3]);
				pixBuffer[pixBufferP].texU[0] = vertexREG[0].TexU[0]
                                                + pixBuffer[pixBufferP].baryCentricPos3[0] * (vertexREG[1].TexU[0] - vertexREG[0].TexU[0])
												+ pixBuffer[pixBufferP].baryCentricPos3[1] * (vertexREG[2].TexU[0] - vertexREG[0].TexU[0]);
				pixBuffer[pixBufferP].texU[0] = pixBuffer[pixBufferP].texU[0] / pixBuffer[pixBufferP].pos4[3];
				pixBuffer[pixBufferP].texV[0] = vertexREG[0].TexV[0]
                                                + pixBuffer[pixBufferP].baryCentricPos3[0] * (vertexREG[1].TexV[0] - vertexREG[0].TexV[0])
												+ pixBuffer[pixBufferP].baryCentricPos3[1] * (vertexREG[2].TexV[0] - vertexREG[0].TexV[0]);
				pixBuffer[pixBufferP].texV[0] = pixBuffer[pixBufferP].texV[0] / pixBuffer[pixBufferP].pos4[3];
				for (a=0; a<4; a++) {
					pixBuffer[pixBufferP].color[a] = vertexREG[0].color[a]
                                                     + pixBuffer[pixBufferP].baryCentricPos3[0]*(vertexREG[1].color[a] - vertexREG[0].color[a])
													 + pixBuffer[pixBufferP].baryCentricPos3[1]*(vertexREG[2].color[a] - vertexREG[0].color[a]);
					//pixBuffer[pixBufferP].color[a] = pixBuffer[pixBufferP].color[a] / pixBuffer[pixBufferP].pos4[3];
				}

#ifdef PIXEL_GENERATE_DEBUG
				fprintf(PIXEL_GENERATE_DEBUGfp,
                        "Postition:(%3d,%3d,%6.2f),Color:(%03x %03x %03x %4.2f)\n",
						(int)pixBuffer[pixBufferP].pos4[0],
                        (int)pixBuffer[pixBufferP].pos4[1],
                        pixBuffer[pixBufferP].pos4[2],
						(int)pixBuffer[pixBufferP].color[0],
                        (int)pixBuffer[pixBufferP].color[1],
                        (int)pixBuffer[pixBufferP].color[2],
                        pixBuffer[pixBufferP].color[3]);
#endif
				TextureMapping();
				PerFragmentOp();
			}
		}
	}
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

	centralTest[0] = (x+(1<<level)-vertexREG[1].pos4[0])*Edge[0][0]-
					 (y+(1<<level)-vertexREG[1].pos4[1])*Edge[0][1];
	centralTest[1] = (x+(1<<level)-vertexREG[2].pos4[0])*Edge[1][0]-
					 (y+(1<<level)-vertexREG[2].pos4[1])*Edge[1][1];
	centralTest[2] = (x+(1<<level)-vertexREG[0].pos4[0])*Edge[2][0]-
					 (y+(1<<level)-vertexREG[0].pos4[1])*Edge[2][1];

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

		pixelStamp[0].pos4[0] = x;
		pixelStamp[0].pos4[1] = y;
		pixelStamp[0].baryCentricPos3[0] = cornerTest[0][2]*area2Reciprocal;
		pixelStamp[0].baryCentricPos3[1] = cornerTest[0][0]*area2Reciprocal;
		pixelStamp[0].baryCentricPos3[2] = cornerTest[0][1]*area2Reciprocal;
		pixelStamp[0].pos4[2] = vertexREG[0].pos4[2] + pixelStamp[0].baryCentricPos3[0]*(vertexREG[1].pos4[2] - vertexREG[0].pos4[2])
								+ pixelStamp[0].baryCentricPos3[1]*(vertexREG[2].pos4[2] - vertexREG[0].pos4[2]);
		pixelStamp[0].pos4[3] = vertexREG[0].pos4[3] + pixelStamp[0].baryCentricPos3[0]*(vertexREG[1].pos4[3] - vertexREG[0].pos4[3])
								+ pixelStamp[0].baryCentricPos3[1]*(vertexREG[2].pos4[3] - vertexREG[0].pos4[3]);
		pixelStamp[0].texU[0] = vertexREG[0].TexU[0] + pixelStamp[0].baryCentricPos3[0]*(vertexREG[1].TexU[0] - vertexREG[0].TexU[0])
								+ pixelStamp[0].baryCentricPos3[1]*(vertexREG[2].TexU[0] - vertexREG[0].TexU[0]);
		pixelStamp[0].texV[0] = vertexREG[0].TexV[0] + pixelStamp[0].baryCentricPos3[0]*(vertexREG[1].TexV[0] - vertexREG[0].TexV[0])
								+ pixelStamp[0].baryCentricPos3[1]*(vertexREG[2].TexV[0] - vertexREG[0].TexV[0]);
		for (lc=0; lc<4; lc++) {
			pixelStamp[0].color[lc] = vertexREG[0].color[lc] + pixelStamp[0].baryCentricPos3[0]*(vertexREG[1].color[lc] - vertexREG[0].color[lc])
									  + pixelStamp[0].baryCentricPos3[1]*(vertexREG[2].color[lc] - vertexREG[0].color[lc]);
			//pixelStamp[0].color[lc] = pixelStamp[0].color[lc] / pixelStamp[0].pos4[3];
		}

		pixelStamp[1].pos4[0] = x+1;
		pixelStamp[1].pos4[1] = y;
		pixelStamp[1].baryCentricPos3[0] = cornerTest[2][2]*area2Reciprocal;
		pixelStamp[1].baryCentricPos3[1] = cornerTest[2][0]*area2Reciprocal;
		pixelStamp[1].baryCentricPos3[2] = cornerTest[2][1]*area2Reciprocal;
		pixelStamp[1].pos4[2] = vertexREG[0].pos4[2] + pixelStamp[1].baryCentricPos3[0]*(vertexREG[1].pos4[2] - vertexREG[0].pos4[2])
								+ pixelStamp[1].baryCentricPos3[1]*(vertexREG[2].pos4[2] - vertexREG[0].pos4[2]);
		pixelStamp[1].pos4[3] = vertexREG[0].pos4[3] + pixelStamp[1].baryCentricPos3[0]*(vertexREG[1].pos4[3] - vertexREG[0].pos4[3])
								+ pixelStamp[1].baryCentricPos3[1]*(vertexREG[2].pos4[3] - vertexREG[0].pos4[3]);
		pixelStamp[1].texU[0] = vertexREG[0].TexU[0] + pixelStamp[1].baryCentricPos3[0]*(vertexREG[1].TexU[0] - vertexREG[0].TexU[0])
								+ pixelStamp[1].baryCentricPos3[1]*(vertexREG[2].TexU[0] - vertexREG[0].TexU[0]);
		pixelStamp[1].texV[0] = vertexREG[0].TexV[0] + pixelStamp[1].baryCentricPos3[0]*(vertexREG[1].TexV[0] - vertexREG[0].TexV[0])
								+ pixelStamp[1].baryCentricPos3[1]*(vertexREG[2].TexV[0] - vertexREG[0].TexV[0]);
		for (lc=0; lc<4; lc++) {
			pixelStamp[1].color[lc] = vertexREG[0].color[lc] + pixelStamp[1].baryCentricPos3[0]*(vertexREG[1].color[lc] - vertexREG[0].color[lc])
									  + pixelStamp[1].baryCentricPos3[1]*(vertexREG[2].color[lc] - vertexREG[0].color[lc]);
			//pixelStamp[1].color[lc] = pixelStamp[1].color[lc] / pixelStamp[1].pos4[3];
		}

		pixelStamp[2].pos4[0] = x;
		pixelStamp[2].pos4[1] = y+1;
		pixelStamp[2].baryCentricPos3[0] = cornerTest[5][2]*area2Reciprocal;
		pixelStamp[2].baryCentricPos3[1] = cornerTest[5][0]*area2Reciprocal;
		pixelStamp[2].baryCentricPos3[2] = cornerTest[5][1]*area2Reciprocal;
		pixelStamp[2].pos4[2] = vertexREG[0].pos4[2] + pixelStamp[2].baryCentricPos3[0]*(vertexREG[1].pos4[2] - vertexREG[0].pos4[2])
								+ pixelStamp[2].baryCentricPos3[1]*(vertexREG[2].pos4[2] - vertexREG[0].pos4[2]);
		pixelStamp[2].pos4[3] = vertexREG[0].pos4[3] + pixelStamp[2].baryCentricPos3[0]*(vertexREG[1].pos4[3] - vertexREG[0].pos4[3])
								+ pixelStamp[2].baryCentricPos3[1]*(vertexREG[2].pos4[3] - vertexREG[0].pos4[3]);
		pixelStamp[2].texU[0] = vertexREG[0].TexU[0] + pixelStamp[2].baryCentricPos3[0]*(vertexREG[1].TexU[0] - vertexREG[0].TexU[0])
								+ pixelStamp[2].baryCentricPos3[1]*(vertexREG[2].TexU[0] - vertexREG[0].TexU[0]);
		pixelStamp[2].texV[0] = vertexREG[0].TexV[0] + pixelStamp[2].baryCentricPos3[0]*(vertexREG[1].TexV[0] - vertexREG[0].TexV[0])
								+ pixelStamp[2].baryCentricPos3[1]*(vertexREG[2].TexV[0] - vertexREG[0].TexV[0]);
		for (lc=0; lc<4; lc++) {
			pixelStamp[2].color[lc] = vertexREG[0].color[lc] + pixelStamp[2].baryCentricPos3[0]*(vertexREG[1].color[lc] - vertexREG[0].color[lc])
									  + pixelStamp[2].baryCentricPos3[1]*(vertexREG[2].color[lc] - vertexREG[0].color[lc]);
			//pixelStamp[2].color[lc] = pixelStamp[2].color[lc] / pixelStamp[2].pos4[3];
		}

		pixelStamp[3].pos4[0] = x+1;
		pixelStamp[3].pos4[1] = y+1;
		pixelStamp[3].baryCentricPos3[0] = cornerTest[7][2]*area2Reciprocal;
		pixelStamp[3].baryCentricPos3[1] = cornerTest[7][0]*area2Reciprocal;
		pixelStamp[3].baryCentricPos3[2] = cornerTest[7][1]*area2Reciprocal;
		pixelStamp[3].pos4[2] = vertexREG[0].pos4[2] + pixelStamp[3].baryCentricPos3[0]*(vertexREG[1].pos4[2] - vertexREG[0].pos4[2])
								+ pixelStamp[3].baryCentricPos3[1]*(vertexREG[2].pos4[2] - vertexREG[0].pos4[2]);
		pixelStamp[3].pos4[3] = vertexREG[0].pos4[3] + pixelStamp[3].baryCentricPos3[0]*(vertexREG[1].pos4[3] - vertexREG[0].pos4[3])
								+ pixelStamp[3].baryCentricPos3[1]*(vertexREG[2].pos4[3] - vertexREG[0].pos4[3]);
		pixelStamp[3].texU[0] = vertexREG[0].TexU[0] + pixelStamp[3].baryCentricPos3[0]*(vertexREG[1].TexU[0] - vertexREG[0].TexU[0])
								+ pixelStamp[3].baryCentricPos3[1]*(vertexREG[2].TexU[0] - vertexREG[0].TexU[0]);
		pixelStamp[3].texV[0] = vertexREG[0].TexV[0] + pixelStamp[3].baryCentricPos3[0]*(vertexREG[1].TexV[0] - vertexREG[0].TexV[0])
								+ pixelStamp[3].baryCentricPos3[1]*(vertexREG[2].TexV[0] - vertexREG[0].TexV[0]);
		for (lc=0; lc<4; lc++) {
			pixelStamp[3].color[lc] = vertexREG[0].color[lc] + pixelStamp[3].baryCentricPos3[0]*(vertexREG[1].color[lc] - vertexREG[0].color[lc])
									  + pixelStamp[3].baryCentricPos3[1]*(vertexREG[2].color[lc] - vertexREG[0].color[lc]);
			//pixelStamp[3].color[lc] = pixelStamp[3].color[lc] / pixelStamp[3].pos4[3];
		}

		texUdX = pixelStamp[1].texU[0] - pixelStamp[0].texU[0];
		texVdX = pixelStamp[1].texV[0] - pixelStamp[0].texV[0];
		texUdY = pixelStamp[2].texU[0] - pixelStamp[0].texU[0];
		texVdY = pixelStamp[2].texV[0] - pixelStamp[0].texV[0];
		WdX = pixelStamp[1].pos4[3] - pixelStamp[0].pos4[3];
		WdY = pixelStamp[2].pos4[3] - pixelStamp[0].pos4[3];

		pixelStamp[0].texU[0] = pixelStamp[0].texU[0] / pixelStamp[0].pos4[3];
		pixelStamp[1].texU[0] = pixelStamp[1].texU[0] / pixelStamp[1].pos4[3];
		pixelStamp[2].texU[0] = pixelStamp[2].texU[0] / pixelStamp[2].pos4[3];
		pixelStamp[3].texU[0] = pixelStamp[3].texU[0] / pixelStamp[3].pos4[3];
		pixelStamp[0].texV[0] = pixelStamp[0].texV[0] / pixelStamp[0].pos4[3];
		pixelStamp[1].texV[0] = pixelStamp[1].texV[0] / pixelStamp[1].pos4[3];
		pixelStamp[2].texV[0] = pixelStamp[2].texV[0] / pixelStamp[2].pos4[3];
		pixelStamp[3].texV[0] = pixelStamp[3].texV[0] / pixelStamp[3].pos4[3];

		pixelStamp[0].scaleFactorDuDx[0] = pixelStamp[1].scaleFactorDuDx[0]
										   = (pixelStamp[1].texU[0]-pixelStamp[0].texU[0])*texImage.width;
		pixelStamp[2].scaleFactorDuDx[0] = pixelStamp[3].scaleFactorDuDx[0]
										   = (pixelStamp[3].texU[0]-pixelStamp[2].texU[0])*texImage.width;
		pixelStamp[0].scaleFactorDvDx[0] = pixelStamp[1].scaleFactorDvDx[0]
										   = (pixelStamp[1].texV[0]-pixelStamp[0].texV[0])*texImage.height;
		pixelStamp[2].scaleFactorDvDx[0] = pixelStamp[3].scaleFactorDvDx[0]
										   = (pixelStamp[3].texV[0]-pixelStamp[2].texV[0])*texImage.height;
		pixelStamp[0].scaleFactorDuDy[0] = pixelStamp[2].scaleFactorDuDy[0]
										   = (pixelStamp[2].texU[0]-pixelStamp[0].texU[0])*texImage.width;
		pixelStamp[1].scaleFactorDuDy[0] = pixelStamp[3].scaleFactorDuDy[0]
										   = (pixelStamp[3].texU[0]-pixelStamp[1].texU[0])*texImage.width;
		pixelStamp[0].scaleFactorDvDy[0] = pixelStamp[2].scaleFactorDvDy[0]
										   = (pixelStamp[2].texV[0]-pixelStamp[0].texV[0])*texImage.height;
		pixelStamp[1].scaleFactorDvDy[0] = pixelStamp[3].scaleFactorDvDy[0]
										   = (pixelStamp[3].texV[0]-pixelStamp[1].texV[0])*texImage.height;

		if (cornerTest[0][0]>=0 && cornerTest[0][1]>=0 && cornerTest[0][2]>=0) {
			pixBuffer[pixBufferP] = pixelStamp[0];
#ifdef PIXEL_GENERATE_DEBUG
			fprintf(PIXEL_GENERATE_DEBUGfp,"P:(%3d,%3d), C:(%03x %03x %03x %4.2f), T:(%7.2f,%7.2f), SFX:(%4.2f,%4.2f), SFY:(%4.2f,%4.2f)\n",
					(int)pixBuffer[pixBufferP].pos4[0],(int)pixBuffer[pixBufferP].pos4[1],//pixBuffer[pixBufferP].pos4[2],
					(int)pixBuffer[pixBufferP].color[0],(int)pixBuffer[pixBufferP].color[1],(int)pixBuffer[pixBufferP].color[2],pixBuffer[pixBufferP].color[3],
					pixBuffer[pixBufferP].texU[0]*texImage.width,pixBuffer[pixBufferP].texV[0]*texImage.height,
					pixBuffer[pixBufferP].scaleFactorDuDx[0],pixBuffer[pixBufferP].scaleFactorDvDx[0],
					pixBuffer[pixBufferP].scaleFactorDuDy[0],pixBuffer[pixBufferP].scaleFactorDvDy[0]);
#endif
			pixBufferP++;
		}

		if (cornerTest[2][0]>=0 && cornerTest[2][1]>=0 && cornerTest[2][2]>=0) {
			pixBuffer[pixBufferP] = pixelStamp[1];
#ifdef PIXEL_GENERATE_DEBUG
			fprintf(PIXEL_GENERATE_DEBUGfp,"P:(%3d,%3d), C:(%03x %03x %03x %4.2f), T:(%7.2f,%7.2f), SFX:(%4.2f,%4.2f), SFY:(%4.2f,%4.2f)\n",
					(int)pixBuffer[pixBufferP].pos4[0],(int)pixBuffer[pixBufferP].pos4[1],//pixBuffer[pixBufferP].pos4[2],
					(int)pixBuffer[pixBufferP].color[0],(int)pixBuffer[pixBufferP].color[1],(int)pixBuffer[pixBufferP].color[2],pixBuffer[pixBufferP].color[3],
					pixBuffer[pixBufferP].texU[0]*texImage.width,pixBuffer[pixBufferP].texV[0]*texImage.height,
					pixBuffer[pixBufferP].scaleFactorDuDx[0],pixBuffer[pixBufferP].scaleFactorDvDx[0],
					pixBuffer[pixBufferP].scaleFactorDuDy[0],pixBuffer[pixBufferP].scaleFactorDvDy[0]);
#endif
			pixBufferP++;
		}

		if (cornerTest[5][0]>=0 && cornerTest[5][1]>=0 && cornerTest[5][2]>=0) {
			pixBuffer[pixBufferP] = pixelStamp[2];
#ifdef PIXEL_GENERATE_DEBUG
			fprintf(PIXEL_GENERATE_DEBUGfp,"P:(%4d,%4d), C:(%03x %03x %03x %4.2f), T:(%7.2f,%7.2f), SFX:(%4.2f,%4.2f), SFY:(%4.2f,%4.2f)\n",
					(int)pixBuffer[pixBufferP].pos4[0],(int)pixBuffer[pixBufferP].pos4[1],//pixBuffer[pixBufferP].pos4[2],
					(int)pixBuffer[pixBufferP].color[0],(int)pixBuffer[pixBufferP].color[1],(int)pixBuffer[pixBufferP].color[2],pixBuffer[pixBufferP].color[3],
					pixBuffer[pixBufferP].texU[0]*texImage.width,pixBuffer[pixBufferP].texV[0]*texImage.height,
					pixBuffer[pixBufferP].scaleFactorDuDx[0],pixBuffer[pixBufferP].scaleFactorDvDx[0],
					pixBuffer[pixBufferP].scaleFactorDuDy[0],pixBuffer[pixBufferP].scaleFactorDvDy[0]);
#endif
			pixBufferP++;
		}

		if (cornerTest[7][0]>=0 && cornerTest[7][1]>=0 && cornerTest[7][2]>=0) {
			pixBuffer[pixBufferP] = pixelStamp[3];
#ifdef PIXEL_GENERATE_DEBUG
			fprintf(PIXEL_GENERATE_DEBUGfp,"P:(%3d,%3d), C:(%03x %03x %03x %4.2f), T:(%7.2f,%7.2f), SFX:(%4.2f,%4.2f), SFY:(%4.2f,%4.2f)\n",
					(int)pixBuffer[pixBufferP].pos4[0],(int)pixBuffer[pixBufferP].pos4[1],//pixBuffer[pixBufferP].pos4[2],
					(int)pixBuffer[pixBufferP].color[0],(int)pixBuffer[pixBufferP].color[1],(int)pixBuffer[pixBufferP].color[2],pixBuffer[pixBufferP].color[3],
					pixBuffer[pixBufferP].texU[0]*texImage.width,pixBuffer[pixBufferP].texV[0]*texImage.height,
					pixBuffer[pixBufferP].scaleFactorDuDx[0],pixBuffer[pixBufferP].scaleFactorDvDx[0],
					pixBuffer[pixBufferP].scaleFactorDuDy[0],pixBuffer[pixBufferP].scaleFactorDvDy[0]);
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

		for(lc=0; lc<3; lc++) {
			Zone[0][lc] = cornerTest[0][lc]>=0 | cornerTest[1][lc]>=0 | cornerTest[3][lc]>=0 | centralTest[lc]>=0;
			Zone[1][lc] = cornerTest[1][lc]>=0 | cornerTest[2][lc]>=0 | centralTest[lc]>=0 | cornerTest[4][lc]>=0;
			Zone[2][lc] = cornerTest[3][lc]>=0 | centralTest[lc]>=0 | cornerTest[5][lc]>=0 | cornerTest[6][lc]>=0;
			Zone[3][lc] = centralTest[lc]>=0 | cornerTest[4][lc]>=0 | cornerTest[6][lc]>=0 | cornerTest[7][lc]>=0;
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
			AlphaTest = pixBuffer[i].color[3] < AlphaRef;
		else if (AlphaTestMode == GL_EQUAL)
			AlphaTest = pixBuffer[i].color[3] == AlphaRef;
		else if (AlphaTestMode == GL_LEQUAL)
			AlphaTest = pixBuffer[i].color[3] <= AlphaRef;
		else if (AlphaTestMode == GL_GREATER)
			AlphaTest = pixBuffer[i].color[3] > AlphaRef;
		else if (AlphaTestMode == GL_NOTEQUAL)
			AlphaTest = pixBuffer[i].color[3] != AlphaRef;
		else if (AlphaTestMode == GL_GEQUAL)
			AlphaTest = pixBuffer[i].color[3] >= AlphaRef;
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
			DepthTest = pixBuffer[i].pos4[2]  < DepthBuffer[(int)pixBuffer[i].pos4[1]][(int)pixBuffer[i].pos4[0]];
		else if (DepthTestMode == GL_EQUAL)
			DepthTest = pixBuffer[i].pos4[2] == DepthBuffer[(int)pixBuffer[i].pos4[1]][(int)pixBuffer[i].pos4[0]];
		else if (DepthTestMode == GL_LEQUAL)
			DepthTest = pixBuffer[i].pos4[2] <= DepthBuffer[(int)pixBuffer[i].pos4[1]][(int)pixBuffer[i].pos4[0]];
		else if (DepthTestMode == GL_GREATER)
			DepthTest = pixBuffer[i].pos4[2]  > DepthBuffer[(int)pixBuffer[i].pos4[1]][(int)pixBuffer[i].pos4[0]];
		else if (DepthTestMode == GL_NOTEQUAL)
			DepthTest = pixBuffer[i].pos4[2] != DepthBuffer[(int)pixBuffer[i].pos4[1]][(int)pixBuffer[i].pos4[0]];
		else if (DepthTestMode == GL_GEQUAL)
			DepthTest = pixBuffer[i].pos4[2] >= DepthBuffer[(int)pixBuffer[i].pos4[1]][(int)pixBuffer[i].pos4[0]];
		else if (DepthTestMode == GL_ALWAYS)
			DepthTest = true;
		else
			fprintf(stderr,"Wrong Depth Test mode!!\n");
		if (DepthTest == false)
			continue;
		else
			DepthBuffer[(int)pixBuffer[i].pos4[1]][(int)pixBuffer[i].pos4[0]] = pixBuffer[i].pos4[2];

		//Alpha blending

		ColorBuffer[(int)pixBuffer[i].pos4[1]][(int)pixBuffer[i].pos4[0]][0]
			= (int)pixBuffer[i].color[0];// R
		ColorBuffer[(int)pixBuffer[i].pos4[1]][(int)pixBuffer[i].pos4[0]][1]
			= (int)pixBuffer[i].color[1];// G
		ColorBuffer[(int)pixBuffer[i].pos4[1]][(int)pixBuffer[i].pos4[0]][2]
			= (int)pixBuffer[i].color[2];// B
	}
}

Rasterizer::Rasterizer()
{
	int i,j;
	for (i = 0; i < TEX_CACHE_ENTRY_X*TEX_CACHE_ENTRY_Y; i++)
		TexCache.valid[i] = false;
	for (j = 0; j < HEIGHT; j++)
		for (i = 0; i < WIDTH; i++) {
			ColorBuffer[j][i][0] = 0;
			ColorBuffer[j][i][1] = 0;
			ColorBuffer[j][i][2] = 0;
			ColorBuffer[j][i][3] = 0;
			DepthBuffer[j][i] = 255;
		}

	for (i = 0; i < 4; i++) {
		FogColor[i] = 0;
		TexEnvColor[i] = 0;
		ColorClearVal[i] = 0;
	}

	TexCache.TexCacheHit = 0;
	TexCache.TexCacheMiss = 0;
	TexCache.TexCacheColdMiss = 0;

	AlphaRef = 0;
	DepthRef = 255;

	TexMinFilterMode = GL_NEAREST;
	TexMaxFilterMode = GL_NEAREST;
	TexWrapModeS = GL_REPEAT;
	TexWrapModeT = GL_REPEAT;
	TexEnvMode = GL_MODULATE;
	AlphaTestMode = GL_ALWAYS;
	DepthTestMode = GL_LESS;
	TexMappingEn = false;
	AlphaBlendingEn = false;
	FogEn = false;

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
			putc (WIDTH&0x000000FF, CLRfp);
			break;
		case 0x13:
			putc ((WIDTH>>8)&0x000000FF, CLRfp);
			break;
		case 0x14:
			putc ((WIDTH>>16)&0x000000FF, CLRfp);
			break;
		case 0x15:
			putc ((WIDTH>>24)&0x000000FF, CLRfp);
			break;
		case 0x16:
			putc (HEIGHT&0x000000FF, CLRfp);
			break;
		case 0x17:
			putc ((HEIGHT>>8)&0x000000FF, CLRfp);
			break;
		case 0x18:
			putc ((HEIGHT>>16)&0x000000FF, CLRfp);
			break;
		case 0x19:
			putc ((HEIGHT>>24)&0x000000FF, CLRfp);
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

	for (y=0; y<HEIGHT; y++)
		for (x=0; x<WIDTH; x++) {
			putc((int)ColorBuffer[y][x][2], CLRfp);// B
			putc((int)ColorBuffer[y][x][1], CLRfp);// G
			putc((int)ColorBuffer[y][x][0], CLRfp);// R
		}

	fclose(CLRfp);
}

