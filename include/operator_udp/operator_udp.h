#ifndef OPERATOR_UDP_H_
#define OPERATOR_UDP_H_

#include "robit_udp/robit_udp.h"
#include "QObject"
#include <QThread>

#include <vector>

class str2ip_port
{
public:
  /**
   * @brief is ip port stirng to ip and port
   * @param string ip+port string "i${ip}p${port}" ip separator is _ (ex: i192_168_199_100p12345)
   * @param ip result of function ip separator is .
   * @param port result of function port
   */
  str2ip_port(const std::string& string, std::string& ip, int port)
  {
    ip = string.substr(1, string.find('p') - 1);
    std::replace(ip.begin(), ip.end(), '_', '.');
    port = stoi(string.substr(string.find('p') + 1));
  }
};

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