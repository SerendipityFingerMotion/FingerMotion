#include"Header.h"
CvHistogram* FingerTipDetector::pHist;
IplImage* FingerTipDetector::bgImage;
void FingerTipDetector::programSetUp(){
	this->camera = new Camera(0, 640, 480);
	
	this->imageProcessor = new ImageProcessor();
	this->userHand = new Hand();
	
	this->dstImage = cvCreateImage(this->camera->getResolution(), IPL_DEPTH_8U, 3);
	this->bgImage = cvCreateImage(this->camera->getResolution(), IPL_DEPTH_8U, 3);
}

void FingerTipDetector::programRun(){
	this->programSetUp();
	IplImage* frame  = cvCreateImage(this->camera->getResolution(), IPL_DEPTH_8U, 3);
	bool backImage = false;
	bool detect = false;
	bool hist = false;
	while(1){
		frame = this->camera->getQueryFrame();
		if(!frame)
			continue;
		cvFlip(frame, dstImage, 1);
		if(!backImage){
			backImage = true;
			cvCopy(dstImage, this->bgImage);
		}
		if(!detect)
			cvCircle(dstImage, cvPoint(420, 260), 100, CV_RGB(0, 255, 0), 3);
		else if(detect){
			if(!hist){
				imageProcessor->CreateSkinColorHistogram(dstImage);
				hist = true;
			}
			imageProcessor->detectFingerTip(dstImage, userHand);

		}
		char key = cvWaitKey(30);
		if(key == 13)
			detect = true;
		else if(key == 27)
			break;
		cvShowImage("Program", dstImage);
	}
	this->programExit();
}

void FingerTipDetector::programExit(){
	delete this->imageProcessor;
	delete this->camera;
	delete this->userHand;
	cvReleaseHist(&this->pHist);
	cvReleaseImage(&dstImage);
	cvReleaseImage(&bgImage);
	delete this;
}