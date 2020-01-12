/*
** EPITECH PROJECT, 2019
** Header
** File description:
** Header
*/

#include "AudioThread.hpp"
#include "networkManager.hpp"
#include "networkCode.hpp"

Sound::AudioThread::AudioThread(INetworkManager *clientNet) : _audioManager(std::make_unique<Sound::PortAudio>()), _audioEncoder(std::make_unique<Sound::OpusCodec>()), _clientNet(clientNet), _stopThread(false), _paused(true), _fullPaused(true)
{
}

Sound::AudioThread::~AudioThread()
{
}

void Sound::AudioThread::run()
{
    unsigned int frameSize = 2880;
    char *data;
    while (!_stopThread) {
        while (_paused && !_stopThread)
            _fullPaused = true;
        _fullPaused = false;
        data = _audioManager->record();
        std::pair<int, char *> pair = _audioEncoder->encode(data, frameSize, frameSize * sizeof(unsigned int));
        _clientNet->sendPaquet(pair.second, pair.first, NetworkCode::Voice);
        rcvAudioPacket();
    }
}

void Sound::AudioThread::rcvAudioPacket()
{
    const unsigned int frameSize = 2880;
    char buffer[frameSize * sizeof(unsigned int)];
    if (_clientNet->getUdpSocket()->hasPendingDatagrams()) {
        qint64 size = _clientNet->getUdpSocket()->pendingDatagramSize();

        QHostAddress sender;
        quint16 senderPort;
        memset(buffer, frameSize * sizeof(unsigned int), 0);
        _clientNet->getUdpSocket()->readDatagram(buffer, size, &sender, &senderPort);

        _audioEncoder->decode(buffer, frameSize, size);
        _audioManager->play(buffer);
    }
    while (_clientNet->getUdpSocket()->hasPendingDatagrams()) {
        qint64 size = _clientNet->getUdpSocket()->pendingDatagramSize();
        _clientNet->getUdpSocket()->readDatagram(buffer, size, nullptr, nullptr);
    }
}

void Sound::AudioThread::stopThread()
{
    _stopThread = true;
}

void Sound::AudioThread::togglePause()
{
    _paused = !_paused;
}

bool Sound::AudioThread::isPaused() const
{
    return (_fullPaused);
}
