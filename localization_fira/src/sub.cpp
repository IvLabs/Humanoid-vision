#include "ros/ros.h"
#include "localization_fira/posi.h"


void chatterCallback(const localization_fira::posi::ConstPtr &msg)
{
  ROS_INFO("I heard: [%s]", msg->msg1);
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "sub");

  
  ros::NodeHandle n;

  
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

  
  ros::spin();

  return 0;
}
