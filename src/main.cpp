
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <math.h>
#include "Pose.h"
#include "Image_Processing.h"
#include "Thresholding.h"
#include "Differential_Rgb.h"
#include <ros/ros.h>
#include "cam_node/posi.h"

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
  	ros::Publisher chatter_pub = n.advertise<cam_node::posi>("chatter", 1000);
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
	Thresholding thresh_blue(layers.getNameBlue(),layers.getNameGreen(),layers.getNameRed(),layers.getNameGray(),blue);
        Mat threshold_blue=thresh_blue.getName();
        Image_Processing denoise_blue;Image_Processing centre_blue; Pose estimation_blue; //Pose getpose_blue;
	threshold_blue = denoise_blue.denoising(threshold_blue); //denoising
	int *blue_centroid=centre_blue.centroid(threshold_blue,src,blue); //centroid calculation
	double *position_blue=estimation_blue.contour_detection(threshold_blue,src);  
        
        //red
/*	int red=3;
        Thresholding thresh_red(layers.getNameBlue(),layers.getNameGreen(),layers.getNameRed(),layers.getNameGray(),red);
        Mat threshold_red=thresh_red.getName();
        Image_Processing denoise_red;Image_Processing centre_red; Pose estimation_red;
	threshold_red = denoise_red.denoising(threshold_red); //denoising
	int *red_centroid=centre_red.centroid(threshold_red,src,red); // centroid calculation
        double *position_red=estimation_red.contour_detection(threshold_red,src);
*/	


   	if ((position_blue[0]!=0.0) && (position_blue[1]!=0.0) && (position_blue[2]!=0.0) && (position_blue[3]!=0.0) && (position_blue[4]!=0.0) && (position_blue[5]!=0.0) )
   	{
      	cam_node::posi data;      
        data.msg1=position_blue[0];
        data.msg2=position_blue[1];
        data.msg3=position_blue[2];
        data.msg4=position_blue[3];
        data.msg5=position_blue[4];
        data.msg6=position_blue[5];
         
        ROS_INFO("x: %f\n y: %f\n z:%f\n roll: %f\n pitch: %f\n yaw: %f\n ", data.msg1,data.msg2,data.msg3,data.msg4,data.msg5,data.msg6);
          
 	chatter_pub.publish(data);
        }  
      
//display images.
	imshow("src",src);

	if(waitKey(3)==27)
        break;
        
//	waitKey(0);
        
         
   	ros::spinOnce();
	loop_rate.sleep();
	}

return 0;
}

