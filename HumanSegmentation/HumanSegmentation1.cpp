#include <windows.h>
#include "HumanSegmentation1.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

extern "C" __global__ void drawline(float *line, float *dot);
extern __host__ __device__ int		   abs(int);
extern __host__ __device__ float		   cos(int);
extern __device__ float sqrt(int);
extern "C" void draw(float *pcuSrc, float *pcuDst, int w, int h, float *cuGkernel, int kernel_size);
extern "C" void sub(float**pcuSrc, int w, int h, float *pcuDst, float *bmask, int *pPoint, float *temp);
struct Points {
	float x;
	float y;
};

Points distance(float x1, float y1, float x2, float y2, float x, float y)
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

	Points ret;
	ret.x = r1;
	ret.y = r2;
	return ret;
}

bool isOnLines(float x1, float y1, float x2, float y2, float x, float y)
{
	Points e1;
	e1.x = x2 - x1;
	e1.y = y2 - y1;

	float rec = e1.x*e1.x + e1.y*e1.y;
	Points e2;
	e2.x = x - x1;
	e2.y = y - y1;
	float val = e1.x*e2.x + e1.y*e2.y;
	return (val >= 0 && val <= rec);

}

void serial_draw(float *src0, int w, int h, float *pdst, int* pPoint)
{
	//int pPoint[26] = { 846,510,866,676,747,686,951,676,776,824,976,799,863,903,761,941,985,872,834,1111,903,1122,861,1326,912,1293 };
	int x = 288;
	int y = 512;

	for (y = 1; y < 512; y++) {
		for (x = 1; x < 288; x++) {
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
				if (i >= 0 && i < 5) {
					x1 = point[i][0];
					y1 = point[i][1];
					x2 = point[i + 1][0];
					y2 = point[i + 1][1];
					if (isOnLines(x1, y1, x2, y2, x, y)) {
						Points ret = distance(x1, y1, x2, y2, x, y);
						int x0 = (int)ret.x;
						int y0 = (int)ret.y;
						pdst[y0*w + x0] = 255;
						if (((x0 - x)* (x0 - x) + (y0 - y)* (y0 - y)) < distance1 / 16) {
							k = true;
						}

					}
					else if (((x1 - x)* (x1 - x) + (y1 - y)* (y1 - y)) < distance1 / 8) {
						k = true;
					}
				}
				if (i == 5)
				{
					x1 = point[i][0];
					y1 = point[i][1];
					x2 = point[i + 1][0];
					y2 = point[i + 1][1];
					if (((x1 - x)* (x1 - x) + (y1 - y)* (y1 - y)) < distance1 / 8) {
						k = true;
					}
				}
				if (i >= 6 && i <= 10)
				{
					x1 = point[i][0];
					y1 = point[i][1];
					x2 = point[i + 1][0];
					y2 = point[i + 1][1];
					if (isOnLines(x1, y1, x2, y2, x, y)) {
						Points ret = distance(x1, y1, x2, y2, x, y);
						int x0 = (int)ret.x;
						int y0 = (int)ret.y;
						pdst[y0*w + x0] = 255;

						if (((x0 - x)* (x0 - x) + (y0 - y)* (y0 - y)) < distance1 / 16) {
							k = true;
						}

					}
					else if (((x1 - x)* (x1 - x) + (y1 - y)* (y1 - y)) < distance1 / 16) {
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
			if (isOnLines(x1, y1, x2, y2, x, y)) {
				Points ret = distance(x1, y1, x2, y2, x, y);
				int x0 = (int)ret.x;
				int y0 = (int)ret.y;
				if (((x0 - x)* (x0 - x) + (y0 - y)* (y0 - y)) < d / 4) {
					k = true;
				}

			}
			else if (((x1 - x)* (x1 - x) + (y1 - y)* (y1 - y)) < d / 4) {
				k = true;
			}


			if (k)
				pdst[index] = src0[index];
			else
				pdst[index] = 0;
		}
	}
}

void serial_sobel2D(float *src0, float *bmask, int w, int h, float *pdst, int *pPoint)
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
	int x = 288;
	int y = 512;
	for (y = 1; y <= 512; y++) {
		for (x = 1; x <= 288; x++) {

			int index = y*w + x;
			int border;
			float tempX, tempY, magnitude;
			bool a = true;

			int weightX[9] = { -1,  0,  1 , -2,  0,  2 ,-1,  0,  1 };
			int weightY[9] = { 1,2,1,0,0,0,-1,-2,-1 };
			if (x > min_x - 20 && x < max_x + 20 && y>min_y  && y < max_y + 20)
				if (x > 3 / 2 && y > 3 / 2 && x < w - 3 / 2 && y < h - 3 / 2)
				{
					if (abs(src0[index] - bmask[index]) > 20) {
						tempX = 0; tempY = 0;
						// make serial code here !!!!!!!!!!!!!!!!!!!!!!!!!
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
						pdst[index] = magnitude > 15 ? magnitude : bmask[index];

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
	}
}

void serial_back(float * src0, float * src1, float * src2, float * src3, float * src4, float * src5, float * src6, float * src7, float * src8, float * src9, int w, int h, float *pDstImage)
{

	int x = 288;
	int y = 512;
	for (y = 1; y < 512; y++) {
		for (x = 1; x < 288; x++) {
			int index = y*w + x;
			int border;
			int count = 0;
			int thes = 20;
			if (abs(src4[index] - src1[index]) < thes)
				count++;
			if (abs(src4[index] - src2[index]) < thes)
				count++;
			if (abs(src4[index] - src3[index]) < thes)
				count++;
			if (abs(src4[index] - src4[index]) < thes)
				count++;
			if (abs(src4[index] - src5[index]) < thes)
				count++;
			if (abs(src4[index] - src6[index]) < thes)
				count++;
			if (abs(src4[index] - src7[index]) < thes)
				count++;
			if (abs(src4[index] - src8[index]) < thes)
				count++;
			if (abs(src4[index] - src9[index]) < thes)
				count++;

			if (count > 7)
				pDstImage[index] = 255 - 255 / count;
			else
				pDstImage[index] = 0;
		}
	}
}

void serial_low2D(float * src0, float * src1, float * src2, float * src3, float * src4, float * src5, float * src6, float * src7, float * src8, float * src9, int w, int h, float *pDstImage)
{

	int x = 288;
	int y = 512;
	for (y = 1; y < 512; y++) {
		for (x = 1; x < 288; x++) {
			int index = y*w + x;
			int border;
			int count = 0;
			float temp[10] = { 0 };
			if (x > 3 / 2 && y > 3 / 2 && x < w - 3 / 2 && y < h - 3 / 2)
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
	}
}

void subs(float**pcuSrc, int w, int h, float *pcuDst, float *bmask, int *pPoint, float *temp)
{
	//Thread 할당
	//dim3 block = dim3(18, 32, 1);
	//dim3 grid = dim3(w / block.x, h / block.y);
	// 10개 프레임씩 불러와서 처리
	serial_low2D(pcuSrc[0], pcuSrc[1], pcuSrc[2], pcuSrc[3], pcuSrc[4], pcuSrc[5], pcuSrc[6], pcuSrc[7], pcuSrc[8], pcuSrc[9], w, h, pcuDst);
	serial_back(pcuSrc[0], pcuSrc[1], pcuSrc[2], pcuSrc[3], pcuSrc[4], pcuSrc[5], pcuSrc[6], pcuSrc[7], pcuSrc[8], pcuSrc[9], w, h, bmask);
	////// 4번 프레임에 대해서 
	serial_sobel2D(pcuSrc[4], bmask, w, h, temp, pPoint);
	serial_draw(temp, w, h, pcuDst, pPoint);
	//cudaThreadSynchronize();
}

void HumanSegmentation1::sha_serial(int ind)
{
	FILE *f;
	int r, i = 0;
	float x, y, z;
	int point[28] = { 0 };

	char name[10];
	char file[10];
	float ** pSrc = new float*[10];
	for (int i = 0; i < 10; i++)
	{
		pSrc[i] = new float[512 * 288];
	}
	float * pDst = new float[512 * 288];
	int w = 288;
	int h = 512;
	int ws = 288;
	for (int k = 0; k<10; k++)
	{
		sprintf(name, "%03d.jpg", k + ind);
		if (k == 0)   printf("%s\n", name);
		IplImage* pInput = cvLoadImage(name, CV_LOAD_IMAGE_GRAYSCALE);
		int w = pInput->width;
		int ws = pInput->widthStep;
		int h = pInput->height;
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				pSrc[k][j*w + i] = unsigned char(pInput->imageData[j*ws + i]);

			}
		}
		if (k == 4) {
			sprintf(file, "%03d.txt", k + ind);
			f = fopen(file, "r");
			while ((r = fscanf(f, "%f %f %f ", &x, &y, &z)) != EOF) {
				point[i++] = int(x * 288 / 288);
				point[i++] = int(y * 512 / 512);
				z = 0;

			}
		}
	}
	float tStarts, tEnds;
	double ProTimes;
	tStarts = cvGetTickCount();
	float **pcuSrc = new float*[10];
	float *bmask;
	float *pcuDst;
	float *temp;
	int *pPoint;

	for (int i = 0; i<10; i++)
		pcuSrc[i] = (float*)malloc(w*h * sizeof(float));


	pPoint = (int*)malloc(28 * sizeof(int));
	pcuDst = (float*)malloc(w*h * sizeof(float));
	temp = (float*)malloc(w*h * sizeof(float));
	bmask = (float*)malloc(w*h * sizeof(float));

	for (int i = 0; i<10; i++)
		pcuSrc[i] = pSrc[i];


	pPoint = point;
	subs(pcuSrc, w, h, pcuDst, bmask, pPoint, temp);
	pDst = pcuDst;


	tEnds = cvGetTickCount();// for check processing
	ProTimes = 0.001 * (tEnds - tStarts) / cvGetTickFrequency(); // for msec
	CvSize cvsize1 = { w ,h };
	//IplImage* TempImage1 = cvCreateImage( cvsize1, IPL_DEPTH_32F, 1); 
	shape_sout = cvCreateImage(cvsize1, IPL_DEPTH_8U, 1);

	// copy to OpenCV
	for (int y = 0; y < cvsize1.height; y++) {
		for (int x = 0; x < cvsize1.width; x++) {

			cvSetReal2D(shape_sout, y, x, pDst[y*cvsize1.width + x]);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		delete(pSrc[i]);
		//free(pcuSrc[i]);
	}

	serialM = cvarrToMat(shape_sout);
	QImage shapeOutputserial = convertOpenCVMatToQtQImage(serialM).scaled(ui.label_shapeserial->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label_shapeserial->setPixmap(QPixmap::fromImage(shapeOutputserial));

	fpss = floor((1 / (ProTimes))*10000.f + 0.5) / 10000.f;
	QString fpsSs = QString::number(fpss);
	ui.textBrowser_fps_s->setText(fpsSs);

	delete(pDst);
}

HumanSegmentation1::HumanSegmentation1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QPixmap zoomicon("zoom.png");
	QIcon ZButtonICON(zoomicon);
	ui.input_z->setIcon(ZButtonICON);
	ui.shape_sz->setIcon(ZButtonICON);
	ui.shape_cz->setIcon(ZButtonICON);
	QPixmap developicon("developer.png");
	QIcon DButtonICON(developicon);
	ui.pushButton_info->setIcon(DButtonICON);
	QPixmap saveicon("save.png");
	QIcon SButtonICON(saveicon);
	ui.input_save->setIcon(SButtonICON);
	ui.shape_saveserial->setIcon(SButtonICON);
	ui.shape_saveCUDA->setIcon(SButtonICON);
	QPixmap pauseicon("play.png");
	QIcon PButtonICON(pauseicon);
	ui.pause->setIcon(PButtonICON);
}
// image load 함수
void HumanSegmentation1::LoadSource()
{
	if (isvideo && !pause)
		return;
	// load 할 때 팝업 생성
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Source File"), "",
		tr("input image (*.jpg *.png *.bmp *.tif)"));

	char* sourcename = strdup((fileName.toStdString()).c_str());
	src = imread(sourcename);

	// 만약에 파일 없으면 return
	if (src.data == NULL)
		return;

	isimage = true;
	isvideo = false;
	// src = mat BGR input, srcin = mat RGB input
	Mat srcin;
	cvtColor(src, srcin, CV_BGR2RGB);
	// srcI = iplimage src
	srcI = &IplImage(srcin);
	// h,w = src height, width
	ih = srcin.rows;
	iw = srcin.cols;
	// input display
	QImage qimgInput = convertOpenCVMatToQtQImage(srcin).scaled(ui.label_input->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label_input->setPixmap(QPixmap::fromImage(qimgInput));
	/*
	QImage qimgInput = convertOpenCVMatToQtQImage(srcin);
	ui.label_input->setPixmap(QPixmap::fromImage(qimgInput));
	ui.label_input->setScaledContents(true);
	*/
	// joint
	gray = cvCreateImage(cvSize(iw, ih), IPL_DEPTH_8U, 1);
	cvCvtColor(srcI, gray, CV_RGB2GRAY);
	grayM = cvarrToMat(gray);
	// 이미지의 height, width 출력
	QString hs = QString::number(ih);
	QString ws = QString::number(iw);
	ui.textBrowser_h->setText(hs);
	ui.textBrowser_w->setText(ws);

	///////////////////////////////////////////////////////////////////////////////////////////
	// serial
	fstarts = omp_get_wtime();

	shape_sout = cvCreateImage(cvSize(iw, ih), IPL_DEPTH_8U, 1);
	Hsegmentation_serial(gray, shape_sout);
	serialM = cvarrToMat(shape_sout);

	fends = omp_get_wtime();
	fprocTimes = fends - fstarts;
	fpss = floor((1 / (fprocTimes))*10000.f + 0.5) / 10000.f;
	QString fpsSs = QString::number(fpss);
	ui.textBrowser_fps_s->setText(fpsSs);

	QImage shapeOutputserial = convertOpenCVMatToQtQImage(serialM).scaled(ui.label_shapeserial->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//	QImage shapeOutputserial = QImage((uchar*)shape_sout->imageData, iw, ih, QImage::Format_Indexed8);
	ui.label_shapeserial->setPixmap(QPixmap::fromImage(shapeOutputserial));
//	ui.label_shapeserial->setScaledContents(true);

	// CUDA
	fstartc = omp_get_wtime();

	shape_cout = cvCreateImage(cvSize(iw, ih), IPL_DEPTH_8U, 1);
//	Hsegmentation_CUDA(gray, shape_cout);
	cudaM = cvarrToMat(shape_cout);

	fendc = omp_get_wtime();
	fprocTimec = fendc - fstartc;
	fpsc = floor((1 / (fprocTimec))*10000.f + 0.5) / 10000.f;
	QString fpsSc = QString::number(fpsc);
	ui.textBrowser_fps_c->setText(fpsSc);

	QImage shapeOutputcuda = convertOpenCVMatToQtQImage(cudaM).scaled(ui.label_shapeCUDA->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label_shapeCUDA->setPixmap(QPixmap::fromImage(shapeOutputcuda));
	/*
	QImage shapeOutputcuda = QImage((uchar*)shape_cout->imageData, iw, ih, QImage::Format_Indexed8);
	ui.label_shapeCUDA->setPixmap(QPixmap::fromImage(shapeOutputcuda));
	ui.label_shapeCUDA->setScaledContents(true);
	*/
	///////////////////////////////////////////////////////////////////////////////////////////

}
void HumanSegmentation1::LoadSourceVideo()
{
	/*
	if (isvideo && !pause)
		return;
	// load 할 때 팝업 생성
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Source File"), "",
		tr("input image (*.avi *.mp4)"));

	char* sourcename = strdup((fileName.toStdString()).c_str());
	cvSequence = cvCaptureFromAVI(sourcename);

	if (cvSequence == NULL)
		return;

	QPixmap pauseicon("pause.png");
	QIcon PButtonICON(pauseicon);
	ui.pause->setIcon(PButtonICON);

	isvideo = true;
	pause = false;
	isimage = false;
	vw = (int)cvGetCaptureProperty(cvSequence, CV_CAP_PROP_FRAME_WIDTH);
	vh = (int)cvGetCaptureProperty(cvSequence, CV_CAP_PROP_FRAME_HEIGHT);

	QString hs = QString::number(vh);
	QString ws = QString::number(vw);
	ui.textBrowser_h->setText(hs);
	ui.textBrowser_w->setText(ws);
	
	theTimer = new QTimer(this);
	connect(theTimer, SIGNAL(timeout()), this, SLOT(DisplayVideo()));
	theTimer->start(25);
	*/
	/*
	theTimer = new QTimer(this);
	connect(theTimer, SIGNAL(timeout()), this, SLOT(Hsegmentation_CUDA()));
	theTimer->start(25);
	*/

	Hsegmentation_CUDA();
}

void HumanSegmentation1::DisplayVideo()
{
	frame = cvQueryFrame(cvSequence);
	if (!frame)
		return;
	frameM = cvarrToMat(frame);
	// inpug frame display
	QImage Qframe = convertOpenCVMatToQtQImage(frameM).scaled(ui.label_input->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	//QImage Qframe = QImage((uchar*)frame->imageData, vw, vh, QImage::Format_RGB888);
//	Qframe = Qframe.scaled(ui.label_input->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label_input->setPixmap(QPixmap::fromImage(Qframe.rgbSwapped()));
	//ui.label_input->setScaledContents(true);

	gray = cvCreateImage(cvSize(vw, vh), IPL_DEPTH_8U, 1);
	cvCvtColor(frame, gray, CV_RGB2GRAY);
	cvtColor(frameM, grayM, CV_RGB2GRAY);

	///////////////////////////////////////////////////////////////////////////////////////////
	// serial
	fstarts = omp_get_wtime();

	shape_sout = cvCreateImage(cvSize(vw, vh), IPL_DEPTH_8U, 1);
	Hsegmentation_serial(gray, shape_sout);

	fends = omp_get_wtime();
	fprocTimes = fends - fstarts;
	fpss = floor((1 / (fprocTimes))*10000.f + 0.5) / 10000.f;
	QString fpsSs = QString::number(fpss);
	ui.textBrowser_fps_s->setText(fpsSs);

	serialM = cvarrToMat(shape_sout);
	QImage shapeOutputserial = convertOpenCVMatToQtQImage(serialM).scaled(ui.label_shapeserial->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label_shapeserial->setPixmap(QPixmap::fromImage(shapeOutputserial));
	/*
	QImage shapeOutputserial = QImage((uchar*)shape_sout->imageData, vw, vh, QImage::Format_Indexed8);
	ui.label_shapeserial->setPixmap(QPixmap::fromImage(shapeOutputserial));
	ui.label_shapeserial->setScaledContents(true);
	*/
	// CUDA
	fstartc = omp_get_wtime();

	shape_cout = cvCreateImage(cvSize(vw, vh), IPL_DEPTH_8U, 1);
//	Hsegmentation_CUDA(gray, shape_cout);

	fendc = omp_get_wtime();
	fprocTimec = fendc - fstartc;
	fpsc = floor((1 / (fprocTimec))*10000.f + 0.5) / 10000.f;
	QString fpsSc = QString::number(fpsc);
	ui.textBrowser_fps_c->setText(fpsSc);

	cudaM = cvarrToMat(shape_cout);
	QImage shapeOutputcuda = convertOpenCVMatToQtQImage(cudaM).scaled(ui.label_shapeCUDA->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label_shapeCUDA->setPixmap(QPixmap::fromImage(shapeOutputcuda));
	/*
	QImage shapeOutputcuda = QImage((uchar*)shape_cout->imageData, vw, vh, QImage::Format_Indexed8);
	ui.label_shapeCUDA->setPixmap(QPixmap::fromImage(shapeOutputcuda));
	ui.label_shapeCUDA->setScaledContents(true);
	*/
	///////////////////////////////////////////////////////////////////////////////////////////


//		this->update();
}


void HumanSegmentation1::checkpause()
{
	if (isimage)
		return;
	QPixmap pauseicon("pause.png");
	QPixmap playicon("play.png");
	if (isvideo)
	{
		if (!pause)
		{
			QIcon PButtonICON(playicon);
			ui.pause->setIcon(PButtonICON);
			pause = true;
			theTimer->stop();
		}
		else
		{
			QIcon PButtonICON(pauseicon);
			ui.pause->setIcon(PButtonICON);
			pause = false;
			theTimer->start();
		}
	}
}

// Mat형을 QImage로 바꾸는 함수
QImage HumanSegmentation1::convertOpenCVMatToQtQImage(Mat mat)
{
	// 각 채널별로 핸들링
	if (mat.channels() == 1)
		return QImage((uchar*)mat.data, (int)mat.cols, (int)mat.rows, (int)mat.step, QImage::Format_Indexed8);
	else if (mat.channels() == 3)
		return QImage((uchar*)mat.data, (int)mat.cols, (int)mat.rows, (int)mat.step, QImage::Format_RGB888);
	return QImage();
}

// input zoom 키가 눌렸을 때
void HumanSegmentation1::inputzoom()
{
	if (!isimage&& !isvideo)
		return;
	else if(isimage&& !isvideo)
	{
		namedWindow("input", WINDOW_AUTOSIZE);
		//resizeWindow("input", 1632, 1224);
		imshow("input", src);
		cvWaitKey(0);
	}
	else if (!isimage&&isvideo && pause)
	{
		Mat zoominput = cvarrToMat(frame);
		namedWindow("input", WINDOW_AUTOSIZE);
		//resizeWindow("input", 1632, 1224);
		imshow("input", zoominput);
		cvWaitKey(0);
	}
}

void HumanSegmentation1::shapezoom_s()
{
	if (!isimage && !isvideo)
		return;
	else if (isimage && !isvideo)
	{
		Mat zoominput = cvarrToMat(shape_sout);
		namedWindow("shape_serial", WINDOW_AUTOSIZE);
		//resizeWindow("input", 1632, 1224);
		imshow("shape_serial", zoominput);
		cvWaitKey(0);
	}
	else if (!isimage&&isvideo && pause)
	{
		Mat zoominput = cvarrToMat(shape_sout);
		namedWindow("shape_serial", WINDOW_AUTOSIZE);
		//resizeWindow("input", 1632, 1224);
		imshow("shape_serial", zoominput);
		cvWaitKey(0);
	}
}

void HumanSegmentation1::shapezoom_c()
{
	if (!isimage && !isvideo)
		return;
	else if (isimage && !isvideo)
	{
		Mat zoominput = cvarrToMat(shape_cout);
		namedWindow("shape_CUDA", WINDOW_AUTOSIZE);
		//resizeWindow("input", 1632, 1224);
		imshow("shape_CUDA", zoominput);
		cvWaitKey(0);
	}
	else if (!isimage&&isvideo && pause)
	{
		Mat zoominput = cvarrToMat(shape_cout);
		namedWindow("shape_CUDA", WINDOW_AUTOSIZE);
		//resizeWindow("input", 1632, 1224);
		imshow("shape_CUDA", zoominput);
		cvWaitKey(0);
	}
}
// show information
void HumanSegmentation1::show_info()
{
	if (!isinfo)
	{
		info_fi = imread("info3.png", 1);
		isinfo = true;
	}

	//cv::resize(info_fi, info_fi, cv::Size(742, 302), 0, 0, CV_INTER_CUBIC);
	//cvtColor(for_v, for_v, CV_RGB2BGR);
	namedWindow("Developer", WINDOW_NORMAL);
	resizeWindow("Developer", 540, 640);
	imshow("Developer", info_fi);
	cvWaitKey(0);
}

void HumanSegmentation1::save_input()
{
	if (!isimage && !isvideo)
		return;
	else if (isimage && !isvideo)
	{
		imwrite("input.png", src);
	}
	else if (!isimage&&isvideo && pause)
	{
		imwrite("input.png", frameM);
	}
}

void HumanSegmentation1::save_serial()
{
	if (!isimage && !isvideo)
		return;
	else if (isimage && !isvideo)
	{
		imwrite("shape_serial.png", serialM);
	}
	else if (!isimage&&isvideo && pause)
	{
		imwrite("shape_serial.png", serialM);
	}
}

void HumanSegmentation1::save_cuda()
{
	if (!isimage && !isvideo)
		return;
	else if (isimage && !isvideo)
	{
		imwrite("shape_cuda.png", cudaM);
	}
	else if (!isimage&&isvideo && pause)
	{
		imwrite("shape_cuda.png", cudaM);
	}
}

IplImage HumanSegmentation1::Hsegmentation_serial(IplImage *iplin, IplImage *iplout)
{
	/*
	int w = iplin->width;
	int ws = iplin->widthStep;
	int h = iplin->height;

	float *pSrc = new float[w*h];
	float *pDst = new float[w*h];
	float *pPoint = new float[8];

	pPoint[0] = 420;
	pPoint[1] = 140;

	pPoint[2] = 425;
	pPoint[3] = 900;

	pPoint[4] = 561;
	pPoint[5] = 297;

	pPoint[6] = 303;
	pPoint[7] = 297;

	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++)
		{
			pSrc[j*w + i] = unsigned char(iplin->imageData[j*ws + i]);
		}
	}
	float *pcuSrc;
	float *pcuPoint;
	float *pcuDst;
	(cudaMalloc((void**)&pcuSrc, w*h * sizeof(float)));
	(cudaMalloc((void**)&pcuDst, w*h * sizeof(float)));

	(cudaMemcpy(pcuSrc, pSrc, w*h * sizeof(float), cudaMemcpyHostToDevice));
	(cudaMalloc((void**)&pcuPoint, 8 * sizeof(float)));
	(cudaMemcpy(pcuPoint, pPoint, 8 * sizeof(float), cudaMemcpyHostToDevice));

	draw(pcuSrc, pcuDst, w, h, pcuPoint, 2);

	(cudaMemcpy(pDst, pcuSrc, w*h * sizeof(float), cudaMemcpyDeviceToHost));

	CvSize cvsize1 = { w ,h };

	for (int y = 0; y < cvsize1.height; y++) {
		for (int x = 0; x < cvsize1.width; x++) {

			cvSetReal2D(iplout, y, x, pDst[y*cvsize1.width + x]);
		}
	}

	cudaFree(pcuSrc);
	cudaFree(pcuDst);
	*/



	return *iplout;
}

void HumanSegmentation1::Hsegmentation_CUDA()
{
	isvideo = true;
	for (int i = 1; i < 40; i++)
	{
		theTimer = new QTimer(this);
		sha_serial(i);
		func(i);

		repaint();

		Sleep(50);
		
		//theTimer->start(25);
	}


	//func(i);
	//this->update();
	
}

void HumanSegmentation1::func(int index)
{

		FILE *f;
		int r, i = 0;
		float x, y, z;
		int point[28] = { 0 };

		char name[10];
		char file[10];
		float ** pSrc = new float*[10];
		for (int i = 0; i < 10; i++)
		{
			pSrc[i] = new float[512 * 288];
		}
		float * pDst = new float[512 * 288];
		int w = 288;
		int h = 512;
		int ws = 288;

		QString hs = QString::number(h);
		QString wss = QString::number(w);
		ui.textBrowser_h->setText(hs);
		ui.textBrowser_w->setText(wss);

		for (int k = 0; k < 10; k++)
		{
			sprintf(name, "%03d.jpg", k + index);
			srcI = cvLoadImage(name, 1);

			frameM = cvarrToMat(srcI);


			gray = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
			cvCvtColor(srcI, gray, CV_RGB2GRAY);
			int w = gray->width;
			int ws = gray->widthStep;
			int h = gray->height;
			for (int j = 0; j < h; j++)
			{
				for (int i = 0; i < w; i++)
				{
					pSrc[k][j*w + i] = unsigned char(gray->imageData[j*ws + i]);

				}
			}
			if (k == 4) {
				sprintf(file, "%03d.txt", k + index);
				f = fopen(file, "r");
				while ((r = fscanf(f, "%f %f %f ", &x, &y, &z)) != EOF) {
					point[i++] = int(x * 288 / 288);
					point[i++] = int(y * 512 / 512);
					z = 0;

				}
			}

		}
		if (!srcI)
			return;
		float tStart, tEnd;
		double ProTime;
		tStart = cvGetTickCount();
		float **pcuSrc = new float*[10];
		float *bmask;
		float *pcuDst;
		float *temp;
		int *pPoint;
		for (int i = 0; i < 10; i++)
			(cudaMalloc((void**)&pcuSrc[i], w*h * sizeof(float)));

		(cudaMalloc((void**)&pPoint, 28 * sizeof(int)));
		(cudaMalloc((void**)&pcuDst, w*h * sizeof(float)));
		(cudaMalloc((void**)&temp, w*h * sizeof(float)));
		(cudaMalloc((void**)&bmask, w*h * sizeof(float)));

		for (int i = 0; i < 10; i++)
			(cudaMemcpy(pcuSrc[i], pSrc[i], w*h * sizeof(float), cudaMemcpyHostToDevice));

		(cudaMemcpy(pPoint, point, 28 * sizeof(int), cudaMemcpyHostToDevice));

		sub(pcuSrc, w, h, pcuDst, bmask, pPoint, temp);

		(cudaMemcpy(pDst, pcuDst, w*h * sizeof(float), cudaMemcpyDeviceToHost));

		//time checker
		tEnd = cvGetTickCount();// for check processing
		ProTime = 0.001 * (tEnd - tStart) / cvGetTickFrequency(); // for msec

		CvSize cvsize1 = { w ,h };
		IplImage *shapecout = cvCreateImage(cvsize1, IPL_DEPTH_8U, 1);

		// copy to OpenCV
		for (int y = 0; y < cvsize1.height; y++) {
			for (int x = 0; x < cvsize1.width; x++) {

				cvSetReal2D(shapecout, y, x, pDst[y*cvsize1.width + x]);
			}
		}

		cudaM = cvarrToMat(shapecout);

		QImage Qframe = convertOpenCVMatToQtQImage(frameM).scaled(ui.label_input->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
		ui.label_input->setPixmap(QPixmap::fromImage(Qframe.rgbSwapped()));
		QImage shapeOutputcuda = convertOpenCVMatToQtQImage(cudaM).scaled(ui.label_shapeCUDA->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
		ui.label_shapeCUDA->setPixmap(QPixmap::fromImage(shapeOutputcuda));

		fpsc = floor((1 / (ProTime))*10000.f + 0.5) / 10000.f;
		QString fpsSc = QString::number(fpsc);
		ui.textBrowser_fps_c->setText(fpsSc);

		// free the device memory
		cudaFree(pcuSrc);
		cudaFree(pcuDst);
}

Mat HumanSegmentation1::Hsegmentation_serial(Mat matin, Mat matout)
{

	return matout;
}

Mat HumanSegmentation1::Hsegmentation_CUDA(Mat matin, Mat matout)
{

	return matout;
}
