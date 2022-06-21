#include <smart_cpp_ros_node/listener.h>

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "listener");
  ros::NodeHandle nh;

  // Create a new node_example::Talker object.
  smart_cpp_ros_node::ExampleListener node(nh);

  // Let ROS handle all callbacks.
  ros::spin();

  return 0;
}  // end main()