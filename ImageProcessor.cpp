#include"Header.h"
FILE *f = fopen("vector_data.txt","w");
ImageProcessor::ImageProcessor(){
	CvSize size = cvSize(640, 480);
	this->transImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	this->splitImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	this->backProImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	this->backSplitImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	this->handMasking = cvCreateImage(size, IPL_DEPTH_8U, 1);
	this->bgImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	this->storage = cvCreateMemStorage(0);
	this->firstContour = NULL;
	this->drawImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	this->patternImage = cvLoadImage("pattern.jpg");
	cvZero(drawImage);
	cvNot(drawImage, drawImage);
}
ImageProcessor::~ImageProcessor(){
	cvReleaseImage(&transImage);
	cvReleaseImage(&splitImage);
	cvReleaseImage(&backProImage);
	cvReleaseImage(&backSplitImage);
	cvReleaseMemStorage(&storage);
}
void ImageProcessor::CreateSkinColorHistogram(IplImage* srcImage){
	CvRect catchROI = cvRect(350, 260, 140, 140);

	int histSize = 8;
	float max;
	float valueRange[] = {40, 180};
	float* ranges[] = {valueRange};

	FingerTipDetector::pHist = cvCreateHist(1, &histSize, CV_HIST_ARRAY, ranges, 1);

	cvCvtColor(srcImage, this->transImage, CV_BGR2YCrCb);
	cvSplit(transImage, 0, splitImage, 0, 0);
	cvSetImageROI(splitImage, catchROI);
	cvCalcHist(&splitImage, FingerTipDetector::pHist, 0);
	cvGetMinMaxHistValue(FingerTipDetector::pHist, 0, &max, 0, 0);
	cvScale(FingerTipDetector::pHist->bins, FingerTipDetector::pHist->bins, max? 255/max : 0);
	cvResetImageROI(splitImage);
}
void ImageProcessor::getHandBinaryImage(IplImage* srcImage){
	cvCvtColor(srcImage, transImage, CV_BGR2YCrCb);
	cvCopy(FingerTipDetector::bgImage, bgImage);
	cvCvtColor(bgImage, bgImage, CV_BGR2YCrCb);
	cvSplit(transImage, 0, splitImage, 0, 0);
	cvCalcBackProject(&splitImage, backProImage, FingerTipDetector::pHist);
	cvInRangeS(transImage, cvScalar(0, 133, 77), cvScalar(255, 173, 127), handMasking);
	cvSplit(bgImage, 0, backSplitImage, 0, 0);
	cvAbsDiff(backSplitImage, splitImage, splitImage);
	cvThreshold(splitImage, splitImage, 25, 255, CV_THRESH_BINARY);
	cvAnd(splitImage, handMasking, splitImage);
	cvAnd(backProImage, splitImage, backProImage);
	cvDilate(backProImage, backProImage, 0, 2);
	cvErode(backProImage, backProImage, 0, 5);
}
void ImageProcessor::detectFingerTip(IplImage* srcImage, Hand* userHand){
	double maxArea = 0, area;
	firstContour = NULL;
	getHandBinaryImage(srcImage);
	if (cvFindContours(backProImage, storage, &firstContour, sizeof(CvContour), CV_RETR_TREE)> 0){
		for (CvSeq* c = firstContour; c != NULL; c = c->h_next){
			area = cvContourArea(c, CV_WHOLE_SEQ);
			if (area> maxArea){
				maxArea = area;
				userHand->handContour = c;
			}
		}
		if (maxArea> 3000){
			userHand->getHandDefect();
			for (; userHand->defect; userHand->defect = userHand->defect->h_next){
				if (userHand->getDefectTotal() == 0)
					continue;
				userHand->convertArray();
				determineSingleHandFingerTip(userHand);
				for (int i = 0; i < userHand->detectFingerCount; i++)
					cvCircle(srcImage, userHand->finger[i]->fingerTip, 3, CV_RGB(255, 0, 0), 2);
			}
		}
	}
	userHand->arrayMemSet();
}
void ImageProcessor::determineSingleHandFingerTip(Hand* userHand){
	CvConvexityDefect decendingOrder[100];
	int k = 0;
	int total = userHand->getDefectTotal();
	userHand->detectFingerCount = 0;
	for (int j = 0; j < total; j++){
		if (userHand->defectArray[j].depth > 30)
			decendingOrder[userHand->detectFingerCount++] = userHand->defectArray[j];
	}
	if (userHand->detectFingerCount == 0)
		return;
	CvConvexityDefect tmp;
	for (int i = 0; i < userHand->detectFingerCount; i++){
		for (int j = 0; j < (userHand->detectFingerCount - 1) - i; j++){
			if (decendingOrder[j].start->y < decendingOrder[j + 1].start->y){
				tmp = decendingOrder[j];
				decendingOrder[j] = decendingOrder[j + 1];
				decendingOrder[j + 1] = tmp;
			}
		}
	}
	k = 0;
	if (userHand->detectFingerCount >= 4){
		userHand->detectFingerCount = 5;
		for (int i = 0; i <total && k != 4; i++){
			for (int j = 0; j < userHand->detectFingerCount; j++){
				if (userHand->defectArray[i].start == decendingOrder[j].start){
					userHand->finger[k]->fingerTip.x = (userHand->defectArray[i].start)->x;
					userHand->finger[k++]->fingerTip.y = (userHand->defectArray[i].start)->y;
					if (k == 4){
						userHand->finger[k]->fingerTip.x = (userHand->defectArray[i].end)->x;
						userHand->finger[k]->fingerTip.y = (userHand->defectArray[i].end)->y;
						break;
					}
					break;
				}
			}
		}
	}
	else{
		for (int i = 0; i <total && k != userHand->detectFingerCount; i++)
			for (int j = 0; j < userHand->detectFingerCount; j++)
				if (userHand->defectArray[i].start == decendingOrder[j].start){
					userHand->finger[k]->fingerTip.x = (userHand->defectArray[i].start)->x;
					userHand->finger[k++]->fingerTip.y = (userHand->defectArray[i].start)->y;
					if (k == userHand->detectFingerCount){
						userHand->finger[k]->fingerTip.x = (userHand->defectArray[i].end)->x;
						userHand->finger[k]->fingerTip.y = (userHand->defectArray[i].end)->y;
						break;
					}
					break;
				}
		userHand->detectFingerCount++;
	}
	memset(decendingOrder, 0, 100);
}
void ImageProcessor::drawPattern(IplImage* srcImage, Hand* userHand){
	for(int i = 0 ; i < userHand->detectFingerCount ; i++)
		cvCircle(drawImage,  userHand->finger[1]->fingerTip, 3, CV_RGB(0, 0, 0), 5);
	cvCopy(drawImage, drawImage);
	cvShowImage("Pattern", drawImage);

}
void ImageProcessor::matchPattern(){
	double min, max;
	CvPoint left_top;
	IplImage* matchPattern = cvCreateImage(cvSize(patternImage->width - drawImage->width + 1, patternImage->height - drawImage->height + 1), IPL_DEPTH_32F, 1);
	
	cvMatchTemplate(patternImage, drawImage, matchPattern, CV_TM_CCOEFF_NORMED);
	cvShowImage("mat", matchPattern);
	cvMinMaxLoc(matchPattern, &min, &max, NULL, &left_top);

	cvRectangle(patternImage, left_top, cvPoint(left_top.x + drawImage->width, left_top.y + drawImage->height), CV_RGB(0, 255, 0), 2);
	//cvCircle(patternImage, left_top, 10, CV_RGB(255, 0, 0), 10); 
	cvShowImage("pattern22", patternImage);
	
	cvShowImage("Pattern", drawImage);


}