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

  	int old_frame_no = 1, i, flag_broken = false;
  	int read_no = 0;
  	int old_left, old_top, old_right, old_bottom;
  	float old_conf;
  	while(1)
  	{
  		Mat frame;
  		cap >> frame;

  		if (frame.empty())
  			break;

  		int frame_no, left, top, right, bottom;
  		float conf;

  		while(1)
  		{
  			i = 0;
  			if (flag_broken)
  			{
  				i = 40;
  				frame_no = old_frame_no;
  				flag_broken = false;
  			}
	  		for (; i < 40; i++)
	  		{
	  			char here[100];
	  			fin>>here;
	  			read_no++;
	  			float num = atof(here);
	  			if (i == 1)
	  				frame_no = num;
	  			if (i == 2)
	  				left = num;
	  			if (i == 3)
	  				top = num;
	  			if (i == 4)
	  				right = num;
	  			if (i == 5)
	  				bottom = num;
	  			if (i == 39)
	  				conf = num;
	  		}
	  		// cout<<"frame no: "<<frame_no<<" in read no "<<read_no<<endl;
	  		if (frame_no != old_frame_no)
	  		{
	  			old_frame_no = frame_no;
	  			old_left = left;
	  			old_right = right;
	  			old_top = top;
	  			old_bottom = bottom;
	  			old_conf = conf;
	  			flag_broken = true;
	  			break;
	  		}
	  		if (conf < 0.0)
	  			continue;
	  		rectangle(frame, Rect(left, top, right - left, bottom - top), Scalar(0, 0, 0), 2);
	  	}

  		imshow("out", frame);
  		waitKey(10);
  	}
  	fin.close();
}