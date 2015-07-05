#ifndef _MULTIPLAYERGAMESTATE_HPP__
#define _MULTIPLAYERGAMESTATE_HPP__

#include "State.hpp"
#include "World.hpp"
#include "PlayerInput.hpp"
#include "MultiplayerServer.hpp"
#include "NetworkInfo.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>

class MultiplayerGameState : public State {

public:

	MultiplayerGameState(StateStack& stateStack, ShareView shareView, bool isHost);
	~MultiplayerGameState();

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

private:

	std::unique_ptr<MultiplayerServer> server;
	sf::TcpSocket socket;
	sf::Clock failedConnectionClock;
	sf::Clock tickClock;
	sf::Time lastPacketTime;
	sf::Time timeOut;

	bool isConnected;
	bool isHost;
	bool gameStarted;
	bool activeState, isFocused;
	World world;
	PlayerInput& playerInput;
};

#endif