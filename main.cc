#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

class rect
{
	int frame_no;
	int left, top, right, bottom;
};

int main()
{
	ifstream fin;
	fin.open("detections/DPM/camera1.mat_plaintext");
	VideoCapture cap("videos/camera1/00000.MTS");

	if(!cap.isOpened())
	{
	    cout << "Error opening video stream or file" << endl;
	    return -1;
  	}

  	while(1)
  	{
  		Mat frame;
  		cap >> frame;

  		if (frame.empty())
  			break;

  		imshow("out", frame);
  		waitKey(1);
  	}
  	fin.close();
}