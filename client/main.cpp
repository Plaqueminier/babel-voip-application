/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "include.hpp"
#include "networkManager.hpp"
#include "GUI.hpp"
#include "core.hpp"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	// ClientNet client;
	// client.show();
	// GUI clientGUI;
	// clientGUI.startGUI();
	Core core;
	core.run();
	// clientGUI.client.show();

    return app.exec();
}
