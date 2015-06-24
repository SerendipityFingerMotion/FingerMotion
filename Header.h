#include<opencv\highgui.h>
#include<opencv\cv.h>
#include<string.h>
typedef enum { RIGHT, RIGHTDOWN, DOWN, LEFTDOWN, LEFT, LEFTUP, UP, RIGHTUP, ZOOMIN, ZOOMOUT, CIRCLE } Motion;

class Camera{
	//CvCapture* camCapture;
	int resolutionWidth;
	int resolutionHeight;
public:
	CvSize getResolution();
	void setResolution(int width, int height);
	void setCamera(int deviceIndex);
	Camera(int deviceIndex, int width, int height);
	~Camera();
	IplImage* getQueryFrame();
	CvCapture* camCapture; //
	//Video Test
	Camera(char* fileName, int width, int height);
	void setVideo(char* fileName);
};



class Finger{
public:
	CvPoint fingerTip;
	Finger();
	void setLocation(int x, int y);
};

class Distance{
	Finger *a, *b;
public:
	void setFinger(Finger *x, Finger *y);
	int getDistance();
};

class Hand{
public:
	Finger* finger[5];
	CvSeq* hull;
	CvSeq* defect;
	CvSeq* handContour;
	CvMemStorage* handMemStorage;
	CvConvexityDefect defectArray[100];
	double handArea;
	int detectFingerCount;
	Distance distance[4];

	Hand();
	~Hand();
	void getHandDefect();
	void arrayMemSet();
	void convertArray();
	int getDefectTotal();
	

	void setFingerDistance();

};

class ImageProcessor{
	IplImage* transImage;
	IplImage* splitImage;
	IplImage* backProImage;
	IplImage* backSplitImage;
	IplImage* handMasking;
	IplImage* bgImage;
	CvMemStorage* storage;
	CvSeq* firstContour;
public:
	ImageProcessor();
	~ImageProcessor();
	void CreateSkinColorHistogram(IplImage* srcImage);
	void getHandBinaryImage(IplImage* srcImage);
	void detectFingerTip(IplImage* srcImage, Hand* userHnad);
	void determineSingleHandFingerTip(Hand* userHand);
};


class FingerTipDetector{
public:
	Camera* camera;
	Hand* userHand;
	static CvHistogram *pHist;
	ImageProcessor* imageProcessor;
	static IplImage* bgImage;
	IplImage* dstImage;
	void programSetUp();
	void programRun();
	void programExit();
};

class Line{
	int startInd, endInd;
public:
	void setIndex(int startInd, int endInd);
	int getStart();
	int getEnd();

};


class Pattern{
	
	int fingerCount;
	int frameCount;
	
public:
	Hand* hand[1000];
	int getFingerCount();
	int getFrameCount();
	void setFingerCount(int count);
	void setFrameCount(int count);
	

};


class Move{
	//핸드 클래스를 갖고 손가락 5개 
	Pattern* frame;
	int lineCount;
public:
	Motion *mPattern;
	Line* line[1000];
	void setHand(Hand *hand);
	void setPattern(Pattern *frame);
	int getFingerCount();
	Motion* getMove(Motion *motion);
	void setMotion(Motion* pattern);
	bool getPatternCompar(Motion *target, int lineCount);
	void setLineCount(int count);
	int getLineCount();
};

