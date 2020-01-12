/*
** EPITECH PROJECT, 2019
** Header
** File description:
** Header
*/

#ifndef OPUSCODEC_HPP_
#define OPUSCODEC_HPP_

#include <opus/opus.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <utility>
#include <complex>
#include <tuple>
#include "IAudioEncoder.hpp"

namespace Sound
{

	class OpusCodec : public IAudioEncoder
	{
	public:
		OpusCodec();
		~OpusCodec();
		std::pair<int, char *> encode(char *data, int frameSize, int maxDataSize);
		int decode(char *data, int frameSize, int len);

	private:
		OpusEncoder *_encoder;
		OpusDecoder *_decoder;
		short _pcm;
	};
}

#endif
