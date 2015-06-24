#include<opencv\highgui.h>
#include<opencv\cv.h>

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

	Hand();
	~Hand();
	void getHandDefect();
	void arrayMemSet();
	void convertArray();
	int getDefectTotal();

};

class ImageProcessor{
	IplImage* transImage;
	IplImage* splitImage;
	IplImage* backProImage;
	IplImage* backSplitImage;
	IplImage* handMasking;
	IplImage* bgImage;
	IplImage* drawImage;
	IplImage* patternImage;
	CvMemStorage* storage;
	CvSeq* firstContour;
public:
	ImageProcessor();
	~ImageProcessor();
	void CreateSkinColorHistogram(IplImage* srcImage);
	void getHandBinaryImage(IplImage* srcImage);
	void detectFingerTip(IplImage* srcImage, Hand* userHnad);
	void determineSingleHandFingerTip(Hand* userHand);
	void drawPattern(IplImage* srcImage, Hand* userHand);
	void matchPattern();
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

