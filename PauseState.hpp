#ifndef _PAUSESTATE_HPP__
#define _PAUSESTATE_HPP__

#include "State.hpp"

#include <SFML/Graphics.hpp>

class PauseState : public State {

public:

	PauseState(StateStack& stateStack, ShareView shareView);

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

private:

	void setText(sf::Font& font, sf::Vector2f viewSize);
	void updateOption();

	enum Options {

		Resume,
		MainMenu,
		Quit
	};

	sf::Sprite background;
	sf::Text pausedText;

	std::vector<sf::Text> options;
	unsigned int optionIndex;
};

#endif