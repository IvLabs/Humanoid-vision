

#ifndef POSE_H
#define POSE_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;

class Pose
{
public:
 Pose();

double* contour_detection(Mat threshold,Mat threshold_extract,Mat gray_src,Mat src);
double* pose_estimation(const std::vector<cv::Point3f> &objectPoints,const std::vector<cv::Point2f> &imagePoints);
private:
	vector<Point3f> objectPoints1 ;
        vector<Point3f> objectPoints2 ;
	Mat cameraIntrinsicParams ;
	Mat distCoeffs;
        
        //int index[20];
        //double area_array[20];
	
	
};
#endif // POSE_H
