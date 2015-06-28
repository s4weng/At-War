#include "GameState.hpp"
#include "MusicPlayer.hpp"

GameState::GameState(StateStack& stateStack, ShareView shareView):
State(stateStack, shareView),
world(*shareView.window),
playerInput(*shareView.playerInput){

	shareView.musicPlayer->play(Music::gameplay);
}

void GameState::draw(){

	world.draw();
}

bool GameState::update(sf::Time deltaTime){

	world.update(deltaTime);

	CommandQueue& commandQueue = world.getCommandQueue();

	playerInput.handleRealtimeInput(commandQueue);

	return true;
}

bool GameState::handleEvent(const sf::Event& event){

	CommandQueue& commandQueue = world.getCommandQueue();

	playerInput.handleEvent(event, commandQueue);

	//pause if requested
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		requestStackPush(StateID::Pause);

	else
		playerInput.handleEvent(event, commandQueue);

	return true;
}