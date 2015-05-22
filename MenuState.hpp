#ifndef _MENUSTATE_HPP__
#define _MENUSTATE_HPP__

#include "State.hpp"

#include <SFML/Graphics.hpp>

class MenuState : public State {

public:

	MenuState(StateStack& stateStack, ShareView shareView);

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

private:

	void setText(sf::Font& font, sf::Vector2f viewSize);
	void updateOption();

	enum Options {

		Play,
		Settings,
		Quit
	};

	sf::Sprite background;
	std::vector<sf::Text> options;
	unsigned int optionIndex;

};

#endif