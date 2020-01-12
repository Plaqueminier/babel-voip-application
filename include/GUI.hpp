/*
** EPITECH PROJECT, 2019
** include
** File description:
** include
*/

#ifndef _GUI_
#define _GUI_

#include "include.hpp"
#include "networkManager.hpp"

class Core;

/*! \class GUI
 * \brief classe permettant de gérer le gui principal de notre client
 *
 * fonctions importantes :
 *      updateGui : Parcour la liste des évenements et actualise le gui en fonction
 *      startGUI : lance le gui
 *      stopGUI : stop le gui
 *
 *      Interpreter pointer sur fonction des différents codes de la classe event
 */

class GUI : public QWidget, private Ui::GUI
{
    Q_OBJECT

    public:
        GUI(Core *core);
        virtual ~GUI() {};
        void startGUI();
        void stopGUI();
        typedef void (GUI::*netcodeInterpreter)(QString data);
        netcodeInterpreter Interpreter[15];
        void callRefused(QString);
        void callAccepted(QString);
        void textMsg(QString);
        void incommingCall(QString data);
        void newClient(QString data);
        void clientLeft(QString data);
        void callTransfertAccepted(QString data);
        void callTransfertRefused(QString data);
        void closeEvent(QCloseEvent *bar);

    private slots:
        void updateGui();
        void selectionChanged();
        void on_send_clicked();
        void on_message_returnPressed();
        void disconect(QString data);
        void errorSocket(QString);
        void on_Call_clicked();
        void on_hangup_clicked();
        void on_logout_clicked();
        void on_AddFriend_clicked();
        void on_AddFriendLine_returnPressed();

    private:
        QTimer *timer;
        QString name;
        Core *coreRef;
        QString inWaitCall;
        std::map<QString, QString> contactlist;
        std::map<QString, QStringList> msgList;

};

#endif
