/*
** EPITECH PROJECT, 2019
** include
** File description:
** include
*/

#ifndef _INETWORK_
#define _INETWORK_

#include "networkCode.hpp"
#include "event.hpp"

namespace Sound
{
    class AudioThread;
}

class INetworkManager : public QWidget
{
    public:
        virtual ~INetworkManager() {};
        virtual void sendPaquet(QString message, NetworkCode::messageType type) = 0;
        virtual void sendPaquet(char *data, int size, NetworkCode::messageType type) = 0;
        virtual QString getServerSocketMsg() = 0;
        virtual void getClientMsg() = 0;
        virtual Event &getEventManager() = 0;
        virtual void connectToServer(QString ip) = 0;
        virtual void getServerMsg() = 0;
        virtual void connecting() = 0;
        virtual void disconect() = 0;
        virtual bool isConnected() = 0;
        virtual void errorSocket(QAbstractSocket::SocketError erreur) = 0;
        virtual QUdpSocket *getUdpSocket() const = 0;
        virtual void addToCall(QString ip) = 0;
        virtual void removeFromCall(QString ip) = 0;
        virtual void addToMsg(QString ip) = 0;
        virtual void removeFromMsg(QString ip) = 0;
        virtual void abortServer() = 0;
};

#endif
