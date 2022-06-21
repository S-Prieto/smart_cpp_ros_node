#ifndef SMART_CPP_ROS_NODE_LISTENER_H
#define SMART_CPP_ROS_NODE_LISTENER_H

// ROS includes.
#include <ros/ros.h>
#include <ros/time.h>

// Custom message includes. Auto-generated from msg/ directory.
#include <smart_cpp_ros_node/SmartCppROSdata.h>

namespace smart_cpp_ros_node
{
class ExampleListener
{
 public:
  //! Constructor.
  explicit ExampleListener(ros::NodeHandle nh);

  //! Callback function for subscriber.
  void messageCallback(const smart_cpp_ros_node::SmartCppROSdata::ConstPtr &msg);

 private:
  //! Subscriber to custom message.
  ros::Subscriber sub_;
};
}

#endif  // SMART_CPP_ROS_NODE_LISTENER_H