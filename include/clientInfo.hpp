/*
** EPITECH PROJECT, 2019
** include
** File description:
** include
*/

#ifndef _CLIENT_INFO_
#define _CLIENT_INFO_

#include "include.hpp"

/**
 * \enum connectingState
 * \brief liste les états possible pour un client
 *
 */
enum connectingState {
    Connected, /*!< connecté */
    Off, /*!< deconnecté */
    InCall /*!< en appel */
};

/*! \class ClientInfo
 * \brief Information utile sur le client connecté
 */

class ClientInfo
{
    public:
        ClientInfo();
        ~ClientInfo();
        void setPseudo(QString);
        void setSoundState(bool);
        void setMicState(bool);
        void setState(connectingState);

        QString getPseudo();
        bool getSoundState();
        bool getMicState();
        connectingState getState();
    private:
        QString pseudo;
        bool soundState;
        bool micState;
        connectingState state;
};

#endif
