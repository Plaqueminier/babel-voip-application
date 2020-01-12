/*
** EPITECH PROJECT, 2019
** include
** File description:
** include
*/

#ifndef _CORE_
#define _CORE_

#include "include.hpp"
#include "networkManager.hpp"
#include "AudioThread.hpp"

class GUI;
class Login;
class Call;
class ClientInfo;

/*! \class Core
 * \brief classe permettant de regrouper les différents éléments du programme
 *
 *  La classe gere les différentes parties pour leur permettre d'intéragir entre eux plus facilement
 */

class Core
{
    public:
        /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe Core
         */
        Core();
        /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe Core
         */
        ~Core();
        /*!
         *  \brief Change de gui
         *
         */
        void changeGui(QString name);

        /*!
         *  \brief Début du programme
         *
         * Lance le programme depuis le main
         */
        void run();

        /*!
         *  \brief lance un son
         *
         *
         * \param name : nom du son
         */
        void playSound(QString name);

        /*!
         *  \brief Stop un son
         *
         *
         * \param name : nom du son
         */
        void stopSound(QString name);

        /*!
         *  \brief ClientInfo getteur
         *
         *  Récupere la classe ClientInfo
         *
         */
        ClientInfo *getClientInfo();

        /*!
         *  \brief INetworkManager getteur
         *
         *  Récupere la classe INetworkManager
         *
         */
        INetworkManager *getNetworkManager();

        /*!
         *  \brief Sound::AudioThread getteur
         *
         *  Récupere la classe Sound::AudioThread
         *
         */
        Sound::AudioThread &getAudioThread();

        /*!
         *  \brief Call  getteur
         *
         *  Récupere la classe Call
         *
         */
        Call *getCallGUI();

        /*!
         *  \brief GUI getteur
         *
         *  Récupere la classe GUI
         *
         */
        GUI *getClientGUI();

    private:
        INetworkManager *netClient; /*!< Network manager*/
        Login *loginGUI; /*!< Gui de login du client*/
        Call *callGUI; /*!< gui pop up lors d'un appel*/
        GUI *clientGUI; /*!< gui principal*/
        QString actualUi; /*!< gui en cour d'utilisation*/
        ClientInfo *info; /*!< information sur le client*/
        std::vector<std::pair<QString, QSound*>> sounds; /*!< Liste des son*/
        Sound::AudioThread audioThread; /*!< audioThread*/
};

#endif
