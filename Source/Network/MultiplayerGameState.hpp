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

#include <vector>
#include <string>

class MultiplayerGameState : public State {

public:

	MultiplayerGameState(StateStack& stateStack, ShareView shareView, bool isHost);
	~MultiplayerGameState();

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

private:

	void handleIncomingPacket(sf::Int32 packetType, sf::Packet packet);
	void updateBroadcastMessage(sf::Time deltaTime);

	std::vector<std::pair<sf::Text, sf::Time> > broadcastMessages;

	std::unique_ptr<MultiplayerServer> server;
	sf::TcpSocket socket;
	sf::Clock failedConnectionClock;
	sf::Clock tickClock;
	sf::Time lastPacketTime;
	sf::Time timeOut;

	bool isConnected;
	bool isHost;
	bool activeState, isFocused;

	sf::Int32 playerIDCount, enemyIDCount, projectileIDCount;
	std::map<sf::Int32, EntityInfo> playerHeroInfoMap;
	std::map<sf::Int32, EntityInfo> enemyHeroInfoMap;	
	std::map<sf::Int32, EntityInfo> projectileInfoMap;

	float currentView;
	World world;
	sf::RenderWindow& window;
	PlayerInput& playerInput;
};

#endif