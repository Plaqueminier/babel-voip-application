//
//  room.hpp
//  CPP_babel_2019
//
//  Created by Thomas Fournier on 02/10/2019.
//
//

#ifndef room_hpp
#define room_hpp

#include <stdio.h>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <set>


class Isession;
class message;
typedef std::deque<message> message_queue;


class room
{
public:
  void join(std::shared_ptr<Isession> participant);
  void leave(std::shared_ptr<Isession> participant);
  void deliver(const char *line);
  const std::set<std::shared_ptr<Isession>> &get_participants();

private:
  std::set<std::shared_ptr<Isession>> participants_;
  enum { max_recent_msgs = 100 };
  message_queue recent_msgs_;
};

#endif /* room_hpp */
