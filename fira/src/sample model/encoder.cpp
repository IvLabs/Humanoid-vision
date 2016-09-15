#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "encoder");

  
  ros::NodeHandle n;

  
  ros::Publisher encoder_pub = n.advertise<std_msgs::String>("enraw", 1000);

  ros::Rate loop_rate(1);

  
  int count = 0;
  while (ros::ok())
  {
   
    std_msgs::String enmsg;

    std::stringstream ss;
    ss << "encoder datastream " << count;
    enmsg.data = ss.str();

    ROS_INFO("I published %s\n", enmsg.data.c_str());

   
    encoder_pub.publish(enmsg);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
