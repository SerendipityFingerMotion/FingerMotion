# FingerMotion
---
[FingerMotion](https://github.com/SerendipityFingerMotion/FingerMotion/)은 영상처리를 통해 사용자의 손을 인식하여 손가락의 움직임에 대한 패턴 인식을 하도록 도와주는 라이브러리입니다.


#Principle
---
&nbsp;영상처리의 과정에서 먼저 손의 이진 이미지를 얻음으로써 손을 인식할 수 있습니다. 좀 더 정확한 손의 이진 이미지를 얻기위해서 배경차 이미지, 추출한 피부색을 가지고 역투영을 해서 얻어낸 이진 이미지, 일반적인 피부색을 추출해내서 이진화 시킨 이미지를 모두 and 연산을 하여 결과를 얻어낸 후 마지막으로 닫힘연산을 합니다. 이렇게 해서 얻어낸 손의 이미지에서 윤곽선을 찾아내고 또 윤곽선에서 손 끝점들을 찾아냅니다. 이 손 끝점들의 움직임을 좌표로 저장하여 이것을 분석하여 어떤 움직임이 발생했는지 알 수 있게 됩니다.

<img src="https://github.com/SerendipityFingerMotion/FingerMotion/blob/hyun13/KakaoTalk_20150625_082829928.png">
<히스토그램에 대한 색 분포 이미지>

<img src="https://github.com/SerendipityFingerMotion/FingerMotion/blob/hyun13/KakaoTalk_20150625_082829928.png">
<일반적인 사람의 피부색으로 검출>

<img src="https://github.com/SerendipityFingerMotion/FingerMotion/blob/hyun13/KakaoTalk_20150625_082842188.png">
<배경과의 차이를 이용한 손 이미지 검출>

<img src="https://github.com/SerendipityFingerMotion/FingerMotion/blob/hyun13/KakaoTalk_20150625_082848138.png">
<추출한 손에 대한이진 이미지>


&nbsp;손 끝점에서 하나를 기준점으로 잡은다음 이것의 움직임을 분석합니다. 움직인 점들을 이어 직선으로 만들고 이 직선의 각도를 측정해서 직선이 어느 방향을 가리키는지 계산하여 저장해 둡니다. 그리고 다음 이 과정을 반복하면서 바로 이전의 결과와 비교를 합니다.

# Installing
---
OpenCV를 [http://opencv.org/downloads.html](http://opencv.org/downloads.html)에서 다운 받으신 후 설치파일을 실행하여 OpenCV를설치 합니다.
# Configuring
---
1. 시스템 환경변수 path에 OpenCV가 설치된 경로의 bin 폴더 경로명을 추가
    - ex) C드라이브에 OpenCV가 설치되고 32bit 운영체제, Visual Studio 버젼이 2012인 경우의 경로명 => C:\opencv\build\x86\vc11\bin

2. Visual Studio의 프로젝트 속성 > 구성 속성 > VC++ 디렉터리 > 포함 디렉터리에 헤더파일 경로명 추가
    - ex) C드라이브에 OpenCV가 설치된 경우의 헤더파일 경로명 => C:\opencv\build\include

3. Visual Studio의 프로젝트 속성 > 구성 속성 > VC++ 디렉터리 > 라이브러리 디렉터리에 라이브러리 경로명 추가
    - ex) C드라이브에 OpenCV가 설치된 경우의 라이브러리 경로명 => C:\opencv\build\x86\vc11\lib

4. Visual Studio의 프로젝트 속성 > 구성 속성 > 링커 > 입력 > 추가 종속성에 lib 파일들 추가
    - ex)<BR>opencv_core2411d.lib<BR>opencv_imgproc2411d.lib<BR>opencv_highgui2411d.lib<BR>opencv_ml2411d.lib<BR>opencv_video2411d.lib<BR>opencv_features2d2411d.lib<BR>opencv_calib3d2411d.lib<BR>opencv_objdetect2411d.lib<BR>opencv_contrib2411d.lib<BR>opencv_legacy2411d.lib<BR>opencv_flann2411d.lib

#Usage
---
사용자의 피부색을 추출하도록 초록색 원안에 대고 엔터를 누르신 후에, 스페이스를 눌러서 패턴 등록을 시작하고 또 스페이스를 눌러 등록을 완료합니다. 그리고 1번 키를 눌러서 패턴 인식 확인을 시작하고, 또 1번 키를 눌러 패턴 인식 확인을 완료합니다.
#Documentation
---
[API 문서 참조](https://github.com/SerendipityFingerMotion/FingerMotion/blob/hyun13/api_v1.pdf)
#Effect
---
&nbsp;이 라이브러리는 화면전환과 같은 단순 입력 필요 시, 영상 인식 게임 개발 시 등 다양한 부분에서 활용될 수 있습니다.

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
