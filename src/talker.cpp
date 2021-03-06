#include <smart_cpp_ros_node/talker.h>

namespace smart_cpp_ros_node
{
ExampleTalker::ExampleTalker(ros::NodeHandle nh) : nh_(nh), message_("hello"), a_(1), b_(2), enable_(true)
{
  // Set up a dynamic reconfigure server.
  // Do this before parameter server, else some of the parameter server values can be overwritten.
  dynamic_reconfigure::Server<smart_cpp_ros_node::smartCppROSConfig>::CallbackType cb;
  cb = boost::bind(&ExampleTalker::configCallback, this, _1, _2);
  dr_srv_.setCallback(cb);

  // Declare variables that can be modified by launch file or command line.
  double rate = 1.0;

  // Initialize node parameters from launch file or command line. Use a private node handle so that multiple instances
  // of the node can be run simultaneously while using different parameters.
  ros::NodeHandle pnh("~");
  pnh.param("a", a_, a_);
  pnh.param("b", b_, b_);
  pnh.param("message", message_, message_);
  pnh.param("rate", rate, rate);
  pnh.param("enable", enable_, enable_);

  // Create a publisher and name the topic. Create any service servers.
  if (enable_)
  {
    start();
  }

  // Create timer.
  timer_ = nh_.createTimer(ros::Duration(1.0 / rate), &ExampleTalker::timerCallback, this);
}

void ExampleTalker::start()
{
  pub_ = nh_.advertise<smart_cpp_ros_node::SmartCppROSdata>("example", 10);
  dummy_service_server_ = nh_.advertiseService("dummy_service", &ExampleTalker::dummyServiceServerCallback, this);
}

void ExampleTalker::stop()
{
  pub_.shutdown();
}

void ExampleTalker::timerCallback(const ros::TimerEvent &event __attribute__((unused)))
{
  if (!enable_)
  {
    return;
  }

  smart_cpp_ros_node::SmartCppROSdata msg;
  msg.message = message_;
  msg.a = a_;
  msg.b = b_;

  pub_.publish(msg);
}

void ExampleTalker::configCallback(smart_cpp_ros_node::smartCppROSConfig &config, uint32_t level __attribute__((unused)))
{
  // Set class variables to new values. They should match what is input at the dynamic reconfigure GUI.
  message_ = config.message;
  a_ = config.a;
  b_ = config.b;

  // Check if we are changing enabled state.
  if (enable_ != config.enable)
  {
    if (config.enable)
    {
      start();
    }
    else
    {
      stop();
    }
  }
  enable_ = config.enable;
}

bool ExampleTalker::dummyServiceServerCallback(smart_cpp_ros_node::DummyService::Request& request, smart_cpp_ros_node::DummyService::Response& response)
{
  ROS_INFO("This is just a dummy service. Your input was %d", request.dummy_input);
  response.message = std::string("OK: Sucessful response");
  return true;
}
}