#include "GameState.hpp"
#include "KeyToString.hpp"

#include <iostream>

GameState::GameState(StateStack& stateStack, ShareView shareView):
State(stateStack, shareView), //GameState is a new state
world(*shareView.window),
playerInput(*shareView.playerInput){
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

	/*else if (event.type == sf::Event::KeyReleased)
		world.setReleasedKeyAnimation();*/

	else {
		
		playerInput.handleEvent(event, commandQueue);
		//world.setInputAnimation(event.key.code);
	}

	return true;
}