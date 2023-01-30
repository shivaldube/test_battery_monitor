# test_battery_monitor

Download the package copying the link or zip in src folder in your catkin workspace
build the package using catkin_make

source your workspace environment 
intilize roscore in another terminal then rosrun <package> battery publisher <battery percentage>
in another terminal subscribe using rosrun <package> battery subscriber
