/*
** EPITECH PROJECT, 2019
** include
** File description:
** include
*/

#ifndef _NETWORK_
#define _NETWORK_

#include "event.hpp"
#include "INetworkManager.hpp"

namespace Sound
{
    class AudioThread;
}

/*! \class NetworkManager
 * \brief classe permettant de gérer le réseau
 *
 *  La classe gere les différentes permettant de gérer le réseau comme envoyer des paquets,
 *  la communication avec le serveur ou entre les clients
 */

class NetworkManager : public INetworkManager
{
    Q_OBJECT

    public:
        /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe NetworkManager
         */
        NetworkManager();

        /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe NetworkManager
         */
        ~NetworkManager() {};

        /*!
         *  \brief  Envoie un paquet
         *
         *  Envoie un packet en utilisant des sockets udp ou tcp
         * \param message : message a envoyer , type : destination du message (serveur, voix, texte)
         */
        void sendPaquet(QString message, NetworkCode::messageType type);

        /*!
         *  \brief  Envoie un paquet
         *
         * \param data : message, size : taille, type : destination
         */
        void sendPaquet(char *data, int size, NetworkCode::messageType type);

        /*!
         *  \brief  get le message du serveur et le renvois en qstring
         */
        QString getServerSocketMsg();

        /*!
         *  \brief  get le message d'un client
         */
        void getClientMsg();

        /*!
         *  \brief  get la socket audio
         */
        QUdpSocket *getUdpSocket() const;

        /*!
         *  \brief  get l'event manager
         */
        Event &getEventManager();

        /*!
         *  \brief  Connexion au serveur
         *
         * \param ip : ip du serveur
         */
        void connectToServer(QString ip);
        /*!
         *  \brief  État de la connexion au serveur
         */
        bool isConnected();
        /*!
         *  \brief  Ajoute un client a l'appel
         *
         * \param ip : ip du client
         */
        void addToCall(QString ip);
        /*!
         *  \brief  Retire un client de l'appel
         * \param ip : ip du client
         */
        void removeFromCall(QString ip);
        /*!
         *  \brief Ajoute un client à la conversation textuel
         *
         * \param ip : ip du client
         */
        void addToMsg(QString ip);
        /*!
         *  \brief  Retire un client de la conversation textuel
         * \param ip : ip du client
         */
        void removeFromMsg(QString ip);
        /*!
         *  \brief  Coupe la connexion avec le serveur
         */
        void abortServer();

    private slots:
        void getServerMsg();
        void connecting();
        void disconect();
        void errorSocket(QAbstractSocket::SocketError erreur);

    private:
        Event eventManager; /*!< event Manager*/
        QTcpSocket *socket; /*!< socket du serveur*/
        QUdpSocket *udpSocket; /*!< socket audio*/
        QUdpSocket *msgSocket; /*!< socket textuel*/
        QList<QString> clientsIpList; /*!< Liste des ip textuel*/
        QList<QString> clientIncall; /*!< liste des ip audio */
        QMutex mutex; /*!< mutex audio*/
        std::pair<int, char *> packetReceived; /*!< list des packets audio reçus*/
};

#endif
