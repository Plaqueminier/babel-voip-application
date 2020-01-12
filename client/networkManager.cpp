/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "networkManager.hpp"
#include "AudioThread.hpp"

NetworkManager::NetworkManager() : packetReceived(0, nullptr)
{
    // setupUi(this);
    // eventManager = new Event;
    socket = new QTcpSocket(this);
    socket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);
    connect(socket, SIGNAL(readyRead()), this, SLOT(getServerMsg()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecting()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconect()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSocket(QAbstractSocket::SocketError)));

    // clientsIpList << "10.101.52.206";

    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::Any, 30000, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);
    msgSocket = new QUdpSocket(this);
    connect(msgSocket, &QUdpSocket::readyRead, this, &NetworkManager::getClientMsg);
    msgSocket->bind(QHostAddress::Any, 8181, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    msgSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);
}

void NetworkManager::addToMsg(QString ip)
{
    clientsIpList << ip;
}

void NetworkManager::removeFromMsg(QString ip)
{
    clientsIpList.clear();
    // for (auto clientIp : clientsIpList) {
    //     if (clientIp == ip)
    //         clientsIpList.removeOne(clientIp);
    // }
}

void NetworkManager::addToCall(QString ip)
{
    clientIncall << ip;
}

void NetworkManager::removeFromCall(QString ip)
{
    clientIncall.clear();
    // for (auto clientIp : clientIncall) {
    //     if (clientIp == ip)
    //         clientIncall.removeOne(clientIp);
    // }
}

Event &NetworkManager::getEventManager()
{
    return (eventManager);
}
QString NetworkManager::getServerSocketMsg()
{
    return(QString::fromStdString(socket->readAll().toStdString()));
}

void NetworkManager::getClientMsg()
{
    while (msgSocket->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(msgSocket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        msgSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
        eventManager.addToList(NetworkCode::TextMsg, QString::fromStdString(buffer.toStdString()));
    }
}

void NetworkManager::connectToServer(QString ip)
{
    socket->abort();
    socket->connectToHost(ip, 8080);
    if (socket->waitForConnected(-1) == false)
        return;
}

bool NetworkManager::isConnected()
{
    if (socket->state() == QTcpSocket::ConnectedState)
        return (true);
    return (false);
}

void NetworkManager::sendPaquet(QString data, NetworkCode::messageType type)
{

    QByteArray paquet;

    paquet.append(data);
    if (type == NetworkCode::Text) {
        for (int i = 0; i < clientsIpList.size(); i++) {
            qDebug() << clientsIpList[i];
            udpSocket->writeDatagram(paquet, QHostAddress(clientsIpList[i]), 8181);
        }
    } if (type == NetworkCode::Server)
        socket->write(paquet);
}

void NetworkManager::sendPaquet(char *data, int size, NetworkCode::messageType type)
{
    QByteArray paquet;

    paquet.append(data);
    if (type == NetworkCode::Voice) {
        for (int i = 0; i < clientIncall.size(); i++) {
            udpSocket->writeDatagram(data, size, QHostAddress(clientIncall[i]), 30000);
        }
    } if (type == NetworkCode::Server)
        socket->write(paquet);
}

void NetworkManager::getServerMsg()
{
    QString msg = getServerSocketMsg();
    QStringList msgList = msg.split(';');
    for ( const auto& i : msgList)
    {
        if (i == "")
            return;
        qDebug() << i;
        QStringList params = i.split(" ");
        if (params[0] == "LOGIN") {
            if (params[1] == "SUCCESS") {
                params.removeFirst();
                params.removeFirst();
                eventManager.addToList(NetworkCode::LoginSuccess, params.join(" "));
            }
            else if (params[1] == "FAILED")
                eventManager.addToList(NetworkCode::LoginFail, "");
        }
        else if (params[0] == "CALLREQUEST") {
            if (params[1] == "SUCCESS")
                eventManager.addToList(NetworkCode::CallAccepted, "waiting");
            else
                eventManager.addToList(NetworkCode::IncommingCall, params[1] + " " + params[2]);
        }
        else if (params[0] == "CALLACCEPT") {
            if (params[1] == "SUCCESS" && params.size() == 3)
                eventManager.addToList(NetworkCode::CallAccepted, params[2]);
            else if (params[1] == "SUCCESS")
                eventManager.addToList(NetworkCode::CallAccepted, "waiting");
            if (params[1] == "FAILED")
                eventManager.addToList(NetworkCode::CallRefused, "");
        }
        else if (params[0] == "CALLTRANSFERT") {
            if (params[1] == "SUCCESS")
                eventManager.addToList(NetworkCode::CallTransfertAccepted, "");
            if (params[1] == "FAILED")
                eventManager.addToList(NetworkCode::CallTransfertRefused, "");
        }
        else if (params[0] == "CALLSTOP")
            eventManager.addToList(NetworkCode::CallTransfertRefused, "");
        else if (params[0] == "CLIENT_CONNECT")
            eventManager.addToList(NetworkCode::NewClient, params[1] + " " + params[2]);
        else if (params[0] == "CLIENT_DISCONNECT")
            eventManager.addToList(NetworkCode::ClientLeft, params[1]);
        else if (params[0] == "ADDFRIEND")
            qDebug() << "accepte";
        else if (params[0] == "IPREQUEST")
            qDebug() << "accepte";
    }
}

void NetworkManager::abortServer()
{
    socket->abort();
}

void NetworkManager::connecting()
{
    eventManager.addToList(NetworkCode::Connected, "");
}

void NetworkManager::disconect()
{
    socket->abort();
    eventManager.addToList(NetworkCode::Disconected, "");
}

void NetworkManager::errorSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur)
    {
        case QAbstractSocket::HostNotFoundError:
            eventManager.addToList(NetworkCode::Socket_Error, "<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            eventManager.addToList(NetworkCode::Socket_Error, tr("<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            eventManager.addToList(NetworkCode::Socket_Error, tr("<em>ERREUR : le serveur a coupé la connexion.</em>"));
            break;
        default:
            eventManager.addToList(NetworkCode::Socket_Error, tr("<em>ERREUR : ") + socket->errorString() + tr("</em>"));
    }
}

QUdpSocket *NetworkManager::getUdpSocket() const
{
    return (udpSocket);
}
