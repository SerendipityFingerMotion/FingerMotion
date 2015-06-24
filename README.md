# FingerMotion
---
[FingerMotion](https://github.com/SerendipityFingerMotion/FingerMotion/)은 영상처리를 통해 사용자의 손을 인식하여 손가락의 움직임에 대한 패턴 인식을 하도록 도와주는 라이브러리입니다.


# Installing
---
OpenCV를 [http://opencv.org/downloads.html](http://opencv.org/downloads.html)에서 다운 받으신 후 설치파일을 실행하여 OpenCV를설치 합니다.
# Configuring
---
1. 시스템 환경변수 path에 OpenCV가 설치된 경로의 bin 폴더 경로명을 추가
    - ex) C드라이브에 OpenCV가 설치되고 32bit의 Visual Studio 버젼이 2012인 경우의 경로명 => C:\opencv\build\x86\vc11\bin

2. Visual Studio의 프로젝트 속성 > 구성 속성 > VC++ 디렉터리 > 포함 디렉터리에 헤더파일 경로명 추가
    - ex) C드라이브에 OpenCV가 설치된 경우의 헤더파일 경로명 => C:\opencv\build\include

3. Visual Studio의 프로젝트 속성 > 구성 속성 > VC++ 디렉터리 > 라이브러리 디렉터리에 라이브러리 경로명 추가
    - ex) C드라이브에 OpenCV가 설치된 경우의 라이브러리 경로명 => C:\opencv\build\x86\vc11\lib

4. Visual Studio의 프로젝트 속성 > 구성 속성 > 링커 > 입력 > 추가 종속성에 dll 파일들 추가
    - ex)<BR>opencv_core2411d.lib<BR>opencv_imgproc2411d.lib<BR>opencv_highgui2411d.lib<BR>opencv_ml2411d.lib<BR>opencv_video2411d.lib<BR>opencv_features2d2411d.lib<BR>opencv_calib3d2411d.lib<BR>opencv_objdetect2411d.lib<BR>opencv_contrib2411d.lib<BR>opencv_legacy2411d.lib<BR>opencv_flann2411d.lib

#Usage
---
사용자의 피부색을 추출하도록 원안에 대고 엔터를 누르신 후에 ....
#Documentation
---
[API 문서 참조](https://github.com/SerendipityFingerMotion/FingerMotion/blob/hyun13/api_v1.pdf)
#Contributors
---
* 팀장 이현 [(leehyun13)] [1]
* 팀원 강진혁 [(jhKang1313)] [2]
* 팀원 이재호 [(jaehos)][3]
* 팀원 윤성민 [(sungmin7465)][4]


[1]: https://github.com/leehyun13
[2]: https://github.com/jhKang1313
[3]: https://github.com/jaehos
[4]: https://github.com/sungmin7465
