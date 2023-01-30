#include "ros/ros.h"
#include "std_msgs/Float32.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "battery_publisher");
  ros::NodeHandle n;
  ros::Publisher battery_pub = n.advertise<std_msgs::Float32>("battery", 1000);
  ros::Rate loop_rate(10);

  float battery_percentage;

  if(argc < 2) {
    ROS_ERROR("Not enough arguments. Usage: battery_publisher <battery_percentage>");
    return 1;
  }
  else {
    battery_percentage = atof(argv[1]);
  }

  while (ros::ok()) {
    std_msgs::Float32 msg;
    msg.data = battery_percentage;
    battery_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
