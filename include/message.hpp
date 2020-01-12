//
// message.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>


class message
{
public:
  enum { tcp_length = 0 };
  enum { max_body_length = 512 };

  message();

  const char* get_data() const;

  char* get_data();

  std::size_t get_length() const;

  const char* get_body() const;

  char* get_body();

  std::size_t get_body_length() const;

  void set_body_length(std::size_t new_length);

private:
  char data_[max_body_length];

  std::size_t body_length_;
};

#endif // MESSAGE_HPP
