#include <ros/ros.h>
#include "sensor_msgs/BatteryState.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Bool.h"
#include <string>
#include "std_msgs/String.h"


//Variable declaration//
std::string batteryStatus;
bool InputAccepted = false;
std::string battery_status_check;
ros::Publisher battery_status_pub;
ros::Publisher input_pub;
ros::Publisher battery_status_check_pub;


void batteryCallback(const sensor_msgs::BatteryState::ConstPtr& msg)													//Battery Callback function
{
    
	ROS_INFO("batteryInfo: %f", msg->percentage);
	
	InputAccepted = true;
	
	std::array<std::string, 3> Battery_State = {"Ok", "MissionCritical", "SafetyCritical"}; 							//[Ok, Mission_Critical, Safety_Critical]
	
	float Battery_Percentage = float(0); 																				//This is a float value for the battery percentages
	int Battery_Safety_Threshold = 30;
	int Battery_Mission_Threshold = 40;

	if (Battery_Mission_Threshold<Battery_Safety_Threshold)
	{
		ROS_ERROR("Mission threshold is below Safety threshold! Please fix the settings");
	}
	else
	{					
			if (msg->percentage > Battery_Mission_Threshold) 
							{
								batteryStatus = Battery_State[0];															//State = OK

							} 
			else if ((msg->percentage <= Battery_Mission_Threshold) && (msg->percentage > Battery_Safety_Threshold )) 
								{
									batteryStatus = Battery_State[1];														//State = Mission_Critical
	
									ROS_INFO("Battery_Mission_Critical");
								} 
			else
									{		
										batteryStatus = Battery_State[2];													//State = Safety_Critical

										ROS_INFO("Battery_Safety_Critical!!");
									}
		
					
    }
		//Input Accepted Boolean Function//
			std_msgs::Bool msg2;
			msg2.data = InputAccepted;
			input_pub.publish(msg2);
			ROS_INFO("Input_Publishing");

		//Battery Status Function//
			std_msgs::String msg3;
			msg3.data = batteryStatus;
			battery_status_pub.publish(msg3);
			ROS_INFO("Publishing_Battery Status");
		
		//Status Check Function//
			std_msgs::String msg4;
   			msg4.data = battery_status_check;
    		battery_status_check_pub.publish(msg);
}	



int main(int argc, char **argv)
{
	ROS_INFO("Battery_Monitor_Running");

    ros::init(argc, argv, "battery_monitor");
    ros::NodeHandle nh;
	
	//Publisher//
	battery_status_pub = nh.advertise<std_msgs::String>("battery_status", 1000);
	input_pub = nh.advertise<std_msgs::Bool>("input_accepted",1000);
	battery_status_check_pub = nh.advertise<std_msgs::String>("battery_status_check", 1000);
	
	//Subscriber//
    ros::Subscriber battery_sub = nh.subscribe("test_4a", 10, batteryCallback);
	
	ros::spin();

    return 0;
}





