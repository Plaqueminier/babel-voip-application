/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "core.hpp"
#include "GUI.hpp"
#include "Login.hpp"
#include "Call.hpp"
#include "clientInfo.hpp"
#include "AudioThread.hpp"
#include "networkManager.hpp"

Core::Core() : netClient(new NetworkManager()), clientGUI(new GUI(this)), loginGUI(new Login(this)), callGUI(new Call(this)),audioThread(netClient)
{
    std::pair<QString, QSound*> newSound;
    QSound *tmp = new QSound("../Ressources/discord-call-sound.wav");
    tmp->setLoops(QSound::Infinite);
    newSound.first = "Call";
    newSound.second = tmp;
    sounds.push_back(newSound);
    tmp = new QSound("../Ressources/discord-sounds.wav");
    newSound.first = "Join";
    newSound.second = tmp;
    sounds.push_back(newSound);
    tmp = new QSound("../Ressources/discord-notification.wav");
    newSound.first = "Notification";
    newSound.second = tmp;
    sounds.push_back(newSound);
    info = new ClientInfo();
}

Core::~Core()
{
    if (audioThread.isRunning() == 1) {
        audioThread.stopThread();
        while (audioThread.isRunning() == 1) {}
    }
}

void Core::playSound(QString name)
{
    for (const std::pair<QString, QSound*> &it : sounds) {
        if (it.first == name)
            it.second->play();
    }
}

void Core::stopSound(QString name)
{
    for (const std::pair<QString, QSound*> &it : sounds) {
        if (it.first == name)
            it.second->stop();
    }
}

void Core::changeGui(QString name)
{
    if (name == "clientGUI") {
        callGUI->stopGUI();
        loginGUI->stopGUI();
        clientGUI->startGUI();
        actualUi = "clientGUI";
    }
    if (name == "loginGUI") {
        callGUI->stopGUI();
        clientGUI->stopGUI();
        loginGUI->startGUI();
        actualUi = "loginGUI";
    }
    if (name == "callGUI") {
        clientGUI->stopGUI();
        loginGUI->stopGUI();
        callGUI->startGUI();
        actualUi = "callGUI";
    }
}

Call *Core::getCallGUI()
{
    return (callGUI);
}

GUI *Core::getClientGUI()
{
    return (clientGUI);
}

void Core::run()
{
    // QObject::connect(netClient->getUdpSocket(), SIGNAL(readyRead()), &audioThread, SLOT(rcvAudioPacket()));
    audioThread.start();
    // clientGUI->startGUI();
    loginGUI->startGUI();
    actualUi = "clientGUI";
}

ClientInfo *Core::getClientInfo()
{
    return(info);
}

INetworkManager *Core::getNetworkManager()
{
    return (netClient);
}

Sound::AudioThread &Core::getAudioThread()
{
    return (audioThread);
}
