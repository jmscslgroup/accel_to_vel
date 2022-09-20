#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "accel_to_vel_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block accel_to_vel/Subscribe
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_accel_to_vel_std_msgs_Float64> Sub_accel_to_vel_27;

// For Block accel_to_vel/Publish
extern SimulinkPublisher<geometry_msgs::Twist, SL_Bus_accel_to_vel_geometry_msgs_Twist> Pub_accel_to_vel_33;

void slros_node_init(int argc, char** argv);

#endif
