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
//Use image_transport for publishing and subscribing to images in ROS
#include <image_transport/image_transport.h>
//Use cv_bridge to convert between ROS and OpenCV Image formats
#include <cv_bridge/cv_bridge.h>
//Include some useful constants for image encoding. 
#include <sensor_msgs/image_encodings.h>

using namespace std;
using namespace cv;

class Thresholding 
{
    
public:
   
   Thresholding(Mat diff_blue,Mat diff_green,Mat diff_red,int value);

   void setName(Mat diff_blue,Mat diff_green,Mat diff_red,int value);
    
   Mat getName();
    
     	
private:
	Mat threshold_blue;
	Mat threshold_yellow;
	Mat threshold_red;
	int flag;
};

#endif // THRESHOLDING_H

