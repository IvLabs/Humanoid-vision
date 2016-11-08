#include "ros/ros.h"
#include "std_msgs/String.h"
#include "localization_fira/posi.h"
#include <sstream>



float z_actual;
float yaw_actual;

float zth = 0.5900;
float yaw = 15.00;
int flag1 = 0 ;
  int flag2 = 0;
  int flag = 0;



void chatterCallback(const localization_fira::posi::ConstPtr &data)
{

z_actual=data->msg3;
yaw_actual=data->msg6;
if ((z_actual)> zth)
{

flag1 = 1;

}

if (yaw_actual > yaw)
{
flag2 = 1 ;
}
ROS_INFO("I heard:  flag1 [%d]", flag1 );
ROS_INFO("I heard:  flag2 [%d]", flag2 );
 
}





int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "decisionNode");

  ros::NodeHandle np;
  ros::NodeHandle ns;
 
  



if((flag1==1)&&(flag2==1))
{
        flag=1;
} 
if((flag1==1)&&(flag2==0))
{
	 flag=2;
} 
if((flag1==0) && (flag2==1))
{
	flag=3;
}


   

if(flag==1)
{
  ros::Publisher chatter_pub = np.advertise<std_msgs::String>("A", 1);
 }
if(flag==2)
{
  ros::Publisher chatter_pub1 = np.advertise<std_msgs::String>("B", 1);
 }
if(flag==3)
{
  ros::Publisher chatter_pub2 = np.advertise<std_msgs::String>("C", 1);
 }



    ros::Subscriber sub1 = ns.subscribe("/chatter", 1, chatterCallback);  

   
  ros::Rate loop_rate(10);
 
  int count = 0;
  while (ros::ok())
  {
    

    ros::spinOnce();

  }



  return 0;
}

