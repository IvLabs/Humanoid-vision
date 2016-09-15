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
#include "Pose.h"
#include "Image_Processing.h"
#include "Thresholding.h"
#include "Differential_Rgb.h"
#include <ros/ros.h>
//Use image_transport for publishing and subscribing to images in ROS
#include <image_transport/image_transport.h>
//Use cv_bridge to convert between ROS and OpenCV Image formats
#include <cv_bridge/cv_bridge.h>
//Include some useful constants for image encoding. 
#include <sensor_msgs/image_encodings.h>
#include "std_msgs/Float64.h"
//Include headers for OpenCV Image processing

namespace enc = sensor_msgs::image_encodings;
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
         ros::init(argc, argv, "main");

  
  	ros::NodeHandle n;  
  	ros::Publisher chatter_pub = n.advertise<std_msgs::Float64>("chatter", 1000);
  	ros::Rate loop_rate(10);
	VideoCapture cap(1);
if ( !cap.isOpened() ) // if not success, exit program
{
	cout << "Cannot open the video file" << endl;
	return -1;
}
	namedWindow("src",1);
while(ros::ok())
	{
	Mat src;
	bool bSuccess = cap.read(src); // read a new frame from video
	if (!bSuccess) //if not success, break loop
	break;

        Differential_Rgb layers(src);
        
// blue 
        int blue=1;
	Thresholding thresh_blue(layers.getNameBlue(),layers.getNameGreen(),layers.getNameRed(),blue);
        Mat threshold_blue=thresh_blue.getName();
        Image_Processing denoise_blue;Image_Processing centre_blue; Pose estimation_blue;
	threshold_blue = denoise_blue.denoising(threshold_blue); //denoising
	int *blue_centroid=centre_blue.centroid(threshold_blue,src,blue); //centroid calculation
	double *position=estimation_blue.contour_detection(threshold_blue,src); //height calculation  
	cout << "blue - " << "x = "<< blue_centroid[0]<< " y = " << blue_centroid[1] << endl ;
        
// yellow 
/*	int yellow=2;
        Thresholding thresh_yellow(layers.getNameBlue(),layers.getNameGreen(),layers.getNameRed(),yellow);
        Mat threshold_yellow=thresh_yellow.getName();
	Image_Processing denoise_yellow;Image_Processing centre_yellow; Pose estimation_yellow;
        threshold_yellow = denoise_yellow.denoising(threshold_yellow); //denoising
	int *yellow_centroid=centre_yellow.centroid(threshold_yellow,src,yellow); // centroid calculation
	estimation_yellow.contour_detection(threshold_yellow,src);//height calculation
	cout << "yellow - " << "x = "<< yellow_centroid[0] << " y = " << yellow_centroid[1] << endl ;

// red 
	int red=3;
        Thresholding thresh_red(layers.getNameBlue(),layers.getNameGreen(),layers.getNameRed(),red);
        Mat threshold_red=thresh_red.getName();
        Image_Processing denoise_red;Image_Processing centre_red; Pose estimation_red;
	threshold_red = denoise_red.denoising(threshold_red); //denoising
	int *red_centroid=centre_red.centroid(threshold_red,src,red); // centroid calculation
	estimation_red.contour_detection(threshold_red,src); //height calculation
	cout << "red - " << "x = "<< red_centroid[0] << " y = " << red_centroid[1] << endl ;
*/
    
        std_msgs::Float64 msg1;
         std_msgs::Float64 msg2;
          std_msgs::Float64 msg3;
        msg1.data=position[0];
        msg2.data=position[1];
	msg3.data=position[2];
       ROS_INFO("x : %lf\n y : %lf\n z :%lf\n ", msg1.data,msg2.data,msg3.data);
        
//display images.
	imshow("src",src);

	if(waitKey(3)==27)
        break;

//	waitKey(0);
         chatter_pub.publish(msg1);
         chatter_pub.publish(msg2);
         chatter_pub.publish(msg3);
   	 ros::spinOnce();
	loop_rate.sleep();
	}

return 0;
}

