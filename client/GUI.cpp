/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "GUI.hpp"
#include "core.hpp"
#include "Call.hpp"
#include "clientInfo.hpp"

GUI::GUI(Core *core)
{
    setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGui()));

    coreRef = core;
    Username->setStyleSheet("color: white");
    FriendName->setStyleSheet("color: white");
    label_2->setStyleSheet("color: white");
    label_3->setStyleSheet("color: grey");
    Status->setStyleSheet("font: 20pt;");
    message->hide();
    ListeMessage->hide();
    send->hide();
    Call->hide();
    hangup->hide();
    message->setStyleSheet("color: white; background-color: rgb(66, 68, 71, 255);");
    AddFriendLine->setStyleSheet("color: white");
    ListeMessage->setStyleSheet("QTextEdit { color: #99AAB5; background-color: rgb(66, 68, 71, 255);}");
    listView->setIconSize(QSize(10, 10));
    listView->setStyleSheet("QListWidget {padding: 5px;} QListWidget::item { margin: 10px; } QListView::item:selected { background-color: rgb(66, 68, 71);}");
    connect(listView, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()), Qt::QueuedConnection);
    Interpreter[0] = &GUI::errorSocket;
    Interpreter[1] = &GUI::disconect;
    Interpreter[2] = &GUI::errorSocket;
    Interpreter[3] = &GUI::errorSocket;
    Interpreter[4] = &GUI::errorSocket;
    Interpreter[5] = &GUI::errorSocket;
    Interpreter[6] = &GUI::errorSocket;
    Interpreter[7] = &GUI::textMsg;
    Interpreter[8] = &GUI::callAccepted;
    Interpreter[9] = &GUI::callRefused;
    Interpreter[10] = &GUI::incommingCall;
    Interpreter[11] = &GUI::newClient;
    Interpreter[12] = &GUI::clientLeft;
    Interpreter[13] = &GUI::callTransfertAccepted;
    Interpreter[14] = &GUI::callTransfertRefused;
}

void GUI::startGUI()
{
    timer->start(80);
    this->show();
    Username->setText(coreRef->getClientInfo()->getPseudo());
}

void GUI::stopGUI()
{
    timer->stop();
    this->hide();
}

void GUI::selectionChanged()
{
    message->show();
    ListeMessage->show();
    send->show();
    Call->show();
    hangup->show();
    label->hide();
    label_3->hide();
    if (listView->selectedItems().size() == 0) {
        message->hide();
        ListeMessage->hide();
        send->hide();
        Call->hide();
        hangup->hide();
        label->show();
        label_3->show();
    }
    if (listView->count() == 0 || coreRef->getClientInfo()->getState() == connectingState::Off)
        return;
    FriendName->setText(listView->currentItem()->text());
    ListeMessage->clear();
    coreRef->getNetworkManager()->removeFromMsg("");
    if (msgList.find(FriendName->text()) != msgList.end()) {
        coreRef->getNetworkManager()->addToMsg(contactlist[FriendName->text()]);
        QStringList tmp = msgList[FriendName->text()];
        for (auto msg : tmp)
            ListeMessage->append(msg);
    }
    for(int i = 0; i < listView->count(); ++i)
    {
        if (listView->item(i)->text() == listView->currentItem()->text()) {
            listView->item(i)->setForeground(QColor("#99AAB5"));
            listView->item(i)->setIcon(QIcon());
        }
    }
}

void GUI::updateGui()
{
    std::list<Event_t> tmp = coreRef->getNetworkManager()->getEventManager().getEventList();
    std::list<Event_t>::iterator it;
    for (it = tmp.begin(); it != tmp.end(); ++it) {
        if (Interpreter[it->code])
            (this->*Interpreter[it->code])(it->data);
    }
}

void GUI::incommingCall(QString data)
{
    coreRef->getNetworkManager()->getEventManager().removeFromList();
    coreRef->getCallGUI()->startGUI();
    coreRef->getCallGUI()->setUsername(data.split(" ")[0]);
    inWaitCall = data.split(" ")[1];
    coreRef->playSound("Call");
}

void GUI::callRefused(QString data)
{
    coreRef->getNetworkManager()->getEventManager().removeFromList();
    coreRef->stopSound("Call");
    Status->setText("");
    coreRef->getClientInfo()->setState(connectingState::Connected);
}

void GUI::callAccepted(QString data)
{
    if (coreRef->getAudioThread().isPaused()) {
        std::cout << "start thread" << std::endl;
        coreRef->getAudioThread().togglePause();
    }
    coreRef->getNetworkManager()->getEventManager().removeFromList();
    coreRef->stopSound("Call");
    coreRef->playSound("Join");
    Status->setText("<font color='green'>Connected</font>");
    if (data != "waiting")
        coreRef->getNetworkManager()->addToCall(data);
    else
        coreRef->getNetworkManager()->addToCall(inWaitCall);
    coreRef->getClientInfo()->setState(connectingState::InCall);
}

void GUI::textMsg(QString data)
{
    coreRef->getNetworkManager()->getEventManager().removeFromList();
    coreRef->playSound("Notification");
    QString test = data;
    QStringList tmp = test.split(":");
    QStringList tmpList;
    if (test.split("<strong>")[1] == FriendName->text()) {
        ListeMessage->append(tmp[0] + ":");
        tmp.removeFirst();
        ListeMessage->append(tmp.join(":"));
        tmpList = msgList[FriendName->text()];
    } else
        tmpList = msgList[test.split("<strong>")[1]];
    tmp = test.split(":");
    tmpList.append(tmp[0] + ":");
    tmp.removeFirst();
    tmpList.append(tmp.join(":"));
    msgList[test.split("<strong>")[1]] = tmpList;
    for(int i = 0; i < listView->count(); ++i)
    {
        if (listView->item(i)->text() == test.split("<strong>")[1]) {
            listView->item(i)->setForeground(Qt::red);
            listView->item(i)->setIcon(QIcon("../Ressources/redDot.png"));
        }
    }
}

void GUI::newClient(QString data)
{
    if (data.split(" ")[0] != Username->text()) {
        QListWidgetItem *item = new QListWidgetItem(data.split(" ")[0]);
        listView->addItem(item);
        contactlist[data.split(" ")[0]] = data.split(" ")[1];
    }
    if (msgList.find(data.split(" ")[0]) == msgList.end())
        msgList[data.split(" ")[0]] = QStringList();
    coreRef->getNetworkManager()->getEventManager().removeFromList();
}

void GUI::clientLeft(QString data)
{
    coreRef->getNetworkManager()->getEventManager().removeFromList();
    for ( int a = 0; a < listView->count(); a++ )
    {
        if (listView->item(a)->text() == data)
        {
            delete listView->takeItem(a);
            break;
        }
    }
}

void GUI::callTransfertAccepted(QString data)
{
    coreRef->playSound("Call");
    coreRef->getNetworkManager()->getEventManager().removeFromList();
    Status->setText("<font color='green'>Connecting ...</font>");
}

void GUI::callTransfertRefused(QString data)
{
    if (!coreRef->getAudioThread().isPaused()) {
        coreRef->getAudioThread().togglePause();
        while (!coreRef->getAudioThread().isPaused()) {}
    }
    coreRef->getNetworkManager()->getEventManager().removeFromList();
    coreRef->getNetworkManager()->removeFromCall("");
    Status->setText("");
    coreRef->getClientInfo()->setState(connectingState::Connected);
}

void GUI::disconect(QString data)
{
    coreRef->getNetworkManager()->getEventManager().removeFromList();
    coreRef->changeGui("loginGUI");
    ListeMessage->clear();
    listView->clear();
    message->clear();
}

void GUI::errorSocket(QString data)
{
    coreRef->getNetworkManager()->getEventManager().removeFromList();
    coreRef->changeGui("loginGUI");
}

void GUI::on_message_returnPressed()
{
    coreRef->getNetworkManager()->sendPaquet(QString(tr("<strong>") + Username->text() + tr("<strong> :")) + QString(message->text()), NetworkCode::Text);
    ListeMessage->append(QString(tr("<strong>") + Username->text() + tr("<strong> :")));
    ListeMessage->append(QString(message->text()));
    QStringList tmp = msgList[FriendName->text()];
    tmp.append(QString(tr("<strong>") + Username->text() + tr("<strong> :")));
    tmp.append(QString(message->text()));
    msgList[FriendName->text()] = tmp;
    message->clear();
    message->setFocus();
}

void GUI::on_send_clicked()
{
    on_message_returnPressed();
}

void GUI::on_Call_clicked()
{
    if (coreRef->getClientInfo()->getState() == connectingState::InCall)
        return;
    coreRef->getClientInfo()->setState(connectingState::InCall);
    coreRef->getNetworkManager()->sendPaquet("CALLTRANSFERT " + FriendName->text(), NetworkCode::Server);
}

void GUI::on_hangup_clicked()
{
    if (coreRef->getClientInfo()->getState() != connectingState::InCall)
        return;
    coreRef->getClientInfo()->setState(connectingState::Connected);
    coreRef->getNetworkManager()->sendPaquet("CALLSTOP " + FriendName->text(), NetworkCode::Server);
    coreRef->getNetworkManager()->removeFromCall("");
    Status->setText("");
}

void GUI::on_logout_clicked()
{
    coreRef->getNetworkManager()->sendPaquet("LOGOUT " + Username->text(), NetworkCode::Server);
    coreRef->changeGui("loginGUI");
    coreRef->getNetworkManager()->abortServer();
    ListeMessage->clear();
    listView->clear();
    message->clear();
    coreRef->getClientInfo()->setState(connectingState::Off);
}

void GUI::closeEvent(QCloseEvent *bar)
{
    coreRef->stopSound("Call");
    coreRef->getNetworkManager()->sendPaquet("LOGOUT " + Username->text(), NetworkCode::Server);
    coreRef->getNetworkManager()->abortServer();
    ListeMessage->clear();
    listView->clear();
    message->clear();
    coreRef->getClientInfo()->setState(connectingState::Off);
}

void GUI::on_AddFriend_clicked()
{
    coreRef->getNetworkManager()->sendPaquet("ADDFRIEND " + AddFriendLine->text(), NetworkCode::Server);
    AddFriendLine->clear();
}

void GUI::on_AddFriendLine_returnPressed()
{
    on_AddFriend_clicked();
}
