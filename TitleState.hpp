#ifndef _TITLESTATE_HPP__
#define _TITLESTATE_HPP__

#include "State.hpp"

class TitleState : public State {

public:

	TitleState(StateStack& stateStack, ShareView shareView);

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

private:

	sf::Sprite background;
	sf::Text titleText, continueText;
	bool showText;
	sf::Time textFlash;
};

#endif