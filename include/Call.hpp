/*
** EPITECH PROJECT, 2019
** include
** File description:
** include
*/

#ifndef _CALL_
#define _CALL_

#include "include.hpp"
#include "networkManager.hpp"

class Core;

/*! \class Call
 * \brief classe permettant de gérer le gui d'appel de notre client
 *
 * fonctions importantes :
 *      updateGui : Parcour la liste des évenements et actualise le gui en fonction
 *      startGUI : lance le gui
 *      stopGUI : stop le gui
 *
 *      Interpreter pointer sur fonction des différents codes de la classe event
 */

class Call : public QWidget, private Ui::Call
{
    Q_OBJECT

    public:
        Call(Core *core);
        virtual ~Call() {};
        void startGUI();
        void stopGUI();
        typedef void (Call::*netcodeInterpreter)(QString data);
        void setUsername(QString name);

    private slots:
        void closeEvent(QCloseEvent *bar);
        void on_Decline_clicked();
        void on_Accept_clicked();
        void updateGui();
        void disconect(QString data);
        void errorSocket(QString);

    private:
        netcodeInterpreter Interpreter[5];
        QTimer *timer;
        QString name;
        Core *coreRef;

};

#endif
