/*
** EPITECH PROJECT, 2019
** Header
** File description:
** Header
*/

#ifndef IAUDIOMANAGER_HPP_
#define IAUDIOMANAGER_HPP_

namespace Sound
{

	/*! \class IAudioManager
	 * \brief Classe abstraite destinée à la gestion de l'audio
	 *
	 */
	class IAudioManager
	{
	public:
		/*!
		 * \brief Destructeur
		 */
		virtual ~IAudioManager() = default;

		/*!
         * \brief Enregistre un paquet audio
         *
         * Retourne le paquet audio enregistré
		 *
         */
		virtual char *record() = 0;

		/*!
         * \brief Joue un paquet audio
         *
         * \param buffer : paquet audio à jouer
         */
		virtual void play(char *buffer) = 0;
	};
}

#endif
