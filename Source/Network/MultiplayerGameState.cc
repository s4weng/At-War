#include "MultiplayerGameState.hpp"
#include "MusicPlayer.hpp"

MultiplayerGameState::MultiplayerGameState(StateStack& stateStack, ShareView shareView, bool isHost):
State(stateStack, shareView),
server(nullptr),
lastPacketTime(sf::seconds(0.f),
timeOut(sf::seconds(5.f)),
isConnected(false),
isHost(isHost),
activateState(true),
isFocused(true),
world(*shareView.window, *shareView.soundPlayer),
window(*shareView.window),
playerInput(*shareView.playerInput){

	sf::IpAddress ipAddr = "127.0.0.1";
	if (isHost) server.reset(new MultiplayerServer());

	if (socket.connect(ipAddr, ServerPort, sf::seconds(5.f)) == sf::TcpSocket::Done)
		isConnected = true;
	else
		failedConnectionClock.restart();

	socket.setBlocking(false);

	shareView.musicPlayer->play(Music::gameplay);
	shareView.musicPlayer->setVolume(75.f);
}

MultiplayerGameState::~MultiplayerGameState(){

	getSharedView().musicPlayer->play(Music::mainTheme);
	getSharedView().musicPlayer->setVolume(100.f);
}

void MultiplayerGameState::draw(){

	if (isConnected){

		world.draw();

		if (!broadcastMessages.empty()){

			for (const auto& message : broadcastMessages)
				window.draw(message.first);
		}
	}
}

bool MultiplayerGameState::update(sf::Time deltaTime){

	if (isConnected){

		world.update(deltaTime);
		
		CommandQueue& commands = world.getCommandQueue();

		if (activateState && isFocused)
			playerInput.handleRealtimeInput(commands);

		//receive packets from the server
		sf::Packet packet;
		while (socket.receive(packet) == sf::Socket::Done){

			lastPacketTime = sf::seconds(0.f);
			sf::Int32 packetType;
			packet >> packetType;
			handleIncomingPacket(packetType, packet);
		}

		else { //check potential timeout

			if (lastPacketTime > timeOut){

				//display disconnection text ********
				isConnected = false;
				failedConnectionClock.restart();
			}
		}

		updateBroadcastMessage(deltaTime);

		if (tickClock.getElapsedTime() > sf::seconds(1.f / 20.f)){

			sf::Packet positionUpdatePacket;
			positionUpdatePacket << static_cast<sf::Int32>(ClientPacketType::PositionUpdate);
			positionUpdatePacket << id << hero->getPosition.x << hero->getPosition.y << static_cast<sf::Int32>(hero->getHitpoints()); //***world get position

			socket.send(positionUpdatePacket);
			tickClock.restart();
		}

		lastPacketTime += deltaTime;
	}

	//disconnected
	if (failedConnectionClock.getElapsedTime() >= sf::seconds(5.f)){

		requestStateClear();
		requestStackPush(StateID::Menu);
	}

	return true;
}

void updateBroadcastMessage(sf::Time deltaTime){

	if (!broadcastMessages.empty()){

		//update broadcasts' time; erase if past 3.5 seconds
		for (auto itr = broadcastMessages.begin(); itr != broadcastMessages.end();){

			itr->second += deltaTime;
			if (itr->second >= sf::seconds(3.5f)) itr = broadcastMessages.erase(itr);
		}
}

void MultiplayerServer::handleIncomingPacket(sf::int32 packetType, sf::Packet packet){

	switch (packetType){

		case ServerPacketType::Broadcast: {

			string message;
			packet >> message;
			sf::Text broadcast;
			broadcast.setString(message);
			broadcastMessages.push_back(std::pair<broadcast, sf::seconds(0.f)>);

		} break;

		case ServerPacketType::EntityUpdate: {

			sf::Int32 id, hitpoints;
			unsigned int heroFaction;
			float posX, posY;
			packet >> id >> hitpoints >> heroFaction >> posX >> posY;

			if (heroFaction == 0){

				playerHeroInfoMap[id].hitpoints = hitpoints;
				playerHeroInfoMap[id].position.x = posX;
				playerHeroInfoMap[id].position.y = posY;
			}

			else {

				enemyHeroInfoMap[id].hitpoints = hitpoints;				
				enemyHeroInfoMap[id].position.x = posX;
				enemyHeroInfoMap[id].position.y = posY;
			}

		} break;

		case ServerPacketType::SpawnSelf: {

			sf::Int32 id;
			float posX, posY;
			packet >> id >> posX >> posY;
			playerHeroInfoMap.insert(std::make_pair(id, EntityInfo(sf::Vector2f(posX, posY), 100)));

		} break;

		case ServerPacketType::InitialState: {

			float battlefieldViewWidth;
			packet >> battlefieldViewWidth;
			currentView = battlefieldViewWidth;

		} break;

		case ServerPacketType::SpawnEnemy: {

			sf::Int32 id, hitpoints;
			float posX, posY;
			packet >> id >> hitpoints >> posX >> posY;
			enemyHeroInfoMap.insert(std::make_pair(id, EntityInfo(sf::Vector2f(posX, posY), hitpoints)));

		} break;

		case ServerPacketType::SpawnProjectile: {

			sf::Int32 id,
			float posX, posY;
			packet >> id >> posX >> posY;
			projectileInfoMap.insert(std::make_pair(id, EntityInfo(sf::Vector2f(posX, posY), hitpoints)));

		} break;

		case ServerPacketType::PlayerConnect: {

			sf::Int32 id;
			float posX, posY;
			packet >> id >> posX >> posY;
			playerHeroInfoMap.insert(std::make_pair(id, EntityInfo(sf::Vector2f(posX, posY), 100)));

		} break;

		case ServerPacketType::PlayerDisconnect: {

			sf::Int32 id;
			packet >> id;
			playerHeroInfoMap.erase(id);

		} break;
	}
}

bool MultiplayerGameState::handleEvent(const sf::Event& event){

	CommandQueue& commandQueue = world.getCommandQueue();

	playerInput.handleEvent(event, commandQueue);

	//pause if requested
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		requestStackPush(StateID::Pause);

	//else
	//	playerInput.handleEvent(event, commandQueue);

	return true;
}