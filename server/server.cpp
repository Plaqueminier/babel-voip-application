/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include "../include/server.hpp"

using boost::asio::ip::tcp;

server::server(int port)
:
    io_service_(),
    ip_(tcp::v4()),
    endpoint_(ip_, port),
    acceptor_(io_service_, endpoint_),
    socket_(io_service_)
{
    do_accept();
    io_service_.run();

}


void server::do_accept()
{
    acceptor_.async_accept(socket_, [this](boost::system::error_code ec)
    {
      if (!ec)
      {
        std::cout << socket_.remote_endpoint().address().to_string() << std::endl;
        create_session(std::move(socket_), std::make_shared<Database>(database_), room_)->start();
    } else {
        std::cout << ec.message() << std::endl;
    }
      do_accept();
    });
}

std::shared_ptr<Isession> server::create_session(tcp::socket socket, std::shared_ptr<Database> database, room &room)
{
    return std::make_shared<session>(std::move(socket), std::move(database), room);
}

//----------------------------------------------------------------------
