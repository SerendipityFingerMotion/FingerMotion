#include"Header.h"
CvHistogram* FingerTipDetector::pHist;
IplImage* FingerTipDetector::bgImage;

char getEnum(Motion m){
	switch (m){
	case RIGHT: return 'a';
	case RIGHTDOWN: return 'b';
	case DOWN: return 'c';
	case LEFTDOWN: return 'd';
	case LEFT: return 'e';
	case LEFTUP: return 'f';
	case UP: return 'g';
	case RIGHTUP: return 'h';
	case ZOOMIN: return 'i';
	case ZOOMOUT: return 'j';
	case CIRCLE: return 'k';

	}
}


void FingerTipDetector::programSetUp(){
	this->camera = new Camera(1, 640, 480);
	
	this->imageProcessor = new ImageProcessor();
	this->userHand = new Hand();
	
	this->dstImage = cvCreateImage(this->camera->getResolution(), IPL_DEPTH_8U, 3);
	this->bgImage = cvCreateImage(this->camera->getResolution(), IPL_DEPTH_8U, 3);
}

void FingerTipDetector::programRun(){
	this->programSetUp();
	IplImage* frame = cvCreateImage(this->camera->getResolution(), IPL_DEPTH_8U, 3);
	bool backImage = false;
	bool detect = false;
	bool hist = false;
	bool patternStart = false;
	bool testStart = false;

	int frameCount = 0;
	int patternCount = 0;
	Move testMove;
	Move move;
	Pattern *pattern = new Pattern();
	Pattern *testPattern = new Pattern();

	while (1){
		frame = this->camera->getQueryFrame();
		if (!frame)
			continue;
		cvFlip(frame, dstImage, 1);

		if (!backImage && frameCount > 10){
			backImage = true;
			cvCopy(dstImage, this->bgImage);
		}
		else if (!detect && backImage)
			cvCircle(dstImage, cvPoint(420, 260), 100, CV_RGB(0, 255, 0), 3);
		else if (detect){
			if (!hist){
				imageProcessor->CreateSkinColorHistogram(dstImage);
				hist = true;
			}
			imageProcessor->detectFingerTip(dstImage, userHand);
			if (patternStart){
				//pattern->hand[patternCount] = new Hand();
				userHand->setMeanFinger();
				pattern->hand[patternCount++] = userHand;
				
				//std::cout << patternCount << std::endl;
				//    std::cout << patternCount << " : " <<pattern->hand[patternCount - 1]->finger[0]->fingerTip.x << "," << pattern->hand[patternCount - 1]->finger[0]->fingerTip.y << std::endl;
			}
			if (testStart){
				testPattern->hand[patternCount++] = userHand;
			}

		}
		userHand = new Hand();

		char key = cvWaitKey(30);
		if (key == 13)
			detect = true;
		else if (key == 27)
			break;
		else if (key == 32){
			if (!patternStart)
				patternStart = true;
			else{
				patternStart = false;
				pattern->setFrameCount(patternCount);
				move.setPattern(pattern);
				move.mPattern = move.getMove(move.mPattern);
				patternCount = 0;
			}
		}
		else if (key == 49){
			if (!testStart)
				testStart = true;
			else{
				testStart = false;
				testPattern->setFrameCount(patternCount);
				testMove.setPattern(testPattern);
				testMove.mPattern = testMove.getMove(testMove.mPattern);
				if (testMove.getPatternCompar(move.mPattern, move.getLineCount())){
					std::cout << "match";
				}
				else{
					std::cout << "nomatch";
				}
				patternCount = 0;
			}
		}

		cvShowImage("Program", dstImage);
		frameCount++;
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

