#include <opencv2\opencv.hpp>
#include <opencv\highgui.h>
#include <opencv2\objdetect.hpp>
#include <opencv2\imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	CascadeClassifier face_cascade;
	//use xml file
	face_cascade.load("haarcascade_frontalface_alt.xml");


	VideoCapture cap;
	cap.open(0);

	//stp images used
	Mat capframe;
	Mat grayframe;
	
	//window
	namedWindow("You're ugly", 1);

	while (true) {

		cap >> capframe;

		//convert to gray and eq
		cvtColor(capframe, grayframe, CV_BGR2GRAY);
		equalizeHist(grayframe, grayframe);

		//vector arr stores found faces
		std::vector<Rect> faces;

		//find and store faces
		face_cascade.detectMultiScale(grayframe, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));

		//draw rect on faces (orig frame)
		for (int i = 0; i < faces.size(); i++) {

			Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point pt2(faces[i].x, faces[i].y);

			rectangle(capframe, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);

		}

		imshow("You're ugly", capframe);

		
		waitKey(3);

	}

	return 0;
}
