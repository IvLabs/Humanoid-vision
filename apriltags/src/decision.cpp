#include "ros/ros.h"
#include "visualization_msgs/MarkerArray.h"
#include "apriltags/AprilTagDetections.h"

#include <ros/ros.h>
#include <ros/forwards.h>
#include <ros/single_subscriber_publisher.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <visualization_msgs/Marker.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cv_bridge/cv_bridge.h>
#include <sstream>
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"





#include "std_msgs/String.h"
#include "localization_fira/posi.h"

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <visualization_msgs/MarkerArray.h>
#include "yaml-cpp/yaml.h"
#include <sstream>
#include <fstream>

float z_actual;
float yaw_actual;

float zth = 2.000;
float yaw = -0.0021;
int flag1 = 0 ;
  int flag2 = 0;
  int flag = 0;


std_msgs::String msg1;
std_msgs::String msg2;
std_msgs::String msg3;


ros::Publisher chatter_pub1;
ros::Publisher chatter_pub2;
ros::Publisher chatter_pub3;

ros::Subscriber sub1;



void chatterCallback(const visualization_msgs::Marker::ConstPtr& marker)
//const apriltags::AprilTagDetections::ConstPtr& detections)
{


z_actual=marker->pose.position.z;
//pose->position.z;

yaw_actual=marker->pose.orientation.z;


 
if ((z_actual) > zth)
{

flag1 = 1;

}

else 
{
flag1 = 0;
}

if (yaw_actual > yaw)
{
flag2 = 1 ;
}

else 
{
flag2 = 0;
}
ROS_INFO("I heard:  flag1 [%d]", flag1 );
ROS_INFO("I heard:  flag2 [%d]", flag2 );


if((flag1==1)&&(flag2==1))
{       
        flag=4;     //backward turning 
} 
if((flag1==1)&&(flag2==0))
{
        flag=2;     // backward walking
} 
if((flag1==0) && (flag2==1))
{
	flag=3;        //forward turning
 }
if((flag1==0) && (flag2==0))   
{
  	flag=1;         //forward walking
} 
 
 

if(flag==1)

{
   //ROS_INFO("%s", msg1.data.c_str());
  chatter_pub1.publish(msg1);

 }

else if(flag==2)

{  
 // ROS_INFO("%s", msg2.data.c_str());
  chatter_pub2.publish(msg2);

 }

else if(flag==3)

{
  //ROS_INFO("%s", msg3.data.c_str());
  chatter_pub3.publish(msg3);
 
}

}


int main(int argc, char **argv)
{

ros::init(argc, argv, "decision");
ros::NodeHandle ns;
ros::NodeHandle np1;

chatter_pub1 = np1.advertise<std_msgs::String>("chatter", 1);
std::stringstream ss1;
ss1 << "forward walk";
msg1.data = ss1.str(); 


chatter_pub2 = np1.advertise<std_msgs::String>("chatter", 1);
std::stringstream ss2;
ss2 << "backward walk";
msg2.data = ss2.str();

chatter_pub3 = np1.advertise<std_msgs::String>("chatter", 1);
std::stringstream ss3;    
ss3 << "forward turn";   
msg3.data = ss3.str(); 

 sub1 = ns.subscribe("/apriltags/marker", 1, chatterCallback); 


  

   
ros::Rate loop_rate(10);

  

while (ros::ok())
{
 
  //ros::NodeHandle np2;
  //ros::NodeHandle np3;

 ros::spinOnce();

    //loop_rate.sleep();

}
 return 0;
}

  


