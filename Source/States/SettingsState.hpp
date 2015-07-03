#ifndef _SETTINGSSTATE_HPP__
#define _SETTINGSSTATE_HPP__

#include "State.hpp"
#include "PlayerInput.hpp"
#include "Button.hpp"
#include "Container.hpp"

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

class SettingsState : public State {

public:

	SettingsState(StateStack& stateStack, ShareView shareView);

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

private:

	void updateControl();

	sf::Sprite background;
	Container container;
	sf::Text upText, downText, leftText, rightText, attackText;
	Button::buttonPtr walkUpButton, walkDownButton, walkLeftButton, walkRightButton, attackButton;
	std::map<PlayerInput::PlayerAction, std::string> actionStringMap;
};

#endif