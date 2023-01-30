# test_battery_monitor

1. Download the package copying the link or zip in src folder in your catkin workspace
2. build the package using catkin_make
3. source your workspace environment 
4. intilize roscore in another terminal then rosrun "package_name" battery publisher "battery_percentage"
5. in another terminal subscribe using rosrun "package_name" battery subscriber
