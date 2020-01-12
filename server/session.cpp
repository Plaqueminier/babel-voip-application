/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "session.hpp"
#include "../include/server.hpp"
#include <boost/bind.hpp>
#include <unordered_map>
using boost::asio::ip::tcp;


//----------------------------------------------------------------------

session::session(tcp::socket socket, std::shared_ptr<Database> database, room &room)
: socket_(std::move(socket)),
    database_(std::move(database)),
    room_(room)
{
    user_ = {-42, "Undefined", "Undefined", 0, "Undefined"};
  std::cout << "new session created" << std::endl;
}

void session::start()
{
    room_.join(shared_from_this());
    do_read();
}

void session::deliver(const char *line)
{

    std::string str = std::string(line) + ';';
    line = str.c_str();
    // std::cout << "message after: " << line << std::endl;

    message msg;
    msg.set_body_length(std::strlen(line));
    std::memcpy(msg.get_body(), line, std::strlen(line) + 1);
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
      do_write();
    }
}

void session::handle_read(std::shared_ptr<session> &s,
                   const boost::system::error_code& ec,
                   size_t bytes_transferred)
  {
      std::string paquet;

      paquet = std::string(read_msg_.get_data()).substr(0, bytes_transferred);
      if (!ec) {
          std::cout << "data: " << paquet << std::endl;
          do_protocol(paquet);
          do_read();

      } else {
          std::vector<std::string> arg;
          arg.push_back("LOGOUT");
          arg.push_back(user_.pseudo);
          protocol_logout(arg);
          std::cerr << "handle read: " << ec.message() << std::endl;
      }
  }

void session::do_read()
{

    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(read_msg_.get_data(), message::max_body_length),
            boost::bind(&session::handle_read, this, self,
                              boost::asio::placeholders::error,
                              boost::asio::placeholders::bytes_transferred)
        );
}


static const std::unordered_map<std::string, std::function<void(const std::shared_ptr<session> &, const std::vector<std::string> &arg)>> protocols_ =  {
    {std::string("TEST"), &session::protocol_test},
    {std::string("CALLTRANSFERT"), &session::protocol_calltransfer},
    {std::string("CALLSTOP"), &session::protocol_callstop},
    {std::string("CALLACCEPT"), &session::protocol_callaccept},
    {std::string("SIGNIN"), &session::protocol_signin},
    {std::string("ADDFRIEND"), &session::protocol_addfriend},
    {std::string("LOGOUT"), &session::protocol_logout},
    {std::string("LOGIN"), &session::protocol_login}
};


void session::protocol_test(const std::vector<std::string> &arg)
{
    std::cout << "TESTING..." << std::endl;
    room_.deliver("TESTING...");
}


void session::protocol_signin(const std::vector<std::string> &arg)
{
    std::string error("SIGNIN FAILED");
    if (arg.size() != 3) {
        std::cout << "protocoll_signin bad arg" << std::endl;
        deliver(error.c_str());
        return;
    }
    std::string pseudo(arg[1]);
    std::string mdp(arg[2]);

    auto users = database_->get_users_by_pseudo(pseudo);
    if(users.size() == 0) {
        User new_user{-1, pseudo, mdp, 0, socket_.remote_endpoint().address().to_string()};
        error = "SIGNIN SUCCESS";
        new_user.id = database_->insert(new_user);
        user_ = new_user;
    }
    deliver(error.c_str());
}

void session::protocol_addfriend(const std::vector<std::string> &arg)
{
    std::string error("ADDFRIEND FAILED");
    if (arg.size() != 2) {
        std::cout << "protocoll_addfriend bad arg" << std::endl;
        deliver(error.c_str());
        return;
    }
    std::string pseudo(arg[1]);
    auto users = database_->get_users_by_pseudo(pseudo);
    if(users.size() == 1) {
        int host = user_.id;
        int connexion = users[0].id;
        auto contacts = database_->get_contacts(host, connexion);
        if (contacts.size() == 0) {
            Contact new_contact{-1, host, connexion};
            Contact new_contact2{-1, connexion, host};
             database_->insert(new_contact);
             database_->insert(new_contact2);
             error = "ADDFRIEND SUCCESS";
             deliver(error.c_str());

            std::string msg = "CLIENT_CONNECT " + users[0].pseudo + " " + users[0].ip;
            std::string msg2 = "CLIENT_CONNECT " + user_.pseudo + " " + user_.ip;

            if (users[0].is_connected) {
                deliver(msg.c_str());
                for (auto &participant : room_.get_participants()) {
                    if (participant->get_user().pseudo == users[0].pseudo) {
                        participant->deliver(msg2.c_str());
                        deliver(error.c_str());
                    }
                }
            }
        }
        return;
    }
    deliver(error.c_str());
}

room &session::get_room()
{
    return room_;
}

void session::protocol_logout(const std::vector<std::string> &arg)
{
    std::string error("LOGOUT FAILED");
    if (arg.size() != 2) {
        std::cout << "protocoll_logout bad arg" << std::endl;
        deliver(error.c_str());
        return;
    }
    std::string pseudo(arg[1]);
    auto users = database_->get_users_by_pseudo(pseudo);
    // auto connected_friends = database_->get_connected_friends(users[0].id);
    if(users.size() == 1) {
        error = "LOGOUT SUCCESS";
        users[0].is_connected = 0;
        database_->update(users[0]);
        auto connected_friends = database_->get_connected_friends(users[0].id);
        user_ = users[0];
        auto self(shared_from_this());
        room_.leave(self);
        deliver(error.c_str());


        auto &participants = room_.get_participants();
        std::string msg;
        for (auto &participant : participants) {
            for (auto afriend : connected_friends) {
                if (afriend.pseudo == participant->get_user().pseudo) {
                    msg = "CLIENT_DISCONNECT " + user_.pseudo;
                    participant->deliver(msg.c_str());

                }
            }
        }
        return;
    }
    deliver(error.c_str());
}

void session::protocol_login(const std::vector<std::string> &arg)
{
    std::string error("LOGIN FAILED");
    if (arg.size() != 3) {
        std::cout << "protocoll_login bad arg" << std::endl;
        deliver(error.c_str());
        return;
    }
    std::string pseudo(arg[1]);
    std::string mdp(arg[2]);

    auto users = database_->get_users_by_logs(pseudo, mdp);
    std::cout << "size: " << users.size() << std::endl;

    if(users.size() == 1 && !users[0].is_connected) {
        error = "LOGIN SUCCESS";
        users[0].ip = socket_.remote_endpoint().address().to_string();
        users[0].is_connected = 1;
        auto connected_friends = database_->get_connected_friends(users[0].id);
        for (auto user : connected_friends)
            error += " " + user.pseudo + ":" + user.ip;
        database_->update(users[0]);
        user_ = users[0];
        deliver(error.c_str());


        auto &participants = room_.get_participants();
        std::string msg;
        for (auto &participant : participants) {
            for (auto afriend : connected_friends) {
                if (afriend.pseudo == participant->get_user().pseudo) {
                    msg = "CLIENT_CONNECT " + user_.pseudo + " " + user_.ip;
                    participant->deliver(msg.c_str());

                }
            }
        }
        return;
    }
    deliver(error.c_str());
}

User &session::get_user()
{
    return user_;
}

void session::protocol_calltransfer(const std::vector<std::string> &arg)
{
    std::string error("CALLTRANSFERT FAILED");

    if (arg.size() != 2) {
        std::cout << "protocoll_call bad arg" << std::endl;
        deliver(error.c_str());
        return;
    }
    std::string pseudo(arg[1]);
    error = "CALLTRANSFERT SUCCESS";
    auto &participants = room_.get_participants();
    for (auto &participant : participants) {
        auto user = participant->get_user();
        if (user.pseudo == pseudo && user.is_connected) {
            participant->deliver(std::string("CALLREQUEST " + user_.pseudo + " " + user_.ip).c_str());
            deliver(error.c_str());
            return;
        }
    }
    error = "CALLTRANSFERT FAILED";
    deliver(error.c_str());
}


void session::protocol_callstop(const std::vector<std::string> &arg)
{
    std::string error("CALLSTOP FAILED");

    if (arg.size() != 2) {
        std::cout << "protocoll_callstop bad arg: " << std::endl;
        for (auto &msg : arg) {
            std::cout << msg;
            std::cout << " ";
        }
        std::cout << std::endl;
        deliver(error.c_str());
        return;
    }
    std::string pseudo(arg[1]);


    error = "CALLSTOP SUCCESS";
    auto &participants = room_.get_participants();
    for (auto &participant : participants) {
        auto user = participant->get_user();
        if (user.pseudo == pseudo && user.is_connected) {
            participant->deliver(std::string("CALLSTOP " + pseudo).c_str());
            deliver(error.c_str());
            return;
        }
    }
    error = "CALLSTOP FAILED";
    deliver(error.c_str());
}

void session::protocol_callaccept(const std::vector<std::string> &arg)
{
    std::string error("CALLACCEPT ");

    if (arg.size() != 3) {
        std::cout << "protocoll_callaccept bad arg" << std::endl;
        deliver(error.c_str());
        return;
    }
    std::string pseudo(arg[2]);
    std::string respond(arg[1]);


    error += respond;
    auto &participants = room_.get_participants();
    for (auto &participant : participants) {
        auto user = participant->get_user();
        if (user.pseudo == pseudo && user.is_connected) {
            participant->deliver(std::string("CALLACCEPT " + respond + " " +  user_.ip).c_str());
            deliver(error.c_str());
            return;
        }
    }
    error = "CALLACCEPT FAILED";
    deliver(error.c_str());
}

void session::do_protocol(std::string protocol) {
    const auto &protocols = protocols_;
    auto self(shared_from_this());

    std::cout << "protocol: " << std::endl;
    if (protocol.empty())
        return;
    try {
        size_t pos = protocol.find(" ");

        if (pos == std::string::npos)
            pos = 0;
        std::vector<std::string> arg;
        std::stringstream ss (protocol);
        std::string item;

        while (getline (ss, item, ' '))
            arg.push_back (item);

        std::string id(arg[0]);
        std::cout << "id: " << id << std::endl;
        const auto &ret = protocols_.find(id);
        if (ret == protocols.end())
            std::cerr << "this protocol doesn't existe: " << id << std::endl;
        else
            ret->second(self, arg);

    } catch(std::exception& e) {}
}

void session::do_write()
{
    auto self(shared_from_this());
    std::cout << "message envoyé: " << write_msgs_.front().get_data() << std::endl;

    boost::asio::async_write(socket_,
    boost::asio::buffer(write_msgs_.front().get_data(),
      write_msgs_.front().get_length()),
    [this, self](boost::system::error_code ec, std::size_t /*length*/)
    {
      if (!ec)
      {
        write_msgs_.pop_front();
        if (!write_msgs_.empty())
        {
          do_write();
        }
      }
      else
      {
          std::cerr << "handle write: " << ec.message() << std::endl;

      }
    });
}

//----------------------------------------------------------------------
