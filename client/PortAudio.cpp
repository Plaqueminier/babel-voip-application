/*
** EPITECH PROJECT, 2019
** Header
** File description:
** Header
*/

#include "PortAudio.hpp"

Sound::PortAudio::PortAudio()
{
	_err = Pa_Initialize();
	if (_err != paNoError)
		std::cerr << Pa_GetErrorText(_err) << std::endl;
	_numChannels = 2;
	_sampleRate = 48000;
	_framesPerBuffer = 1024;
	_inputBuffer = static_cast<char *>(malloc(sizeof(paInt32) * _framesPerBuffer * _numChannels));
	for (int i = 0; i < (sizeof(paInt32) * _framesPerBuffer * _numChannels); i++)
		_inputBuffer[i] = 0;
	_err = Pa_OpenDefaultStream(&_inputStream, _numChannels, 0, paInt32, _sampleRate, _framesPerBuffer, nullptr, nullptr);
	if (_err != paNoError)
		std::cerr << Pa_GetErrorText(_err) << std::endl;
	_err = Pa_OpenDefaultStream(&_outputStream, 0, _numChannels, paInt32, _sampleRate, _framesPerBuffer, nullptr, nullptr);
	if (_err != paNoError)
		std::cerr << Pa_GetErrorText(_err) << std::endl;
	_err = Pa_StartStream(_inputStream);
	if (_err != paNoError)
		std::cerr << Pa_GetErrorText(_err) << std::endl;
	_err = Pa_StartStream(_outputStream);
	if (_err != paNoError)
		std::cerr << Pa_GetErrorText(_err) << std::endl;
}

Sound::PortAudio::~PortAudio()
{
	free(_inputBuffer);
	Pa_StopStream(_inputStream);
	if (_err != paNoError)
		std::cerr << Pa_GetErrorText(_err) << std::endl;
	Pa_StopStream(_outputStream);
	if (_err != paNoError)
		std::cerr << Pa_GetErrorText(_err) << std::endl;
	Pa_CloseStream(_inputStream);
	if (_err != paNoError)
		std::cerr << Pa_GetErrorText(_err) << std::endl;
	Pa_CloseStream(_outputStream);
	_err = Pa_Terminate();
	if (_err != paNoError)
		std::cerr << Pa_GetErrorText(_err) << std::endl;
}

char *Sound::PortAudio::record()
{
	_err = Pa_ReadStream(_inputStream, _inputBuffer, _framesPerBuffer);
	if (_err != paNoError)
		std::cerr << Pa_GetErrorText(_err) << std::endl;
	return (_inputBuffer);
}

void Sound::PortAudio::play(char *buffer)
{
	_err = Pa_WriteStream(_outputStream, buffer, _framesPerBuffer);
	if (_err != paNoError)
		std::cerr << Pa_GetErrorText(_err) << std::endl;
}
