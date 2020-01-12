/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "../include/message.hpp"
#include <iostream>

message::message()
: body_length_(0)
{
}

const char* message::get_data() const
{
    return data_;
}

char* message::get_data()
{
    return data_;
}

std::size_t message::get_length() const
{
    return body_length_;

}

const char* message::get_body() const
{
    return data_;

}

char* message::get_body()
{
    return data_;

}

std::size_t message::get_body_length() const
{
    return body_length_;
}

void message::set_body_length(std::size_t new_length)
{
    body_length_ = new_length;
    if (body_length_ > max_body_length)
      body_length_ = max_body_length;
}
