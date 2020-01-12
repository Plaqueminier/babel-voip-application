/*
** EPITECH PROJECT, 2019
** Header
** File description:
** Header
*/

#ifndef PORTAUDIO_HPP_
#define PORTAUDIO_HPP_

#include "portaudio.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "IAudioManager.hpp"

namespace Sound
{
	class PortAudio : public IAudioManager
	{
	public:
		PortAudio();
		~PortAudio();

		char *record();
		void play(char *buffer);

	private:
		PaError _err;
		PaStream *_inputStream;
		PaStream *_outputStream;
		char *_inputBuffer;
		int _numChannels;
		int _sampleRate;
		int _framesPerBuffer;
	};
}

#endif
