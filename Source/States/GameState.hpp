#ifndef _GAMESTATE_HPP__
#define _GAMESTATE_HPP__

#include "State.hpp"
#include "World.hpp"
#include "PlayerInput.hpp"

class GameState : public State {

public:

	GameState(StateStack& stateStack, ShareView shareView);

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

private:

	World world;
	PlayerInput& playerInput;
};

#endif