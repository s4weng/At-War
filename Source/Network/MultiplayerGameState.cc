#include "MultiplayerGameState.hpp"
#include "MusicPlayer.hpp"

MultiplayerGameState::MultiplayerGameState(StateStack& stateStack, ShareView shareView, bool isHost):
State(stateStack, shareView),
server(nullptr),
lastPacketTime(sf::seconds(0.f),
timeOut(sf::seconds(5.f)),
isConnected(false),
isHost(isHost),
gameStarted(false),
activateState(true),
isFocused(true),
world(*shareView.window, *shareView.soundPlayer),
playerInput(*shareView.playerInput){

	sf::IpAddress ipAddr = "127.0.0.1" //temporary
	if (isHost) server.reset(new MultiplayerServer(sf::Vector2f())); //****** vector to be determined later

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

	world.draw();
}

bool MultiplayerGameState::update(sf::Time deltaTime){

	if (isConnected){

		world.update(deltaTime);

		//if (!foundLocalHero && gameStarted) //Game over state *****
		
		CommandQueue& commands = world.getCommandQueue();

		if (activateState && isFocused)
			playerInput.handleRealtimeInput(commands);

		playerInput.handleRealtimeNetworkInput(commands);

		//messages from server
		sf::Packet packet;
		if (socket.receive(packet) == sf::Socket::Done){

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

		if (tickClock.getElapsedTime() > sf::seconds(1.f / 20.f)){

			sf::Packet positionUpdatePacket;
			positionUpdatePacket << static_cast<sf::Int32>(ClientPacketType::PositionUpdate);
			//positionUpdatePacket << static_cast<sf::Int32>(playerID.size()); ********************** hero isn't declared
			positionUpdatePacket << id << hero->getPosition.x << hero->getPosition.y << static_cast<sf::Int32>(hero->getHitpoints());

			socket.send(positionUpdatePacket);
			tickClock.restart();
		}

		lastPacketTime += deltaTime;
	}

	if (failedConnectionClock.getElapsedTime() >= sf::seconds(5.f)){

		requestStateClear();
		requestStackPush(StateID::Menu);
	}

	return true;
}

bool MultiplayerGameState::handleEvent(const sf::Event& event){

	CommandQueue& commandQueue = world.getCommandQueue();

	playerInput.handleEvent(event, commandQueue);

	//pause if requested
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		requestStackPush(StateID::Pause);

	else
		playerInput.handleEvent(event, commandQueue);

	return true;
}