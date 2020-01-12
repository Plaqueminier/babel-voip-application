/*
** EPITECH PROJECT, 2019
** include
** File description:
** include
*/

#ifndef _LOGIN_
#define _LOGIN_

#include "include.hpp"
#include "networkManager.hpp"

class Core;

/*! \class Login
 * \brief classe permettant de gérer le gui de login de notre client
 *
 * fonctions importantes :
 *      updateGui : Parcour la liste des évenements et actualise le gui en fonction
 *      startGUI : lance le gui
 *      stopGUI : stop le gui
 *
 *      Interpreter pointer sur fonction des différents codes de la classe event
 */

class Login : public QWidget, private Ui::login
{
    Q_OBJECT

    public:
        Login(Core *core);
        virtual ~Login() {};
        void startGUI();
        void stopGUI();
        typedef void (Login::*netcodeInterpreter)(QString data);
        void loginCallBack(QString data);
        void LoginFailCallBack(QString data);
        void newClient(QString data);
        void clientLeft(QString data);

    private slots:
        void updateGui();
        void on_Login_clicked();
        void on_ServerIp_returnPressed();
        void on_SignIn_clicked();
        void connecting(QString data);
        void disconect(QString data);
        void errorSocket(QString);

    private:
        netcodeInterpreter Interpreter[13];
        QTimer *timer;
        QString name;
        Core *coreRef;

};

#endif
