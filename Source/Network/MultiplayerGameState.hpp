#ifndef _MULTIPLAYERGAMESTATE_HPP__
#define _MULTIPLAYERGAMESTATE_HPP__

#include "State.hpp"
#include "World.hpp"
#include "PlayerInput.hpp"

class MultiplayerGameState : public State {

public:

	MultiplayerGameState(StateStack& stateStack, ShareView shareView, bool isHost);
	~MultiplayerGameState();

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

private:

	typedef std::unique_ptr<PlayerInput> playerPtr;

	bool isHost;
	World world;
	PlayerInput& playerInput;
};

#endif