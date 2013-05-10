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

using namespace std;
Rasterizer rm;

void Rasterizer::TriangleSetup()
{
	float constantC;

	Edge[0][0] = vertexREG[0].pos4[1] - vertexREG[1].pos4[1];
	Edge[0][1] = vertexREG[0].pos4[0] - vertexREG[1].pos4[0];
	Edge[1][0] = vertexREG[1].pos4[1] - vertexREG[2].pos4[1];
	Edge[1][1] = vertexREG[1].pos4[0] - vertexREG[2].pos4[0];
	Edge[2][0] = vertexREG[2].pos4[1] - vertexREG[0].pos4[1];
	Edge[2][1] = vertexREG[2].pos4[0] - vertexREG[0].pos4[0];

	constantC = Edge[0][1]*Edge[1][0] - Edge[0][0]*Edge[1][1];
	area2Reciprocal = 1/constantC;

	LY = min(vertexREG[0].pos4[1], min(vertexREG[1].pos4[1], vertexREG[2].pos4[1]));
	LX = min(vertexREG[0].pos4[0], min(vertexREG[1].pos4[0], vertexREG[2].pos4[0]));
	HY = max(vertexREG[0].pos4[1], max(vertexREG[1].pos4[1], vertexREG[2].pos4[1]));
	RX = max(vertexREG[0].pos4[0], max(vertexREG[1].pos4[0], vertexREG[2].pos4[0]));
}

bool Rasterizer::Inside(int e,int a,int b)
{
	if (e < 0)
		return true;
	if (e > 0)
		return false;
	if (a > 0)
		return true;
	if (a < 0)
		return false;
	if (b > 0)
		return false;
	return false;
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

		TextureMapping();
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

/*
 * u,v - Texture coodinate in 2 dimension directions.
 * s,b,o - 3 block-based hirachy level, Super block, Block, Offset, in textrue coordinate.
 *
 * The following two function are to calculate 1D address and fetch data
 * in system memory from 6D block-based texture address.
 */
int Rasterizer::CalcTexAdd(short int us,short int ub,short int uo,short int vs,short int vb,short int vo,int level)
{
	return (vs*TEX_CACHE_BLOCK_SIZE_ROOT*TEX_CACHE_ENTRY_Y+vb*TEX_CACHE_BLOCK_SIZE_ROOT+vo)*(texImage.width>>level)+
		   us*TEX_CACHE_BLOCK_SIZE_ROOT*TEX_CACHE_ENTRY_X+ub*TEX_CACHE_BLOCK_SIZE_ROOT+uo;
}

fixColor4 Rasterizer::GetTexColor(const unsigned short u, const unsigned short v, const unsigned int level)
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
	tag = (int)(((V_Super << 8)|(U_Super&0x00ff))<<4)|(level&0xf);
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
				texTmpPtr = texImage.data[level] + CalcTexAdd(U_Super,U_Block,i,V_Super,V_Block,j,level)*3;

				//printf("%d %x (%d,%d)\n",level,texImage.data[level],u,v);

				TexCache.color[pos_cache][j*TEX_CACHE_BLOCK_SIZE_ROOT+i].r = *texTmpPtr++;
				TexCache.color[pos_cache][j*TEX_CACHE_BLOCK_SIZE_ROOT+i].g = *texTmpPtr++;
				TexCache.color[pos_cache][j*TEX_CACHE_BLOCK_SIZE_ROOT+i].b = *texTmpPtr++;
				TexCache.color[pos_cache][j*TEX_CACHE_BLOCK_SIZE_ROOT+i].a = 0xff;
			}
		}
		return TexCache.color[pos_cache][pos_block];
	}
}

fixColor4 Rasterizer::BilinearFilter(float texU,float texV,int level)
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

	TexColor[0] = GetTexColor(texUC, texVC, level);
	TexColor[1] = GetTexColor((texUC+1>=texImage.width>>level)?texUC:texUC+1, texVC, level);
	TexColor[2] = GetTexColor(texUC, (texVC+1>=texImage.height>>level)?texVC:texVC+1, level);
	TexColor[3] = GetTexColor((texUC+1>=texImage.width>>level)?texUC:texUC+1, (texVC+1>=texImage.height>>level)?texVC:texVC+1, level);

	color = (TexColor[0]*(1-u_ratio) + TexColor[1]*u_ratio)*(1-v_ratio) + (TexColor[2]*(1-u_ratio) + TexColor[3]*u_ratio)*v_ratio;

	return color;
}

fixColor4  Rasterizer::TrilinearFilter(float texU, float texV, int level, float w_ratio)
{
	fixColor4 color[2];
	color[0] = BilinearFilter(texU,texV,level);
	color[1] = BilinearFilter(texU,texV,(level+1)<texImage.level?level+1:texImage.level);

	color[0] = color[0]*(1-w_ratio) + color[1]*w_ratio;

	return color[0];
}

void Rasterizer::TextureMapping()
{
	int i;
	float TexU, TexV;
	unsigned short TexUC, TexVC;
	float u_ratio, v_ratio, wx_ratio, wy_ratio, w_ratio;
	fixColor4 TexColor[8];  // 1st 2 3  2nd  6 7
	//     0 1       4 5
	fixColor4 color, colorNext;
	int LoDx,LoDy,LoD;

#ifdef TEXDEBUG
	fprintf(TEXDEBUGfp,"\nXXX--YYY--UUU.UU--VVV.VV----------------\n");
#endif
	for (i = 0; i < pixBufferP; i++) {
		//find absolutely position in texture image
		TexU = pixBuffer[i].texU[0]*texImage.width;
		TexV = pixBuffer[i].texV[0]*texImage.height;

		wx_ratio = frexp(max(pixBuffer[i].scaleFactorDuDx[0],pixBuffer[i].scaleFactorDvDx[0]), &LoDx);
		wy_ratio = frexp(max(pixBuffer[i].scaleFactorDuDy[0],pixBuffer[i].scaleFactorDvDy[0]), &LoDy);
//        if ((pixBuffer[i].pos4[0] == 340) & (pixBuffer[i].pos4[1] == 200)){
//            printf("%d %d %f %f \n",LoDx,LoDy,wx_ratio,wy_ratio);
//        }
		wx_ratio = wx_ratio*2-1;
		wy_ratio = wy_ratio*2-1;
		LoD = max(LoDx,LoDy);
		LoD--;
		w_ratio = (max(pixBuffer[i].scaleFactorDuDx[0],pixBuffer[i].scaleFactorDvDx[0]) > max(pixBuffer[i].scaleFactorDuDy[0],pixBuffer[i].scaleFactorDvDy[0]))?wx_ratio:wy_ratio;

///********* Texture Wrap mode ***************************
		if (TexWrapModeS == GL_REPEAT)
			TexU = fmod(TexU,texImage.width);
		//fmod: mod in floating point format, %(mod) can only be used under integer format
		else if (TexWrapModeS == GL_CLAMP_TO_EDGE)
			TexU = (TexU < texImage.width-1)?((TexU > 0)?TexU:0):texImage.width-1;
		//0 <= TexU <= TexWidth-1
		else
			fprintf(stderr,"Wrong Texture Wrap mode in x-axis!!");

		if (TexWrapModeT == GL_REPEAT)
			TexV = fmod(TexV,texImage.height);
		else if (TexWrapModeT == GL_CLAMP_TO_EDGE)
			TexV = (TexV < texImage.height-1)?((TexV > 0)?TexV:0):texImage.height-1;
		//0 <= TexV <= TexHeight-1
		else
			fprintf(stderr,"Wrong Texture Wrap mode %x in y-axis!!\n",TexWrapModeT);
///*******************************************************

		TexUC = (unsigned short)floor(TexU);// floor: Round down value
		TexVC = (unsigned short)floor(TexV);

		if(LoD>0) {
			switch (TexMinFilterMode) {
			case GL_NEAREST:    //u,v nearest filter
				TexColor[0] = GetTexColor(TexUC, TexVC, 0);
				color = TexColor[0];
				break;
			case GL_LINEAR:     //u,v bilinear filter
				color = BilinearFilter(TexU, TexV, 0);
				break;
			case GL_NEAREST_MIPMAP_NEAREST: //u,v,w nearest filter
				TexUC = TexUC >> LoD;
				TexVC = TexVC >> LoD;

				TexColor[0] = GetTexColor(TexUC, TexVC, LoD);

				color = TexColor[0];
				break;
			case GL_LINEAR_MIPMAP_NEAREST:  //u,v bilinear, w nearest filter
				color = BilinearFilter(TexU,TexV,LoD);
				break;
			case GL_NEAREST_MIPMAP_LINEAR:  //u,v nearest, w linear filter
				TexUC = TexUC >> LoD;
				TexVC = TexVC >> LoD;

				TexColor[0] = GetTexColor(TexUC, TexVC, LoD);
				TexColor[1] = GetTexColor(TexUC>>1, TexVC>>1, LoD+1);

				color = TexColor[0]*(1-w_ratio) + TexColor[1]*w_ratio;
				break;
			case GL_LINEAR_MIPMAP_LINEAR:   //u,v,w trilinear filter
				color = TrilinearFilter(TexU, TexV, LoD, w_ratio);
				break;
			case GL_ANISOTROPIC:
				float r1,r2,r3,r4;

				r1 = sqrt(pixBuffer[i].scaleFactorDuDx[0]*pixBuffer[i].scaleFactorDuDx[0]+pixBuffer[i].scaleFactorDvDx[0]*pixBuffer[i].scaleFactorDvDx[0]);
				r2 = sqrt(pixBuffer[i].scaleFactorDuDy[0]*pixBuffer[i].scaleFactorDuDy[0]+pixBuffer[i].scaleFactorDvDy[0]*pixBuffer[i].scaleFactorDvDy[0]);

				r3 = max(r1,r2);
				r4 = min(r1,r2);
				if ((r3/r4) > 2.0f) {
					LoD = (LoD - 1)>0?LoD - 1:0;

					color = TrilinearFilter(fabs(TexU-(pixBuffer[i].scaleFactorDuDx[0]+pixBuffer[i].scaleFactorDuDy[0])/2),
											fabs(TexV-(pixBuffer[i].scaleFactorDvDx[0]+pixBuffer[i].scaleFactorDvDy[0])/2),LoD,w_ratio);
					colorNext = TrilinearFilter(fabs(TexU+(pixBuffer[i].scaleFactorDuDx[0]+pixBuffer[i].scaleFactorDuDy[0])/2),
												fabs(TexV+(pixBuffer[i].scaleFactorDvDx[0]+pixBuffer[i].scaleFactorDvDy[0])/2),LoD,w_ratio);

					color = color/2 + colorNext/2;
				} else
					color = TrilinearFilter(TexU, TexV, LoD, w_ratio);

				break;
			default:
				fprintf(stderr,"Texture filter mode is not supported!!");
				break;
			}
		} else {
			switch (TexMaxFilterMode) {
			case GL_NEAREST:    //u,v nearest filter
				TexColor[0] = GetTexColor(TexUC, TexVC ,0);
				color = TexColor[0];
				break;
			case GL_LINEAR:     //u,v bilinear filter
				color = BilinearFilter(TexU,TexV,0);
				break;
			case GL_NEAREST_MIPMAP_NEAREST: //u,v,w nearest filter
				TexUC = TexUC >> LoD;
				TexVC = TexVC >> LoD;

				TexColor[0] = GetTexColor(TexUC, TexVC ,LoD);

				color = TexColor[0];
				break;
			}
		}

#ifdef TEXDEBUG
		fprintf(TEXDEBUGfp,"%3d  %3d  %6.2f  %6.2f",(int)pixBuffer[i].pos4[0],(int)pixBuffer[i].pos4[1],TexU,TexV);
		fprintf(TEXDEBUGfp,"  %2x %2x %2x %2x",color.r,color.g,color.b,color.a);
		fprintf(TEXDEBUGfp,"  %2d %3.2f\n",LoD, w_ratio);
#endif

		///********** Texture Environment mode ***********
		switch (TexEnvMode) {
		case GL_MODULATE:
			pixBuffer[i].color[0] = (int)(pixBuffer[i].color[0]*color.r)>>8;
			pixBuffer[i].color[1] = (int)(pixBuffer[i].color[1]*color.g)>>8;
			pixBuffer[i].color[2] = (int)(pixBuffer[i].color[2]*color.b)>>8;
			//pixBuffer[i][11] = (int)(pixBuffer[i][11]*color[3])>>8;
			break;
		case GL_REPLACE:
			pixBuffer[i].color[0] = color.r;
			pixBuffer[i].color[1] = color.g;
			pixBuffer[i].color[2] = color.b;
			//pixBuffer[i][11] = color[3];
			break;
		case GL_DECAL:
			pixBuffer[i].color[0] = pixBuffer[i].color[0]*(1-color.a)+color.r*color.a;
			pixBuffer[i].color[1] = pixBuffer[i].color[1]*(1-color.a)+color.g*color.a;
			pixBuffer[i].color[2] = pixBuffer[i].color[2]*(1-color.a)+color.b*color.a;
			break;
		case GL_ADD:
			pixBuffer[i].color[0] = ((pixBuffer[i].color[0]+color.r) > 255)?255:(pixBuffer[i].color[0]+color.r);
			pixBuffer[i].color[1] = ((pixBuffer[i].color[1]+color.g) > 255)?255:(pixBuffer[i].color[1]+color.g);
			pixBuffer[i].color[2] = ((pixBuffer[i].color[2]+color.b) > 255)?255:(pixBuffer[i].color[2]+color.b);
			break;
		case GL_BLEND:
			pixBuffer[i].color[0] = (int)(pixBuffer[i].color[0]*(255-color.r))>>8 + ((color.r*TexEnvColor[0])>>8);
			pixBuffer[i].color[1] = (int)(pixBuffer[i].color[1]*(255-color.g))>>8 + ((color.g*TexEnvColor[1])>>8);
			pixBuffer[i].color[2] = (int)(pixBuffer[i].color[2]*(255-color.b))>>8 + ((color.b*TexEnvColor[2])>>8);
			break;
		default:
			fprintf(stderr,"Texture environment mode is not supported!!");
			break;
		}
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

