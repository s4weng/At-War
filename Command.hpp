#ifndef _COMMAND_HPP__
#define _COMMAND_HPP__

#include "Receiver.hpp" //Receiver.hpp

#include <functional>
#include <SFML/System.hpp>

class SceneNode;

class Command {

public:

	Command();

	std::function<void(SceneNode&, sf::Time)> action;

	int receiver;
};

#endif