#include <smart_cpp_ros_node/listener.h>

namespace smart_cpp_ros_node
{
ExampleListener::ExampleListener(ros::NodeHandle nh)
{
  // Create a subscriber.
  // Name the topic, message queue, callback function with class name, and object containing callback function.
  sub_ = nh.subscribe("example", 10, &ExampleListener::messageCallback, this);
}

void ExampleListener::messageCallback(const smart_cpp_ros_node::SmartCppROSdata::ConstPtr &msg)
{
  // Note that these are only set to INFO so they will print to a terminal for example purposes.
  // Typically, they should be DEBUG.
  ROS_INFO("message is %s, a + b = %d", msg->message.c_str(), msg->a + msg->b);
}
}