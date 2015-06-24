#include "Header.h"

void Line::setIndex(int start, int end){
	this->startInd = start;
	this->endInd = end;
}

int Line::getStart(){
	return this->startInd;
}

int Line::getLineCount(){
	return this->lineCount;
}
int Line::getEnd(){
	return this->endInd;
}