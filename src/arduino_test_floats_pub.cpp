#include "ros/ros.h"
#include "ros/time.h"
#include <string> 
#include "sensor_msgs/ChannelFloat32.h"
#include "trajectory_msgs/JointTrajectory.h"
#include "trajectory_msgs/JointTrajectoryPoint.h"
#include <sstream>

int main(int argc, char *argv[])
{
    sensor_msgs::ChannelFloat32 msg;

	ros::init(argc, argv, "archie_command_pub");

	ros::NodeHandle n;

	int pubNumberCounter(1);


//////CHANGE NUMBER OF FLOATS TRANSMITTED HERE /////////////////////////////////////////////////	
    int count  = 307;
///////////////////////////////////////////////////////

    msg.name="N";

    for(int i = 0; i < count; i++)
        msg.values.push_back(i+1);
    
    ros::Publisher cmd_traj_pub = n.advertise<sensor_msgs::ChannelFloat32>("control/jointTrajectory", 1);


	ros::Rate loop_rate(30); 
	while (ros::ok())
	{
	
		cmd_traj_pub.publish(msg);	

		ROS_INFO("Trajectory published");

		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}
