

#ifndef THRESHOLDING_H
#define THRESHOLDING_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <cv.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
using namespace std;
using namespace cv;

class Thresholding 
{
    
public:
   
   Thresholding(Mat diff_blue,Mat diff_green,Mat diff_red,Mat gray,int value,int rLowH,int rHighH,int gLowH,int gHighH,int bLowH,int bHighH);

   void setName(Mat diff_blue,Mat diff_green,Mat diff_red,Mat gray,int value,int rLowH,int rHighH,int gLowH,int gHighH,int bLowH,int bHighH);
    
   Mat getName();
    
     	
private:
	Mat threshold_blue;
	Mat threshold_yellow;
	Mat threshold_red;
	int flag;
};

#endif // THRESHOLDING_H

