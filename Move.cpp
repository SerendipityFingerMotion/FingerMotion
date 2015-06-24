#include"Header.h"
#define M_PI 3.14159265358979323846

void Move::setFrame(Frame *frame){
	this->frame = frame;
}

Motion* Move::getMove(){
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


}