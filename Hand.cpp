#include"Header.h"

Hand::Hand(){
	for(int i = 0 ; i < 5 ; i++)
		finger[i] = new Finger();

	this->detectFingerCount = 0;
	this->handMemStorage = cvCreateMemStorage(0);
	handContour = NULL;

}
void Hand::getHandDefect(){
	this->handContour = cvApproxPoly(handContour, sizeof(CvContour), handMemStorage, CV_POLY_APPROX_DP, 1);
	this->hull =cvConvexHull2(this->handContour, 0, CV_CLOCKWISE, 0);
	this->defect = cvConvexityDefects(this->handContour, this->hull, this->handMemStorage);

}
void Hand::arrayMemSet(){
	memset(defectArray, 0, 100);

}
void Hand::convertArray(){
	cvCvtSeqToArray(this->defect, this->defectArray, CV_WHOLE_SEQ);
}
int Hand::getDefectTotal(){
	return this->defect->total;
}

void Hand::setFingerDistance(){
	for (int i = 0; i < (this->detectFingerCount)-1; i++){
		distance[i].setFinger(finger[i], finger[i + 1]);
	}
}
Hand::~Hand(){
	cvReleaseMemStorage(&this->handMemStorage);
	//for(int i =0 ; i < 5 ; i++)
	//	delete this->finger[i];

}