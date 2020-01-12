/*
** EPITECH PROJECT, 2019
** Header
** File description:
** Header
*/

#ifndef AUDIOTHREAD_HPP_
#define AUDIOTHREAD_HPP_

#include <QtWidgets>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork>
#include <QThread>
#include "INetworkManager.hpp"
#include "IAudioManager.hpp"
#include "IAudioEncoder.hpp"
#include "PortAudio.hpp"
#include "OpusCodec.hpp"
#include <memory>
#include <QMutex>

class ClientNet;

namespace Sound
{
	class AudioThread : public QThread
	{

		Q_OBJECT

	public:
		AudioThread(INetworkManager *clientNet);
		~AudioThread();

		void run();
		void rcvAudioPacket();
		void stopThread();
		void togglePause();
		bool isPaused() const;

	private:
		std::unique_ptr<Sound::IAudioManager> _audioManager;
		std::unique_ptr<Sound::IAudioEncoder> _audioEncoder;
		INetworkManager *_clientNet;
		bool _stopThread;
		bool _paused;
		bool _fullPaused;
	};
}

#endif
