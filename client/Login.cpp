/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "Login.hpp"
#include "core.hpp"
#include "clientInfo.hpp"
#include "GUI.hpp"

Login::Login(Core *core)
{
    setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGui()));

    coreRef = core;
    Username->setStyleSheet("color: white");
    Password->setStyleSheet("color: white");
    Password->setEchoMode(QLineEdit::Password);
    ServerIp->setStyleSheet("color: white");
    Interpreter[0] = &Login::connecting;
    Interpreter[1] = &Login::disconect;
    Interpreter[2] = &Login::errorSocket;
    Interpreter[3] = &Login::loginCallBack;
    Interpreter[4] = &Login::LoginFailCallBack;
    Interpreter[5] = &Login::errorSocket;
    Interpreter[6] = &Login::errorSocket;
    Interpreter[7] = &Login::errorSocket;
    Interpreter[8] = &Login::errorSocket;
    Interpreter[9] = &Login::errorSocket;
    Interpreter[10] = &Login::errorSocket;
    Interpreter[11] = &Login::newClient;
    Interpreter[12] = &Login::clientLeft;
}

void Login::startGUI()
{
    timer->start(80);
    this->show();
    Password->clear();
    coreRef->getClientInfo()->setPseudo("");
    coreRef->getClientInfo()->setState(connectingState::Connected);
}

void Login::stopGUI()
{
    timer->stop();
    this->hide();
}

void Login::updateGui()
{
    std::list<Event_t> tmp = coreRef->getNetworkManager()->getEventManager().getEventList();
    std::list<Event_t>::iterator it;
    for (it = tmp.begin(); it != tmp.end(); ++it) {
        if (Interpreter[it->code]) {
            (this->*Interpreter[it->code])(it->data);
        }
    }
}

void Login::newClient(QString data)
{
    coreRef->getClientGUI()->newClient(data);
}

void Login::clientLeft(QString data)
{
    coreRef->getClientGUI()->clientLeft(data);
}

void Login::LoginFailCallBack(QString data)
{
    coreRef->getNetworkManager()->getEventManager().removeFromList();
    LogError->setText("<font color='red'>Wrong Username or Password</font>");
}

void Login::loginCallBack(QString data)
{
    // coreRef->getNetworkManager()->getEventManager().removeFromList();
    coreRef->getClientInfo()->setPseudo(Username->text());
    coreRef->changeGui("clientGUI");
    QStringList fList = data.split(" ");
    std::cout << "OK" << '\n';
    qDebug() << fList.size();
    if (fList.first() == "") {
        coreRef->getNetworkManager()->getEventManager().removeFromList();
        return;
    }
    std::cout << "2" << '\n';
    for (auto friends : fList)
        newClient(friends.split(":").join(" "));
}

void Login::connecting(QString data)
{
    coreRef->getNetworkManager()->getEventManager().removeFromList();
    coreRef->getClientInfo()->setState(connectingState::Connected);
    coreRef->getNetworkManager()->sendPaquet("LOGIN " + Username->text() + " " + Password->text(), NetworkCode::Server);
}

void Login::disconect(QString data)
{
    LogError->setText("<font color='red'>Can't reach Server</font>");
    coreRef->getNetworkManager()->getEventManager().removeFromList();
}

void Login::errorSocket(QString data)
{
    coreRef->getNetworkManager()->getEventManager().removeFromList();
    LogError->setText("<font color='red'>Can't reach Server</font>");
}

void Login::on_ServerIp_returnPressed()
{
    on_Login_clicked();
}

void Login::on_Login_clicked()
{
    if (Username->text() == "" || Password->text() == "") {
        LogError->setText("<font color='red'>Enter an Username and a Password</font>");
        return;
    }
    if (coreRef->getNetworkManager()->isConnected() == false) {
        coreRef->getNetworkManager()->connectToServer(ServerIp->text());
    } else
        coreRef->getNetworkManager()->sendPaquet("LOGIN " + Username->text() + " " + Password->text(), NetworkCode::Server);
}

void Login::on_SignIn_clicked()
{
    if (Username->text() == "" || Password->text() == "") {
        LogError->setText("<font color='red'>Enter an Username and a Password</font>");
        return;
    }
    if (coreRef->getNetworkManager()->isConnected() == false) {
        coreRef->getNetworkManager()->connectToServer(ServerIp->text());
        coreRef->getNetworkManager()->sendPaquet("SIGNIN " + Username->text() + " " + Password->text(), NetworkCode::Server);
    } else
        coreRef->getNetworkManager()->sendPaquet("SIGNIN " + Username->text() + " " + Password->text(), NetworkCode::Server);
}
