//
//  room.cpp
//  CPP_babel_2019
//
//  Created by Thomas Fournier on 02/10/2019.
//
//

#include "room.hpp"
#include "Isession.hpp"
#include "session.hpp"



void room::join(std::shared_ptr<Isession> participant)
{
  participants_.insert(participant);
  for (auto &msg : recent_msgs_) {
      participant->deliver(msg.get_body());
  }
}

void room::leave(std::shared_ptr<Isession> participant)
{
  participants_.erase(participant);
  std::cout << "nombre d eparticipant: " << participants_.size() << std::endl;
}
//
void room::deliver(const char *line)
{

  message msg;
  msg.set_body_length(std::strlen(line));
  std::memcpy(msg.get_body(), line, std::strlen(line) + 1);

  recent_msgs_.push_back(msg);
  while (recent_msgs_.size() > max_recent_msgs)
    recent_msgs_.pop_front();

   for (auto &participant : participants_) {
       std::cout << "participant: " << participant->get_user().pseudo << std::endl;
       participant->deliver(line);
   }
}

const std::set<std::shared_ptr<Isession>> &room::get_participants()
{
    return participants_;
}
