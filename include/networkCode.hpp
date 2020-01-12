/*
** EPITECH PROJECT, 2019
** include
** File description:
** include
*/

#ifndef _NETWORK_CODE_
#define _NETWORK_CODE_

/*! \namespace NetworkCode
 *
 * espace de nommage regroupant les outils composants
 * les codes du serveur et au network Manager
 */

namespace NetworkCode {
    /**
     * \enum messageType
     * \brief liste des moyens de communication pour les sockets
     *
     * chaque type permet d'envoyer un type de message différents au serveur ou au client
     */
    enum messageType {
        Server, /*!< Envoyer un message au serveur */
        Voice, /*!< Envoyer un packet vocal au client */
        Text /*!<  Envoyer un packet textuel au client */
    };

    /**
     * \enum netEvent
     * \brief liste des évenements pouvant être levé par le network manager
     *
     * chaque type renvoie à un évenement qui sera levé quand le network manager recevera un message lui correspondant
     */
    enum netEvent {
        Connected, /*!< Connexion au serveur */
        Disconected, /*!< Déconnexion du serveur */
        Socket_Error, /*!< Une erreur a été reçus */
        LoginSuccess, /*!< Connexion du client au serveur réussi */
        LoginFail, /*!<  Connexion du client au serveur échoué */
        Register, /*!<  Enregistrement du client au serveur */
        VoiceMsg, /*!< Packet audio reçu */
        TextMsg, /*!< Packet textuel reçu */
        CallAccepted, /*!<  Un appel a été accepté*/
        CallRefused, /*!<  Un appel a été rejeté*/
        IncommingCall, /*!< Une demande d'appel a été envoyée */
        NewClient, /*!<  Un amis c'est connecté*/
        ClientLeft, /*!< Un amis c'est déconnecté */
        CallTransfertAccepted, /*!<  Un client a accepté l'appel*/
        CallTransfertRefused /*!<  Un client a refusé ou coupé l'appel*/
    };
}


#endif
