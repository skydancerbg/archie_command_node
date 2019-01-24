#include "ros/ros.h"
#include "trajectory_msgs/JointTrajectoryPoint.h"
#include "trajectory_msgs/JointTrajectory.h"

// REMARK: 
// It is too much pointless work to format the teminal output of the subscriber,to match the ros topic echo output. 
// The subscriber just prints the message received line by line in the terminal ...

 void PrintFloats(std::vector<double> values)
 {
	for(int jointIndex = 0; jointIndex < values.size(); jointIndex++)
		ROS_INFO("\t\t\t\t%f", values[jointIndex]);
 }
 

void jointTrajectoryCallback(const trajectory_msgs::JointTrajectory::ConstPtr& jt)
{
 ROS_INFO("Entered callback!");
 ROS_INFO("header:");
 ROS_INFO("\tseq: %d", jt->header.seq);
 ROS_INFO("\tstamp:");
 ROS_INFO("\t\tsecs: %f", jt->header.stamp.toSec());
 ROS_INFO("\t\tnsecs: %lu", jt->header.stamp.toNSec());
 ROS_INFO("\t\tframeId: %s", jt->header.frame_id.c_str());

 for(int i = 0; i < jt->joint_names.size(); i++)
{ 
	ROS_INFO("\t\t\t%s", jt->joint_names[i].c_str());

} 

 ROS_INFO("points:");
 for(int pointIndex = 0; pointIndex < jt->points.size(); pointIndex++)
 {
	 ROS_INFO("positions:");
	 PrintFloats(jt->points[pointIndex].positions);

	 ROS_INFO("velocities:");
	 PrintFloats(jt->points[pointIndex].velocities);

	 ROS_INFO("accelerations:");
	 PrintFloats(jt->points[pointIndex].accelerations);
 
	 ROS_INFO("effort:");
	 PrintFloats(jt->points[pointIndex].effort);

	ROS_INFO("\ttime from start:");
	ROS_INFO("\t\tsecs: %f", jt->points[pointIndex].time_from_start.toSec());
	ROS_INFO("\t\tnsecs: %lu", jt->points[pointIndex].time_from_start.toNSec());
 }
}

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "archie_command_sub");

	ros::NodeHandle n;

	// ros::Subscriber jTraj_sub = n.subscribe("control/feedbackJoint", 1000, jointTrajectoryCallback);	
	ros::Subscriber jTraj_sub = n.subscribe("control/jointTrajectory", 1000, jointTrajectoryCallback);	

	ros::spin();

	return 0;
}