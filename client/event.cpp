/*
** EPITECH PROJECT, 2019
** include
** File description:
** include
*/

#include "event.hpp"

Event::Event()
{
}

std::list<Event_t> Event::getEventList()
{
    return (EventList);
}

void Event::addToList(NetworkCode::netEvent code, QString data)
{
    Event_t newEvent;
    newEvent.code = code;
    newEvent.data = data;
    EventList.push_back(newEvent);
}

void Event::removeFromList()
{
    EventList.pop_front();
}
