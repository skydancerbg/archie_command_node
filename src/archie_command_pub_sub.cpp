#include "ros/ros.h"
#include "trajectory_msgs/JointTrajectoryPoint.h"
#include "trajectory_msgs/JointTrajectory.h"

// REMARKS: Francesco, this is "quick and dirty" demo test rig...
// You can use use global variables (considered bad style) to move data between the subscriber and the publisher,
// or create a class, that contains the subscriber, publisher and the publish loop and then use a member variables.
//
// It is too much pointless work to format the teminal output of the subscriber,to match the ros topic echo output. 
// The subscriber just prints the message received line by line in the terminal ...


void jointTrajectoryCallback(const trajectory_msgs::JointTrajectory::ConstPtr& jt);
void publishJointTrajectoryMessage(ros::Publisher cmd_traj_pub, int pubNumberCounter,int numberOfJoints_toPublish, int numberOfPoints_toPublish);

void PrintFloats(std::vector<double> values);
int setValueToPoint(trajectory_msgs::JointTrajectory* trajectoire, int pointNumber, int jointNumber, int val);


int main(int argc, char *argv[])
{
	ros::init(argc, argv, "archie_command_pub_sub");

	ros::NodeHandle n;

	ros::Subscriber jTraj_sub = n.subscribe("control/left_leg/feedbackJoint", 1000, jointTrajectoryCallback);	// Listening to the imcoming Arduino messages ....
	// ros::Subscriber jTraj_sub = n.subscribe("control/jointTrajectory", 1000, jointTrajectoryCallback);	// Just for testing - subscribed to itself :)

    ros::Publisher cmd_traj_pub = n.advertise<trajectory_msgs::JointTrajectory>("control/left/leg/jointTrajectory", 1);

	int pubNumberCounter(1); 
    /////////////////////////////////////////////////////////////////////////////////////////////////////  
    //  !!!!!!!!!!!!!!!!!!!!
	// CHANGE THE NUMBER OF JOINTS AND POINTS TO PUBLISH HERE:
    int numberOfJoints_toPublish(6);
	int numberOfPoints_toPublish(1);
    //  !!!!!!!!!!!!!!!!!!!!
    ///////////////////////////////////////////////
    ///////////////////////////////////////////////
    //  !!!!!!!!!!!!!!!!!!!!
	// CHANGE THE PUBLISH RATE HERE:
	ros::Rate loop_rate(5); //IN Hz - TIMES PER SECOND
    //  !!!!!!!!!!!!!!!!!!!!
    ///////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
	// PUBLISH LOOP:
	while (ros::ok())
	{
        publishJointTrajectoryMessage(cmd_traj_pub, pubNumberCounter,numberOfJoints_toPublish, numberOfPoints_toPublish);
		ros::spinOnce();
		loop_rate.sleep();
		pubNumberCounter++;    
    }   

	return 0;
}

//////////// SUBSCRIBERS MESSAGE CALLBACK /////////////////////////////////////

void jointTrajectoryCallback(const trajectory_msgs::JointTrajectory::ConstPtr& jt)
{
//  ROS_INFO("Entered callback!");  // PRINT DEBUG MESSAGE IN TERMINAL

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

 void PrintFloats(std::vector<double> values)
 {
	for(int jointIndex = 0; jointIndex < values.size(); jointIndex++)
		ROS_INFO("\t\t\t\t%f", values[jointIndex]);
 }


void publishJointTrajectoryMessage(ros::Publisher cmd_traj_pub, int pubNumberCounter,int numberOfJoints_toPublish, int numberOfPoints_toPublish)
 {

//////////// FILL THE MESSAGE WITH FAKE DATA ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////  
    //  !!!!!!!!!!!!!!!!!!!!
	// CHANGE THE NUMBER OF JOINTS AND POSITIONS TO PUBLISH HERE:
    int numberOfJoints = numberOfJoints_toPublish;
	int numberOfPoints = numberOfPoints_toPublish;
    //  !!!!!!!!!!!!!!!!!!!!
    ///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

    trajectory_msgs::JointTrajectory traj;
	trajectory_msgs::JointTrajectoryPoint point;

  	char jNames[12][20] = {"j0", "j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "j10","j11"};

    traj.header.frame_id = "base_link";
    traj.joint_names = std::vector<std::basic_string<char> >();
    traj.joint_names.resize(numberOfJoints);
    traj.points = std::vector<trajectory_msgs::JointTrajectoryPoint>(numberOfPoints);

    for(int jointNumber=0; jointNumber<numberOfJoints; jointNumber++)
            traj.joint_names[jointNumber] =jNames[jointNumber];
	

	 for(int pointNumber=0; pointNumber<numberOfPoints; pointNumber++) 
     {

      traj.points[pointNumber] = trajectory_msgs::JointTrajectoryPoint();
      traj.points[pointNumber].positions = std::vector<double>(numberOfJoints);
      traj.points[pointNumber].accelerations = std::vector<double>(numberOfJoints);
	  traj.points[pointNumber].velocities = std::vector<double>(numberOfJoints);
	  traj.points[pointNumber].effort = std::vector<double>(numberOfJoints);
      traj.points[pointNumber].time_from_start = ros::Duration(pointNumber+1, 9999); //each trajectory point's time_from_start must be greater than the last    
	 }

	// // // // // // set dummy values to the point array
    for(int pointNumber=0; pointNumber<numberOfPoints; pointNumber++) {
        for(int jointNumber=0; jointNumber<numberOfJoints; jointNumber++) {
                setValueToPoint(&traj,pointNumber,jointNumber,pubNumberCounter);
        }
	}

 ///////////////////////////////////////////////////////////////////////////////////////

// fill the header stamp with current ROS time
       traj.header.stamp = ros::Time::now();

// publish the message
		cmd_traj_pub.publish(traj);	

		// ROS_INFO("Trajectory published!!!!!!!!!!!!!!!!!!!!!!!!!!!!"); // PRINT DEBUG MESSAGE IN TERMINAL

 }

 // sets dummy values to the current point
int setValueToPoint(trajectory_msgs::JointTrajectory* trajectoire, int pointNumber, int jointNumber, int val){
    trajectoire->points[pointNumber].positions[jointNumber] = val;
    trajectoire->points[pointNumber].accelerations[jointNumber] = val;
	trajectoire->points[pointNumber].velocities[jointNumber] = val;
	 trajectoire->points[pointNumber].effort[jointNumber] = val;
    return 0;
}
