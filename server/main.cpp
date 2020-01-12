/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <list>
#include "../include/server.hpp"
#include <sqlite_orm/sqlite_orm.h>

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: server <port> [<port> ...]\n";
      return 1;
    }
    server server(std::atoi(argv[1]));
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
