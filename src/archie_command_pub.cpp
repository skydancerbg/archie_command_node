#include "ros/ros.h"
#include "ros/time.h"
#include "trajectory_msgs/JointTrajectory.h"
#include "trajectory_msgs/JointTrajectoryPoint.h"
#include <sstream>


int setValueToPoint(trajectory_msgs::JointTrajectory* trajectoire, int pointNumber, int jointNumber, int val);


int main(int argc, char *argv[])
{
	ros::init(argc, argv, "archie_command_pub");

	ros::NodeHandle n;


    ros::Publisher cmd_traj_pub = n.advertise<trajectory_msgs::JointTrajectory>("control/jointTrajectory", 1);


	int pubNumberCounter(1); 

	/////////////////////////////////////////////////////////////////////////////////////////////////////  
    //  !!!!!!!!!!!!!!!!!!!!
	// CHANGE THE PUBLISH RATE HERE:
	ros::Rate loop_rate(5); //IN Hz - TIMES PER SECOND
    //  !!!!!!!!!!!!!!!!!!!!
    ///////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////

	while (ros::ok())
	{

//////////// FILL THE MESSAGE WITH FAKE DATA ///////////////////////////////////////////////////////////

    trajectory_msgs::JointTrajectory traj;
	trajectory_msgs::JointTrajectoryPoint point;

  	char jNames[12][20] = {"j0", "j1", "j2", "j3", "j4", "j5", "j6", "j7", "j8", "j9", "j10","j11"};

/////////////////////////////////////////////////////////////////////////////////////////////////////  
    //  !!!!!!!!!!!!!!!!!!!!
	// CHANGE THE NUMBER OF JOINTS AND POINTS TO PUBLISH HERE:
    int numberOfJoints(6);
	int numberOfPoints(1);
    //  !!!!!!!!!!!!!!!!!!!!
    ///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

    traj.header.frame_id = "base_link";
    traj.joint_names = std::vector<std::basic_string<char> >();
    traj.joint_names.resize(numberOfJoints);
    traj.points = std::vector<trajectory_msgs::JointTrajectoryPoint>(numberOfPoints);

    for(int jointNumber=0; jointNumber<numberOfJoints; jointNumber++) {
    traj.joint_names[jointNumber] =jNames[jointNumber];
	}

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

		ROS_INFO("Trajectory published"); // PRINT DEBUG MESSAGE IN TERMINAL

		ros::spinOnce();
		loop_rate.sleep();
		pubNumberCounter++;
	}

	return 0;
}

// sets dummy values to the current point
int setValueToPoint(trajectory_msgs::JointTrajectory* trajectoire, int pointNumber, int jointNumber, int val){
    trajectoire->points[pointNumber].positions[jointNumber] = val;
    trajectoire->points[pointNumber].accelerations[jointNumber] = val;
	trajectoire->points[pointNumber].velocities[jointNumber] = val;
	 trajectoire->points[pointNumber].effort[jointNumber] = val;
    return 0;
}


