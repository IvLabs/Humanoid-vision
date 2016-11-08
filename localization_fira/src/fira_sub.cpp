#include "localization_fira/posi.h"
#include "ros/ros.h"



void chatterCallback(const localization_fira::posi::ConstPtr &msg)
{
  std::cout<<"\n [Listener] X"<<msg->msg1;
  std::cout<<"\n [Listener] Y "<<msg->msg2;
std::cout<<"\n [Listener] Z "<<msg->msg3;
std::cout<<"\n [Listener] Roll"<<msg->msg4;
std::cout<<"\n [Listener]  Pitch "<<msg->msg5;
std::cout<<"\n [Listener] Yaw "<<msg->msg6;

}
int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "fira_sub");

  
  ros::NodeHandle n;

  
  ros::Subscriber sub = n.subscribe("chatter", 1, chatterCallback);

  
  ros::spin();

  return 0;
}
