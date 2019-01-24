#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/MultiArrayDimension.h"
#include <sstream>
// #include <vector>
// #include <array>

#define H (5)
#define W (10)


int main(int argc, char **argv)
{
    ros::init(argc, argv, "archie_command_pub");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<std_msgs::Int32MultiArray>("control/jointTrajectory", 1);
    ros::Rate loop_rate(10);
    std_msgs::Int32MultiArray dat;
    // int array[H][W] = {
    //     {0, 1, 2, 3, 4},
    //     {10, 11, 12, 13, 14},
    //     {20, 21, 22, 23, 24},
    //     {30, 31, 32, 33, 34}};

    // fill out message:
    dat.layout.dim.push_back(std_msgs::MultiArrayDimension());
    dat.layout.dim.push_back(std_msgs::MultiArrayDimension());
    dat.layout.dim[0].label = "height";
    dat.layout.dim[1].label = "width";
    dat.layout.dim[0].size = H;
    dat.layout.dim[1].size = W;
    dat.layout.dim[0].stride = H*W;
    dat.layout.dim[1].stride = W;
    dat.layout.data_offset = 0;
    std::vector<int> vec(W*H, 0);
    for (int i=0; i<H; i++)
        for (int j=0; j<W; j++)
            vec[i*W + j] = j;
    dat.data = vec;

    while (ros::ok())
    {
        pub.publish(dat);
        loop_rate.sleep();
    }

    return 0;
}