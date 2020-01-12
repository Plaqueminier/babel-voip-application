/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "Call.hpp"
#include "core.hpp"

Call::Call(Core *core)
{
    setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGui()));

    // coreRef->getNetworkManager() = new NetworkManager();
    coreRef = core;
    Interpreter[0] = &Call::errorSocket;
    Interpreter[1] = &Call::disconect;
    Interpreter[2] = &Call::errorSocket;
}

void Call::startGUI()
{
    timer->start(80);
    this->show();
}

void Call::stopGUI()
{
    timer->stop();
    this->hide();
}

void Call::updateGui()
{
    std::list<Event_t> tmp = coreRef->getNetworkManager()->getEventManager().getEventList();
    std::list<Event_t>::iterator it;
    for (it = tmp.begin(); it != tmp.end(); ++it) {
        if (Interpreter[it->code])
            (this->*Interpreter[it->code])(it->data);
    }
}

void Call::closeEvent(QCloseEvent *bar)
{
    coreRef->stopSound("Call");
    coreRef->getNetworkManager()->sendPaquet("CALLACCEPT FAILED " + Username->text(), NetworkCode::Server);
}

void Call::setUsername(QString name)
{
    Username->setText(name);
    Username->setStyleSheet("font: 20pt;color: red");
}

void Call::on_Decline_clicked()
{
    coreRef->getNetworkManager()->sendPaquet("CALLACCEPT FAILED " + Username->text(), NetworkCode::Server);
    coreRef->stopSound("Call");
    hide();
}

void Call::on_Accept_clicked()
{
    coreRef->getNetworkManager()->sendPaquet("CALLACCEPT SUCCESS " + Username->text(), NetworkCode::Server);
    coreRef->stopSound("Call");
    hide();
}

void Call::disconect(QString data)
{
    coreRef->getNetworkManager()->getEventManager().removeFromList();
}

void Call::errorSocket(QString data)
{
    coreRef->getNetworkManager()->getEventManager().removeFromList();
}
