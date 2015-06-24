#include"Header.h"
#define M_PI 3.14159265358979323846



void Move::setPattern(Pattern *frame){
	this->frame = frame;
}
void Move::setMotion(Motion *pattern){
	this->mPattern = pattern;
}


bool Move::getPatternCompar(Motion *target, int lineCount){
	int targetNum = lineCount;
	int thisNum = this->getLineCount();
	int collectCount = 0;
	if (targetNum > thisNum){
		for (int i = 0; i < targetNum - thisNum; i++){
			for (int j = 0; j < thisNum; j++){
				std::cout << target[j];
				if (target[i + j] == this->mPattern[j]) collectCount++;
			}
		}
		if ((collectCount / targetNum * 100) > 80){
			return true;
		}
		else return false;
	}
	else if (targetNum == thisNum){
		for (int i = 0; i < targetNum; i++){
			if (target[i] == this->mPattern[i]) collectCount++;

		}
		if (((collectCount / targetNum) * 100) > 80){
			return true;
		}
		else return false;

	}
	else{
		for (int i = 0; i < thisNum - targetNum; i++){
			for (int j = 0; j < targetNum; j++){
				if (this->mPattern[i + j] == target[j]) collectCount++;
			}
		}
		if ((collectCount / thisNum * 100) > 80){
			return true;
		}
		else return false;
	}

}

void Move::setLineCount(int count){
	this->lineCount = count;
}
int Move::getLineCount(){
	return this->lineCount;
}
Motion searchLine(double theta){
	double end = 342.5;
	double start = 22.5;
	Motion motion = RIGHT;
	for (int i = 0; i < 8; i++){
		if (theta >= end || theta < start){
			return RIGHT;
		}
		else if (theta >= start + (45 * (i - 1)) && theta < start + (45 * i)){
			return (Motion)i;
		}

	}

}

double getTheta(int thetaX, int thetaY){
	if (thetaX < 0){
		if (thetaY < 0){
			thetaX = thetaX* (-1);
			thetaY = thetaY* (-1);
			return 270 - atan2(thetaY, thetaX);
		}
		else{
			thetaX = thetaX* (-1);
			return 180 - atan2(thetaY, thetaX);
		}
	}
	else{
		if (thetaY < 0){
			thetaY = thetaY* (-1);
			return 360 - atan2(thetaY, thetaX);

		}
		else
			return atan2(thetaY, thetaX);

	}
}


Motion* Move::getMove(Motion *motion){

	int fingerCount = this->frame->hand[0]->detectFingerCount;
	int frameCount = this->frame->getFrameCount();
	int lineCount = 0;
	double sumAtan = 0;


	for (int i = 0; i < frameCount - 1; i++){
		for (int j = i; j < frameCount - 1; j++){
			int preThetaY = this->frame->hand[j + 1]->finger[0]->fingerTip.y;
			int preThetaX = this->frame->hand[j + 1]->finger[0]->fingerTip.x;
			int postThetaY = this->frame->hand[j]->finger[0]->fingerTip.y;
			int postThetaX = this->frame->hand[j]->finger[0]->fingerTip.x;

			sumAtan += getTheta(preThetaX, preThetaY) - getTheta(postThetaX, postThetaY);
			//            std::cout << this->frame->hand[j + 1]->finger[0]->fingerTip.y << "," << this->frame->hand[j + 1]->finger[0]->fingerTip.x << std::endl;
			if (sumAtan>fabs((double)((180 * 2) / 8))){
				this->line[lineCount++]->setIndex(i, j);
				i = ++j;
				//                std::cout << lineCount;
			}
		}
	}
	if (lineCount == 0){
		this->line[lineCount] = new Line();
		this->line[lineCount++]->setIndex(0, frameCount - 1);
	}

	motion = (Motion*)malloc(sizeof(Motion)*lineCount);
	for (int k = 0; k < lineCount; k++){
		double theta = 0;
		//    std::cout << this->frame->hand[line[i]->getEnd()]->finger[0]->fingerTip.y << "," << this->frame->hand[line[i]->getStart()]->finger[0]->fingerTip.y << "," << this->frame->hand[line[i]->getEnd()]->finger[0]->fingerTip.x << "," << this->frame->hand[line[i]->getStart()]->finger[0]->fingerTip.x;
		int thetaY = this->frame->hand[line[k]->getEnd()]->finger[0]->fingerTip.y - this->frame->hand[line[k]->getStart()]->finger[0]->fingerTip.y;
		int thetaX = this->frame->hand[line[k]->getEnd()]->finger[0]->fingerTip.x - this->frame->hand[line[k]->getStart()]->finger[0]->fingerTip.x;
		theta = getTheta(thetaX, thetaY);
		motion[k] = searchLine(theta);
	}
	this->setLineCount(lineCount);

	return motion;
}





