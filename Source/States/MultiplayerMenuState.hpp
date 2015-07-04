#ifndef _MULTIPLAYERMENUSTATE_HPP__
#define _MULTIPLAYERMENUSTATE_HPP__

#include "State.hpp"
#include "Container.hpp"

#include <SFML/Graphics.hpp>

class MultiplayerMenuState : public State {

public:

	MultiplayerMenuState(StateStack& stateStack, ShareView shareView);

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

private:

	enum Options {

		Host,
		Join,
		Menu
	};

	sf::Sprite background;
	Container container;
};

#endif