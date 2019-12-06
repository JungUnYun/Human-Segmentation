// HW#7 22181250 윤정언
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

extern "C" void gpu_Gabor(float *pcuSrc, float *pcuDst, int w, int h, float *cuGkernel, int kernel_size);

__global__ void cuda_Filter2D(float * pSrcImage, int SrcWidth,
	int SrcHeight, float *pKernel, int KWidth, int KHeight, float *pDstImage)
{
	int x = blockIdx.x*blockDim.x + threadIdx.x;
	int y = blockIdx.y*blockDim.y + threadIdx.y;
	int index = y*SrcWidth + x;
	int border;
	float temp;
	// 
	if (x > KWidth / 2 && y > (KHeight / 2) && x < (SrcWidth - KWidth / 2) 
		&& y < (SrcHeight - KHeight / 2))
	{
		temp = 0;
		for (int i = 0; i < KHeight; i++)
		{
			for (int j = 0; j < KWidth; j++)
			{
				border = (y + i)*SrcWidth + (x + j);
				temp += (pSrcImage[border] * pKernel[i*KWidth + j]);
			}
		}
		pDstImage[index] = temp;
//		__syncthreads();
	}
	else
	{
		pDstImage[index] = 0;
	}

}

__global__ void cuda_Shared_Filter2D(float * pSrcImage, int SrcWidth,
	int SrcHeight, float *pKernel, int KWidth, int KHeight, float *pDstImage)
{
	int x = blockIdx.x*blockDim.x + threadIdx.x;
	int y = blockIdx.y*blockDim.y + threadIdx.y;
	int index = y*SrcWidth + x;
	int border;

	float temp;
	int tx = threadIdx.x;
	int ty = threadIdx.y;
	extern __shared__ float gmat[];

	if (x > KWidth / 2 && y >(KHeight / 2) && x < (SrcWidth - KWidth / 2)
		&& y < (SrcHeight - KHeight / 2))
	{
		temp = 0;
		if (tx < KWidth&&ty < KHeight)
		{
			// shared memory를 쓰기위해 gmat으로 pKernel 한번에 읽어 준비함
			gmat[ty*KWidth + tx] = pKernel[ty*KWidth + tx];
		}

		for (int i = 0; i < KHeight; i++)
		{
			for (int j = 0; j < KWidth; j++)
			{
				border = (y + i)*SrcWidth + (x + j);
				temp += (pSrcImage[border] * gmat[i*KWidth + j]);
			}
		}
		pDstImage[index] = temp;
//		__syncthreads();
	}
	else
	{
		pDstImage[index] = 0;
	}

}


void gpu_Gabor(float *pcuSrc, float *pcuDst, int w, int h, float *cuGkernel, int kernel_size)
{
	// block 준비하고 block에 맞게 grid 나눔
	dim3 block = dim3(16, 16, 1); // 16  16  1 threads per block
	dim3 grid = dim3(h / block.x, w / block.y); // 32 *16 thread blocks
	
	cuda_Filter2D << < grid, block >> >(pcuSrc, w, h, cuGkernel, kernel_size, kernel_size, pcuDst);
//	cuda_Shared_Filter2D << < grid, block,sizeof(float)*kernel_size*kernel_size >> >(pcuSrc, w, h, cuGkernel, kernel_size, kernel_size, pcuDst);

	cudaThreadSynchronize();


	float *PrintKernel = new float[kernel_size*kernel_size];
	cudaMemcpy(PrintKernel, cuGkernel, kernel_size*kernel_size * sizeof(float), cudaMemcpyDeviceToHost);

	for (int i = 0; i<kernel_size; i++) {
		for (int j = 0; j<kernel_size; j++)
		{
			printf("%f\t", PrintKernel[i*kernel_size + j]);
		}
		printf("\n");
	}
}
