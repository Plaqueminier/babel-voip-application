/*
** EPITECH PROJECT, 2019
** Header
** File description:
** Header
*/

#ifndef IAUDIOENCODER_H_
#define IAUDIOENCODER_H_

namespace Sound
{

	/*! \class IAudioEncoder
	 * \brief Classe abstraite destinée à l'encodage de l'audio
	 */

	class IAudioEncoder
	{
	public:
		/*!
		 * \brief Destructeur
		 */
		virtual ~IAudioEncoder() = default;

		/*!
         * \brief  Encode un paquet audio
		 *
		 * Encode un paquet et retourne un std::pair contenant la longueur du paquet encodé et le paquet en char *
         *
         * \param data : paquet audio, frameSize : nombre de samples par canal dans le signal d'entré, maxDataSize : mémoire allouée pour le paquet encodé
         */
		virtual std::pair<int, char *> encode(char *data, int frameSize, int maxDataSize) = 0;

		/*!
         * \brief  Décode un paquet audio
		 *
		 * Décode un paquet et retourne le nombre de samples décodées
         *
         * \param data : paquet audio, frameSize : nombre de samples par canal dans le signal de sortie, len : nombre d'octets dans le paquet décodé
         */
		virtual int decode(char *data, int frameSize, int len) = 0;
	};
}

#endif
