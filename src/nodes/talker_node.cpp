#include <smart_cpp_ros_node/talker.h>

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "talker");
  ros::NodeHandle nh;

  // Create a new node_example::Talker object.
  smart_cpp_ros_node::ExampleTalker node(nh);

  // Let ROS handle all callbacks.
  ros::spin();

  return 0;
}  // end main()