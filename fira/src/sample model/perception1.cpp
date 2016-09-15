#include "ros/ros.h"
#include "std_msgs/String.h"
 
void Callback1(const std_msgs::String::ConstPtr& immsg)
{
  
  ROS_INFO("[Perciever] I am getting: [%s]\n", immsg->data.c_str());
  
}

void Callback2(const std_msgs::String::ConstPtr& dmsg)
{
  
  ROS_INFO("[Perciever] I am getting: [%s]\n", dmsg->data.c_str());
  
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "perception1");

  
  ros::NodeHandle n,m;

  
  ros::Subscriber sub1 = n.subscribe("raw_values", 1000,Callback1);
ros::Subscriber sub2 = m.subscribe("raw_values", 1000,Callback2);


  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  return 0;
}
