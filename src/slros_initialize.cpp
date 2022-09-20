#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "accel_to_vel";

// For Block accel_to_vel/Subscribe
SimulinkSubscriber<std_msgs::Float64, SL_Bus_accel_to_vel_std_msgs_Float64> Sub_accel_to_vel_27;

// For Block accel_to_vel/Publish
SimulinkPublisher<geometry_msgs::Twist, SL_Bus_accel_to_vel_geometry_msgs_Twist> Pub_accel_to_vel_33;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

