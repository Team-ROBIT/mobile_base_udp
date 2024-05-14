#include "operator_udp.h"

#include <ros/ros.h>

#include "image_transport/image_transport.h"

#include <sensor_msgs/Image.h>

#include <QApplication>

#include <string>
#include <vector>
#include <utility>

#include <iostream>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  operator_udp udp(argc, argv);

  app.connect(&udp, SIGNAL(thread_end()), &app, SLOT(quit()));

  int result = app.exec();

  return 0;
}

operator_udp::operator_udp(int argc, char** argv) : controller(this)
{
  ros::init(argc, argv, "operator_udp");
  if (!ros::master::check())
  {
    return;
  }
  ros::start();
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);

  std::map<std::string, int> param;

  // this param
  {
    std::string s;
    nh.getParam("/this_ip", s);

    std::string ip;
    int port;
    str2ip_port(s, ip, port);

    controller.bind_udp(ip, port);

    ROS_INFO("this ip : %s:%d", ip.data(), port);
  }
  std::cout << "\n";

  // dst_param
  param.clear();
  nh.getParam("/dst_ip", param);
  ROS_INFO("dest ip : ");
  for (auto& par : param)
  {
    std::string ip;
    int port;
    str2ip_port(par.first, ip, port);
    controller.add_destination(par.second, ip, port);

    ROS_INFO("%s:%d num : %d", ip.data(), port, par.second);
  }
  std::cout << "\n";

  // img param

  param.clear();
  nh.getParam("/image", param);
  ROS_INFO("image topic : ");
  for (auto& par : param)
  {
    img_pub.push_back(nh.advertise<sensor_msgs::Image>(par.first, 1));
    controller.set_MAT_service(par.second, &(img_pub.back()));

    ROS_INFO("name : /%s , num : %d", par.first.data(), par.second);
  }
  std::cout << "\n";

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
  ros::Rate rate(10);
  while (ros::ok())
  {
    ros::spinOnce();
    rate.sleep();
  }
  emit thread_end();
}