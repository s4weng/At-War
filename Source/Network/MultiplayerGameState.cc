#include "MultiplayerGameState.hpp"
#include "MusicPlayer.hpp"

MultiplayerGameState::MultiplayerGameState(StateStack& stateStack, ShareView shareView, bool isHost):
State(stateStack, shareView),
isHost(isHost),
world(*shareView.window, *shareView.soundPlayer),
playerInput(*shareView.playerInput){

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

	world.update(deltaTime);

	CommandQueue& commandQueue = world.getCommandQueue();

	playerInput.handleRealtimeInput(commandQueue);

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