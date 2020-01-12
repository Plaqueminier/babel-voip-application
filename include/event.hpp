/*
** EPITECH PROJECT, 2019
** include
** File description:
** include
*/

#ifndef _EVENT_
#define _EVENT_

#include "include.hpp"

/**
 * \struct Event_t
 * \brief Objet De liste d'évènements
 *
 * Lors d'un appel du serveur stock le code d'appel et la donnée envoyée
 */

struct Event_t {
    NetworkCode::netEvent code; /*!< Identifiant du message */
    QString data; /*!< Data exemple : texte du message */
};

/*! \class Event
 * \brief classe representant la liste des évenements
 *
 *  La classe gere une liste d'évenements en fonction des appels reçus par le serveur
 *  Permet de faire le liens entre le gui de QT et les codes du serveurs dans le network manager
 */

class Event
{
    public:
        /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe Event
         */
        Event();
        /*!
         *  \brief Ajoute à la liste d'évenements
         *
         *  Constructeur de la classe Event
         * \param code : code de l'évenement
         * \param data : donnée supplémentaire renvoyé par le serveur, exemple : un pseudo
         */
        void addToList(NetworkCode::netEvent code, QString data);
        /*!
         *  \brief Retire de la liste d'évenements
         *
         * retire le premier évenement de la liste
         */
        void removeFromList();
        /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe Event
         */
        ~Event() {};
        /*!
         *  \brief Récupère la liste d'évenements
         *
         */
        std::list<Event_t> getEventList();

    private:
        std::list<Event_t> EventList; /*!< Liste des évenements*/


};

#endif
