/*
** EPITECH PROJECT, 2019
** Header
** File description:
** Header
*/

#include "OpusCodec.hpp"

Sound::OpusCodec::OpusCodec()
{
	int error;
	_encoder = opus_encoder_create(48000, 2, OPUS_APPLICATION_VOIP, &error);
	_decoder = opus_decoder_create(48000, 2, &error);
}

Sound::OpusCodec::~OpusCodec()
{
	opus_encoder_destroy(_encoder);
	opus_decoder_destroy(_decoder);
}

std::pair<int, char *> Sound::OpusCodec::encode(char *data, int frameSize, int maxDataSize)
{
	int length = opus_encode(_encoder, reinterpret_cast<opus_int16 const *>(data), frameSize, reinterpret_cast<unsigned char *>(data), maxDataSize);
	std::pair<int, char *> pair(length, data);
	if (length < 0)
		std::cerr << "Error when encoding packet" << std::endl;
	return (pair);
}

int Sound::OpusCodec::decode(char *data, int frameSize, int len)
{
	int length = opus_decode(_decoder, reinterpret_cast<unsigned char *>(data), len, reinterpret_cast<opus_int16 *>(data), frameSize, 0);
	if (length < 0)
		std::cerr << "Error when decoding packet" << std::endl;
	return (length);
}
