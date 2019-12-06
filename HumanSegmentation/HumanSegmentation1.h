#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets\qfiledialog.h>
#include <Qtimer.h>
#include "ui_HumanSegmentation1.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <omp.h>

using namespace std;
using namespace cv;

class HumanSegmentation1 : public QMainWindow
{
	Q_OBJECT

public:
	HumanSegmentation1(QWidget *parent = Q_NULLPTR);
	QImage convertOpenCVMatToQtQImage(Mat mat);
	IplImage Hsegmentation_serial(IplImage *iplin, IplImage *iplout);
	Mat Hsegmentation_serial(Mat matin, Mat matout);
	Mat Hsegmentation_CUDA(Mat matin, Mat matout);
	void sha_serial(int ind);
private slots:	// 버튼 클릭 핸들하기 위해 각 함수 선언
	void LoadSource();
	void LoadSourceVideo();
	void DisplayVideo();
	void checkpause();
	void inputzoom();
	void shapezoom_s();
	void shapezoom_c();
	void show_info();
	void save_input();
	void save_serial();
	void save_cuda();
	void Hsegmentation_CUDA();
	void func(int index);
private:
	Ui::HumanSegmentation1Class ui;
	Mat src, info_fi;
	IplImage* srcI;
	Mat frameM, grayM, shape_soutM, serialM, shape_coutM, cudaM;
	IplImage* frame, *gray, *shape_sout, *shape_cout;
	int ih, iw, vh, vw;
	CvCapture* cvSequence;
	QTimer* theTimer;
	double fstarts, fends, fprocTimes, fpss;
	double fstartc, fendc, fprocTimec, fpsc;
	bool pause = false;
	bool isimage = false;
	bool isvideo = false;
	bool isjoint = false;
	bool isshape = false;
	bool isinfo = false;
};
