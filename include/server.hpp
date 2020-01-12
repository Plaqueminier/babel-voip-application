#ifndef SERVER_HPP
#define SERVER_HPP

//
// server.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include "message.hpp"
#include "session.hpp"
#include "database.hpp"
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>
#include <sqlite_orm/sqlite_orm.h>
#include "room.hpp"
#include "Iserver.hpp"
using boost::asio::ip::tcp;


class server :
    public Iserver
{
public:
    ~server() {};
    server(int port);
    void do_accept();
    std::shared_ptr<Isession> create_session(tcp::socket socket, std::shared_ptr<Database> database, room &room);
private:
    Database database_;
    room room_;
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp ip_;
    tcp::endpoint endpoint_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

//----------------------------------------------------------------------

#endif
