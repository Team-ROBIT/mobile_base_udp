#ifndef OPERATOR_UDP_H_
#define OPERATOR_UDP_H_

#include "robit_udp/robit_udp.h"
#include "QObject"
#include <QThread>

#include <vector>

class operator_udp : public QThread
{
  Q_OBJECT

private:
  robit_udp::udp_controller controller;

  std::vector<ros::Subscriber> sub_vec_;
  std::vector<ros::Publisher> pub_vec_;

Q_SIGNALS:

  void thread_end();

public:
  operator_udp(int argc, char** argv);
  ~operator_udp();
  void run();
};

#endif