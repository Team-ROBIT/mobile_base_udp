#include "mobile_base_udp.h"

#include <ros/ros.h>

#include "image_transport/image_transport.h"

#include <sensor_msgs/Image.h>
#include "mobile_base_msgs/STMrx.h"
#include "mobile_base_msgs/STMtx.h"

#include <QApplication>

#include <string>
#include <vector>
#include <utility>

#include <iostream>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  operator_udp udp(argc, argv);

  app.connect(&udp, SIGNAL(thread_end()), &app, SLOT(quit()));

  int result = app.exec();

  return 0;
}

operator_udp::operator_udp(int argc, char **argv) : controller(this)
{
  ros::init(argc, argv, "operator_udp");
  if (!ros::master::check())
  {
    return;
  }
  ros::start();
  ros::NodeHandle nh("~");
  image_transport::ImageTransport it(nh);

  controller.load_param(nh, sub_vec_, pub_vec_);

  start();
}

operator_udp::~operator_udp()
{
  if (ros::isStarted())
  {
    ros::shutdown();
    ros::waitForShutdown();
  }
}

void operator_udp::run()
{
  ros::spin();
  emit thread_end();
}