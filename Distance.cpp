//#include"Header.h"
//
//int Distance::getDistance(){
//	int firstFingerx,firstFingery,secondFingerx,secondFingery;
//	int colX, colY;
//	firstFingerx = this->a->fingerTip.x;
//	firstFingery = this->a->fingerTip.y;
//	secondFingerx = this->b->fingerTip.x;
//	secondFingery = this->b->fingerTip.y;
//
//	colX = firstFingerx - secondFingerx;
//	colY = firstFingery - secondFingery;
//	if (colX < 0) colX*(-1);
//	if (colY < 0) colY*(-1);
//
//	return colX + colY;
//}
//
//void Distance::setFinger(Finger *x, Finger *y){
//	this->a = x;
//	this->b = y;
//}