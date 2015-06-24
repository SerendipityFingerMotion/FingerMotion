#include"Header.h"
Finger::Finger(){
	this->fingerTip = cvPoint(0, 0);

}
void Finger::setLocation(int x, int y){
	this->fingerTip.x = x;
	this->fingerTip.y = y;
}