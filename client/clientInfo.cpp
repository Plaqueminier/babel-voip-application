/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "clientInfo.hpp"

ClientInfo::ClientInfo()
{
    state = Connected;
    soundState = true;
    micState = true;
}

ClientInfo::~ClientInfo()
{
}

void ClientInfo::setPseudo(QString nPseudo)
{
    pseudo = nPseudo;
}

void ClientInfo::setSoundState(bool nSoundState)
{
    soundState = nSoundState;
}

void ClientInfo::setMicState(bool nMicState)
{
    micState = nMicState;
}

void ClientInfo::setState(connectingState nstate)
{
    state = nstate;
}

QString ClientInfo::getPseudo()
{
    return (pseudo);
}
bool ClientInfo::getSoundState()
{
    return (soundState);
}

bool ClientInfo::getMicState()
{
    return (micState);
}

connectingState ClientInfo::getState()
{
    return (state);
}
