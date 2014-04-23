#ifndef NETWORKS_HPP
#define NETWORKS_HPP

#include <boost/asio.hpp>

namespace Networks {

class Core {
private:
  
  static boost::asio::io_service io_service();

  Core() {};
  
public:
  static boost::asio::io_service getIOService() {
    return io_service;
  }
}

}

#endif
