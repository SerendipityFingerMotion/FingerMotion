#include"Header.h"
#define M_PI 3.14159265358979323846



void Move::setPattern(Pattern *frame){
	this->frame = frame;
}

Motion* Move::getMove(){
	Motion *motion;
	int fingerCount = frame->hand[0]->detectFingerCount;
	int frameCount = frame->getFrameCount();
	int lineCount = 0;
	double sumAtan = 0;
	

	for (int i = 0; i < frameCount-1; i++){
		for (int j = i; i < frameCount-1; j++){
			sumAtan = atan2(this->frame->hand[i + 1]->finger[0]->fingerTip.y, this->frame->hand[i + 1]->finger[0]->fingerTip.x) - atan2(this->frame->hand[i]->finger[0]->fingerTip.y, this->frame->hand[i]->finger[0]->fingerTip.x);
			if (sumAtan>fabs(M_PI / 8)){
				this->line[lineCount++]->setIndex(i,j);
				i = ++j;
			}
		}
	}
	for (int i = 0; i < lineCount; i++){
		double theta;
		theta = atan2(this->frame->hand[line[i]->getEnd]->finger[0].y - this->frame->hand[line[i]->getStart]->finger[0].y, this->frame->hand[line[i]->getEnd]->finger[0].x - this->frame->hand[line[i]->getStart].x);
		motion[i] = searchLine(theta);
	}
	

}
Motion searchLine(double theta){
	double end = 342.5;
	double start = 22.5;
	Motion motion;
	for (int i = 0; i < 8; i++){
		if (motion == RIGHT){
			if (theta >= end || theta < start){
				return RIGHT;
			}
		}
		else{
			if (theta >= start + (45 * (i-1)) && theta < start + (45 * i)){
				return (Motion)i;
			}
		}
	}

}