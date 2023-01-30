#include <ros/ros.h>
#include "std_msgs/Float32.h"

void batteryCallback(const std_msgs::Float32::ConstPtr& msg)
{
    
	ROS_INFO("Battery_Percentage: %f", msg->data);
	
	std::array<std::string, 4> State = {"Initialisation", "High", "Low", "Final"}; 					//This can be [Initialisation, High, Low, Final]
	std::array<std::string, 3> Battery_State = {"Ok", "Mission_Critical", "Safety_Critical"}; 		//[Ok, Mission_Critical, Safety_Critical] 
	std::array<std::string, 2> Battery_Mission_Monitor = {"Ok", "Low"}; 							//This can be [Ok, Low]
	std::array<std::string, 2> Battery_Safety_Monitor = {"Ok", "Low"}; 								//This can be [Ok, Low]
	float Battery_Percentage = float(0); 															//This is a float value for the battery percentages THIS IS THE BATTERYINFO equivalent
	int Battery_Safety_Threshold = 20;
	int Battery_Mission_Threshold = 30;
	
		while (ros::ok()) 
		{
			if (msg->data > Battery_Safety_Threshold)
				{	
					
					if (msg->data > Battery_Mission_Threshold) 
							{
								Battery_State[0];															//State = High;

								Battery_Mission_Monitor[0]; 												//This can be [Ok, Low]
								Battery_Safety_Monitor[0]; 													//This can be [Ok, Low]
								
								ROS_INFO("Battery_Mission_Safety_Ok");

							} else if ((msg->data <= Battery_Mission_Threshold) && (msg->data > Battery_Safety_Threshold )) 
								{
									Battery_State[1];														//State = Low;

									Battery_Mission_Monitor[1]; 											//This can be [Ok, Low]
									Battery_Safety_Monitor[0]; 												//This can be [Ok, Low]
									
									ROS_INFO("Battery_Mission_Low");

								} 
				} else
									{		
										Battery_State[2];														//State=Final;

										Battery_Mission_Monitor[1]; 											//This can be [Ok, Low]
										Battery_Safety_Monitor[1]; 												//This can be [Ok, Low]
										
										ROS_ERROR("Battery Exception Error");
									}
							
				
					
		
					
    	}
}	
 

int main(int argc, char **argv)
{
    ros::init(argc, argv, "battery_subscriber");
    ros::NodeHandle nh;
	ros::Rate rate(1); // ROS Rate at 1Hz

    ros::Subscriber battery_sub = nh.subscribe("battery", 10, batteryCallback);
	
	rate.sleep();
	ros::spin();

    return 0;
}





