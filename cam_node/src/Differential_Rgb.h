/*
*********************************************************
*							*
*	Author :  Aniket : IvLabs                       *
*                 Radha                                 *
*							*
*********************************************************
*/

#ifndef DIFFERENTIAL_RGB_H
#define DIFFERENTIAL_RGB_H

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

class Differential_Rgb
{
 public:  
   Differential_Rgb(Mat src);
   void setName(Mat src);
   Mat getNameBlue();
   Mat getNameGreen();
   Mat getNameRed();
   Mat getNameGray();

 private:
   Mat rgbChannels[3];
   Mat g;
   Mat new_rgb;
   Mat diff_red;
   Mat diff_blue;
   Mat diff_green;
   Mat gray;
   vector<Mat> channels;
};

#endif // DIFFERENTIAL_H
