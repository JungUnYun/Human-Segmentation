#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <math.h>
#include <opencv\cv.h>
#include <opencv\highgui.h>

/*
extern "C" void draw(float *pcuSrc, float *pcuDst, int w, int h, float *cuGkernel, int kernel_size);
extern "C" __global__ void drawline(float *line , float *dot)
{

}
struct Point {
	float x;
	float y;
};
extern __host__ __device__ int		   abs(int) ;
extern __host__ __device__ float		   cos(int);
extern __device__ float sqrt(int);
__constant__ int point[8];
__global__ void historgram(float *buf, int x, int y ,unsigned short *histo)
{

}
__device__ Point distance(float x1,float y1, float x2, float y2,float x,float y)
{
	// get dot product of e1, e2
	int _ex1 = x2 - x1;
	int _ey1 = y2 - y1;
	int _ex2 = x - x1;
	int _ey2 = y - y1;
	float val = _ex1*_ex2 + _ey1*_ey2;
	float len = _ex1*_ex1 + _ey1*_ey1;
	float r1 = x1 + (val*_ex1) / len;
	float r2 = y1 + (val*_ey1) / len;
	//float dot = (float)(_ex1*_ex2 + _ey1*_ey2);
	//float len1 = sqrtf(_ex1*_ex1 + _ey1*_ey1);
	//float len2 = sqrtf(_ex2*_ex2 + _ey2*_ey2);
	//float cos = dot / (len1*len2);
	//float proj = cos*len2;
	//float r1 = x1 + (proj*_ex1) / len1;
	//float r2 = y1 + (proj*_ey1) / len1;
	Point ret;
	ret.x = r1;
	ret.y = r2;
	return ret;
}

__device__ bool isOnLine(float x1,float y1,float x2,float y2,float x, float y)
{
	Point e1;
	e1.x = x2 - x1;
	e1.y = y2 - y1;

	float rec = e1.x*e1.x + e1.y*e1.y;
	Point e2;
	e2.x = x - x1;
	e2.y = y - y1;
	float val = e1.x*e2.x + e1.y*e2.y;
	return (val >= 0 && val <= rec);

}
__device__ int cross2D(int x1,int y1,int x2,int y2)
{
	return x1*y2 - y1*x2;
}
__device__ int distance2D(int _x, int _y, int _x1, int _y1)
{
	
	return abs(cross2D(_x, _y, _x1, _y1)*cross2D(_x, _y, _x1, _y1)) / (_x1*_x1 + _y1*_y1);
}
__global__ void cuda_Filter2D(float * pSrcImage, int SrcWidth, int SrcHeight, float *pKernel, int KWidth, int KHeight, float *pDstImage)
{
	
	int x = blockIdx.x*blockDim.x + threadIdx.x;
	int y = blockIdx.y*blockDim.y + threadIdx.y;
	int index = y*SrcWidth + x;
	int border;
	float tempX,tempY,magnitude;
	bool a = true;

	int weightX[9] = {  -1,  0,  1 , -2,  0,  2 ,-1,  0,  1  };
	int weightY[9] = { 1,2,1,0,0,0,-1,-2,-1 };

	if (x>3 / 2 && y>3 / 2 && x < SrcWidth - 3 / 2 && y < SrcHeight - 3 / 2)
	{

		tempX = 0; tempY = 0;
		// make cuda code here !!!!!!!!!!!!!!!!!!!!!!!!!
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				border = (y + i)*SrcWidth + (x + j);
				tempX += (pSrcImage[border] * weightX[i*3 + j]);
				tempY += (pSrcImage[border] * weightY[i * 3 + j]);

			}
		}
		magnitude = sqrt(tempX*tempX + tempY*tempY)+0.5;
		
		pDstImage[index] = magnitude > 120 ? 2 : 255;
	}


	//int ret;
	//int x1 = pKernel[0];
	//int y1 = pKernel[1];
	//int x2 = pKernel[2];
	//int y2 = pKernel[3];


	//if (isOnLine(x1, y1, x2, y2, x, y)) {
	//	Point ret = distance(x1, y1, x2, y2, x, y);
	//	if ( ((ret.x-x)* (ret.x - x)+ (ret.y - y)* (ret.y - y)) < 100000) {
	//		int index_ret = (int)(ret.y*(float)SrcWidth + ret.x);
	//		pDstImage[index_ret] = 127;

	//		//if (abs(pSrcImage[index_ret] - pSrcImage[index])<=50)
	//			//pDstImage[index] = pSrcImage[index];
	//		//else
	//			//pDstImage[index] = 127;
	//	}
	//	else {
	//		pDstImage[index] = 127;

	//	}
	//}
	//else
	//{
	//	pDstImage[index] = pSrcImage[index];
	//}




}
__global__ void cuda_lowpass2D(float * pSrcImage, int SrcWidth, int SrcHeight, float *pKernel, int KWidth, int KHeight, float *pDstImage)
{
	float Kernel[25] = { 1 / 25.0,  1 / 25.0,  1 / 25.0,  1 / 25.0,  1 / 25.0, 
		1 / 25.0,  1 / 25.0,  1 / 25.0,  1 / 25.0,  1 / 25.0, 
		1 / 25.0,  1 / 25.0,  1 / 25.0,  1 / 25.0,  1 / 25.0, 
		1 / 25.0,  1 / 25.0,  1 / 25.0,  1 / 25.0,  1 / 25.0, 
		1 / 25.0,  1 / 25.0,  1 / 25.0,  1 / 25.0,  1 / 25.0 };
	int x = blockIdx.x*blockDim.x + threadIdx.x;
	int y = blockIdx.y*blockDim.y + threadIdx.y;
	int index = y*SrcWidth + x;
	int border;
	float tempX, tempY, magnitude;
	if (x>5 / 2 && y>5 / 2 && x < SrcWidth - 5 / 2 && y < SrcHeight - 5 / 2)
	{

		tempX = 0; tempY = 0;
		// make cuda code here !!!!!!!!!!!!!!!!!!!!!!!!!
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				border = (y + i)*SrcWidth + (x + j);
				tempX += (pSrcImage[border] * Kernel[i * 5 + j]);

			}
		}
		pDstImage[index] = tempX;
	}
	else {
		pDstImage[index] = pSrcImage[index];
	}
}
__global__ void line(int x0, int y0, int x1, int y1) {

	int dx = abs(x1 - x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy) / 2, e2;

	for (;;) {
		
		if (x0 == x1 && y0 == y1) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}
__global__ void cuda_full(float* pSrcImage, int w, int h, float *pKernel,float* pDstImage)
{
	int x = blockIdx.x*blockDim.x + threadIdx.x;
	int y = blockIdx.y*blockDim.y + threadIdx.y;
	int index = y*w + x;


	int ret;
	int x1 = pKernel[0];
	int y1 = pKernel[1];
	int x2 = pKernel[2];
	int y2 = pKernel[3];
	bool k = false;
	short count = 0;
	if (isOnLine(x1, y1, x2, y2, x, y)) {
		Point ret = distance(x1, y1, x2, y2, x, y);
		int x0 = (int)ret.x;
		int y0 = (int)ret.y;
		if ( ((x0-x)* (x0 - x)+ (y0 - y)* (y0 - y)) < 100000) {
			int dx = abs(x - x0), sx = x0 < x ? 1 : -1;
			int dy = abs(y - y0), sy = y0 < y ? 1 : -1;
			int err = (dx>dy ? dx : -dy) / 2, e2;

			for (;;) {
				if (pSrcImage[y0*w + x0] == 2 )
				{
					k = true;
					break;
				}
				if (x0 == x && y0 == y) break;
				e2 = err;
				if (e2 >-dx) { err -= dy; x0 += sx; }
				if (e2 < dy) { err += dx; y0 += sy; }
			}
			pDstImage[index] =2;
		}
		else {
			pDstImage[index] = pSrcImage[index];

		}
	}
	else
	{
		pDstImage[index] = pSrcImage[index];
	}
	if(k)
		pDstImage[index] = pSrcImage[index];



}


void draw(float *pcuSrc, float *pcuDst, int w, int h, float *cuGkernel, int kernel_size)
{
	dim3 block = dim3(32, 32, 1);
	dim3 grid = dim3(w / block.x, h / block.y);

	cuda_Filter2D <<<grid, block >>> (pcuSrc, w, h, cuGkernel, kernel_size, kernel_size, pcuDst);
	cuda_full << <grid, block >> > (pcuDst, w, h,cuGkernel,pcuSrc);
	cudaThreadSynchronize();

}
*/

extern "C" void sub(float**pcuSrc, int w, int h, float *pcuDst, float *bmask, int *pPoint, float *temp);

extern "C" __global__ void drawline(float *line, float *dot)
{

}
struct Point {
	float x;
	float y;
};
extern __host__ __device__ int         abs(int);
extern __host__ __device__ float         cos(int);
extern __device__ float sqrt(int);
extern __device__ float sqrtf(float);

__constant__ int point[8];
__global__ void historgram(float *buf, int x, int y, unsigned short *histo)
{

}
__device__ Point distance(float x1, float y1, float x2, float y2, float x, float y)
{
	// get dot product of e1, e2
	int _ex1 = x2 - x1;
	int _ey1 = y2 - y1;
	int _ex2 = x - x1;
	int _ey2 = y - y1;
	float val = _ex1*_ex2 + _ey1*_ey2;
	float len = _ex1*_ex1 + _ey1*_ey1;

	float r1 = x1 + (val*_ex1) / len;
	float r2 = y1 + (val*_ey1) / len;

	Point ret;
	ret.x = r1;
	ret.y = r2;
	return ret;
}

__device__ bool isOnLine(float x1, float y1, float x2, float y2, float x, float y)
{
	Point e1;
	e1.x = x2 - x1;
	e1.y = y2 - y1;

	float rec = e1.x*e1.x + e1.y*e1.y;
	Point e2;
	e2.x = x - x1;
	e2.y = y - y1;
	float val = e1.x*e2.x + e1.y*e2.y;
	return (val >= 0 && val <= rec);

}

__global__ void cuda_low2D(float * src0, float * src1, float * src2, float * src3, float * src4, float * src5, float * src6, float * src7, float * src8, float * src9, int w, int h, float *pDstImage)
{

	int x = blockIdx.x*blockDim.x + threadIdx.x;
	int y = blockIdx.y*blockDim.y + threadIdx.y;
	int index = y*w + x;
	int border;
	int count = 0;
	float temp[10] = { 0 };
	if (x>3 / 2 && y>3 / 2 && x < w - 3 / 2 && y < h - 3 / 2)
	{

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				border = (y + i)*w + (x + j);
				temp[0] += src0[border] * 1 / 9.0;
				temp[1] += src1[border] * 1 / 9.0;
				temp[2] += src2[border] * 1 / 9.0;
				temp[3] += src3[border] * 1 / 9.0;
				temp[4] += src4[border] * 1 / 9.0;
				temp[5] += src5[border] * 1 / 9.0;
				temp[6] += src6[border] * 1 / 9.0;
				temp[7] += src7[border] * 1 / 9.0;
				temp[8] += src8[border] * 1 / 9.0;
				temp[9] += src9[border] * 1 / 9.0;

			}
		}
		src0[index] = temp[0];
		src1[index] = temp[1];
		src2[index] = temp[2];
		src3[index] = temp[3];
		src4[index] = temp[4];
		src5[index] = temp[5];
		src6[index] = temp[6];
		src7[index] = temp[7];
		src8[index] = temp[8];
		src9[index] = temp[9];


		pDstImage[index] = temp[4];
	}
	else {
		pDstImage[index] = src4[0];
	}

}
__global__ void cuda_back(float * src0, float * src1, float * src2, float * src3, float * src4, float * src5, float * src6, float * src7, float * src8, float * src9, int w, int h, float *pDstImage)
{

	int x = blockIdx.x*blockDim.x + threadIdx.x;
	int y = blockIdx.y*blockDim.y + threadIdx.y;
	int index = y*w + x;
	int border;
	int count = 0;
	int thes = 20;
	if (abs(src4[index] - src1[index])<thes)
		count++;
	if (abs(src4[index] - src2[index])<thes)
		count++;
	if (abs(src4[index] - src3[index])<thes)
		count++;
	if (abs(src4[index] - src4[index])<thes)
		count++;
	if (abs(src4[index] - src5[index])<thes)
		count++;
	if (abs(src4[index] - src6[index])<thes)
		count++;
	if (abs(src4[index] - src7[index])<thes)
		count++;
	if (abs(src4[index] - src8[index])<thes)
		count++;
	if (abs(src4[index] - src9[index])<thes)
		count++;

	if (count > 7)
		pDstImage[index] = 255 - 255 / count;
	else
		pDstImage[index] = 0;

}
__global__ void cuda_sobel2D(float *src0, float *bmask, int w, int h, float *pdst, int *pPoint)
{
	//int pPoint[26] = { 846,510,866,676,747,686,951,676,776,824,976,799,863,903,761,941,985,872,834,1111,903,1122,861,1326,912,1293 };
	int point[14][2] = { 0 };
	for (int i = 0; i < 14; i++)
	{
		point[i][0] = pPoint[i * 2 + 0];
		point[i][1] = pPoint[i * 2 + 1];
	}
	int min_x = 288, min_y = 512, max_x = 0, max_y = 0;
	for (int i = 0; i < 14; i++)
	{
		if (min_x > point[i][0])
		{
			min_x = point[i][0];
		}
		if (min_y > point[i][1])
		{
			min_y = point[i][1];
		}

		if (max_x < point[i][0])
			max_x = point[i][0];

		if (max_y < point[i][1])
			max_y = point[i][1];

	}
	int x = blockIdx.x*blockDim.x + threadIdx.x;
	int y = blockIdx.y*blockDim.y + threadIdx.y;
	int index = y*w + x;
	int border;
	float tempX, tempY, magnitude;
	bool a = true;

	int weightX[9] = { -1,  0,  1 , -2,  0,  2 ,-1,  0,  1 };
	int weightY[9] = { 1,2,1,0,0,0,-1,-2,-1 };
	if (x > min_x - 20 && x < max_x + 20 && y>min_y  && y<max_y + 20)
		if (x>3 / 2 && y>3 / 2 && x < w - 3 / 2 && y < h - 3 / 2)
		{
			if (abs(src0[index] - bmask[index]) >20) {
				tempX = 0; tempY = 0;
				// make cuda code here !!!!!!!!!!!!!!!!!!!!!!!!!
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						border = (y + i)*w + (x + j);
						tempX += (src0[border] * weightX[i * 3 + j]);
						tempY += (src0[border] * weightY[i * 3 + j]);

					}
				}
				magnitude = sqrt(tempX*tempX + tempY*tempY);
				pdst[index] = magnitude>15 ? magnitude : bmask[index];

			}
			else {
				pdst[index] = 0;
			}

		}
		else {
			pdst[index] = 0;
		}
	else
	{
		pdst[index] = 0;
	}

}
__global__ void cuda_draw(float *src0, int w, int h, float *pdst, int* pPoint)
{
	//int pPoint[26] = { 846,510,866,676,747,686,951,676,776,824,976,799,863,903,761,941,985,872,834,1111,903,1122,861,1326,912,1293 };
	int x = blockIdx.x*blockDim.x + threadIdx.x;
	int y = blockIdx.y*blockDim.y + threadIdx.y;
	int index = y*w + x;

	int point[14][2] = { 0 };
	for (int i = 0; i < 14; i++)
	{
		point[i][0] = pPoint[i * 2 + 0];
		point[i][1] = pPoint[i * 2 + 1];
	}
	int head[2] = { point[13][0],point[13][1] };
	int neck[2] = { point[12][0],point[12][1] };
	int heap[2] = { point[3][0],point[3][1] };
	int rsh[2] = { point[8][0],point[8][1] };
	int lsh[2] = { point[9][0],point[9][1] };
	int x1 = head[0];
	int y1 = head[1];
	int x2 = neck[0];
	int y2 = neck[1];
	bool k = false;
	short count = 0;
	int distance1 = (point[6][0] - point[7][0])*(point[6][0] - point[7][0]) + (point[6][1] - point[7][1])*(point[6][1] - point[7][1]);
	int d = 0;
	int d1 = (lsh[0] - rsh[0])*(lsh[0] - rsh[0]) + (lsh[1] - rsh[1])*(lsh[1] - rsh[1]);
	int d2 = (head[0] - neck[0])*(head[0] - neck[0]) + (head[1] - neck[1])*(head[1] - neck[1]);
	if (d1 > d2)
		d = d1;
	else
		d = d2;
	for (int i = 0; i < 13; i++)
	{
		if (i >= 0 && i<5) {
			x1 = point[i][0];
			y1 = point[i][1];
			x2 = point[i + 1][0];
			y2 = point[i + 1][1];
			if (isOnLine(x1, y1, x2, y2, x, y)) {
				Point ret = distance(x1, y1, x2, y2, x, y);
				int x0 = (int)ret.x;
				int y0 = (int)ret.y;
				pdst[y0*w + x0] = 255;
				if (((x0 - x)* (x0 - x) + (y0 - y)* (y0 - y)) < distance1 / 16) {
					k = true;
				}

			}
			else if (((x1 - x)* (x1 - x) + (y1 - y)* (y1 - y)) <  distance1 / 8) {
				k = true;
			}
		}
		if (i == 5)
		{
			x1 = point[i][0];
			y1 = point[i][1];
			x2 = point[i + 1][0];
			y2 = point[i + 1][1];
			if (((x1 - x)* (x1 - x) + (y1 - y)* (y1 - y)) <  distance1 / 8) {
				k = true;
			}
		}
		if (i >= 6 && i <= 10)
		{
			x1 = point[i][0];
			y1 = point[i][1];
			x2 = point[i + 1][0];
			y2 = point[i + 1][1];
			if (isOnLine(x1, y1, x2, y2, x, y)) {
				Point ret = distance(x1, y1, x2, y2, x, y);
				int x0 = (int)ret.x;
				int y0 = (int)ret.y;
				pdst[y0*w + x0] = 255;

				if (((x0 - x)* (x0 - x) + (y0 - y)* (y0 - y)) < distance1 / 16) {
					k = true;
				}

			}
			else if (((x1 - x)* (x1 - x) + (y1 - y)* (y1 - y)) <  distance1 / 16) {
				k = true;
			}
		}

		if (i == 12)
		{
			x1 = point[i][0];
			y1 = point[i][1];
			x2 = point[i + 1][0];
			y2 = point[i + 1][1];
			int x0 = (x1 + x2) / 2;
			int y0 = (y1 + y2) / 2;
			if (((x0 - x)* (x0 - x) + (y0 - y)* (y0 - y)) < ((x2 - x1)* (x2 - x1) + (y2 - y1)* (y2 - y1)) / 4) {
				k = true;
			}

		}

	}

	x1 = neck[0];
	y1 = neck[1];
	x2 = heap[0];
	y2 = heap[1];
	if (isOnLine(x1, y1, x2, y2, x, y)) {
		Point ret = distance(x1, y1, x2, y2, x, y);
		int x0 = (int)ret.x;
		int y0 = (int)ret.y;
		if (((x0 - x)* (x0 - x) + (y0 - y)* (y0 - y)) < d / 4) {
			k = true;
		}

	}
	else if (((x1 - x)* (x1 - x) + (y1 - y)* (y1 - y)) <  d / 4) {
		k = true;
	}


	if (k)
		pdst[index] = src0[index];
	else
		pdst[index] = 0;

}

void sub(float**pcuSrc, int w, int h, float *pcuDst, float *bmask, int *pPoint, float *temp)
{
	dim3 block = dim3(18, 32, 1);
	dim3 grid = dim3(w / block.x, h / block.y);
	cuda_low2D << <grid, block >> > (pcuSrc[0], pcuSrc[1], pcuSrc[2], pcuSrc[3], pcuSrc[4], pcuSrc[5], pcuSrc[6], pcuSrc[7], pcuSrc[8], pcuSrc[9], w, h, pcuDst);
	cuda_back << <grid, block >> > (pcuSrc[0], pcuSrc[1], pcuSrc[2], pcuSrc[3], pcuSrc[4], pcuSrc[5], pcuSrc[6], pcuSrc[7], pcuSrc[8], pcuSrc[9], w, h, bmask);
	cuda_sobel2D << <grid, block >> > (pcuSrc[4], bmask, w, h, temp, pPoint);
	cuda_draw << <grid, block >> > (temp, w, h, pcuDst, pPoint);
	cudaThreadSynchronize();
}