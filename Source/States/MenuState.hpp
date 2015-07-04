#ifndef _MENUSTATE_HPP__
#define _MENUSTATE_HPP__

#include "State.hpp"
#include "Container.hpp"

#include <SFML/Graphics.hpp>

class MenuState : public State {

public:

	MenuState(StateStack& stateStack, ShareView shareView);

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

private:

	enum Options {

		Singleplayer,
		Multiplayer,
		Settings,
		Quit
	};

	sf::Sprite background;
	Container container;
};

#endif