#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "imu");

  
  ros::NodeHandle n;

  
  ros::Publisher imu_pub = n.advertise<std_msgs::String>("imuraw", 1000);

  ros::Rate loop_rate(1);

  
  int count = 0;
  while (ros::ok())
  {
   
    std_msgs::String imumsg;

    std::stringstream ss;
    ss << "imu datastream " << count;
    imumsg.data = ss.str();

    ROS_INFO("I published %s\n", imumsg.data.c_str());

   
    imu_pub.publish(imumsg);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
