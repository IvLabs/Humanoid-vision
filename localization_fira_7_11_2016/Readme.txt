

This Package take Four Corner points postion of a color markerand 
publishes publishes X,Y,Z Position of Camera with w.r.t to global origin.

 

------------------------------------------------------------------------------------------------------------------------------------------------
You have to Feed World points of marker corners w.r.t to global origin in Pose.cpp file
You will need extenal web camp
------------------------------------------------------------------------------------------------------------------------------------------------


------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------
For running this package you have to keep this package in src folder of your catkin_package

start typing folowing commands in terminal:

$ roscore


In new terminal first go in your catkin workspace directory and enter following commands

$ source devel/setup.bash
$ cd catkin_make localization_fira
$ roslaunch localization_fira uvcCameraLaunch.launch

In the new terminal type ( remember to be in same directory)

$ source devel/setup.bash
$ rosrun localization_fira localization_fira
---------------------------------------------------------------------------------------------------------------------------------------------------



