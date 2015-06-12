#include "PlayerInput.hpp"
#include "HeroOptions.hpp"

#include <algorithm>

PlayerInput::PlayerInput(){

	keyActionMap[sf::Keyboard::Left] = PlayerAction::MoveLeft;
	keyActionMap[sf::Keyboard::Right] = PlayerAction::MoveRight;
	keyActionMap[sf::Keyboard::Up] = PlayerAction::MoveUp;
	keyActionMap[sf::Keyboard::Down] = PlayerAction::MoveDown;
	keyActionMap[sf::Keyboard::Space] = PlayerAction::Attack;

	//map initialize key to action bindings
	initializeActions();

	//set commands for only player to receive
	for (auto& pair : actionCommandMap)
		pair.second.receiver = Receiver::PlayerHero;
}

void PlayerInput::handleEvent(const sf::Event& event, CommandQueue& commandQueue){

	if (event.type == sf::Event::KeyPressed){

		//check if pressed key is in keyActionMap, push to CommandQueue with corresponding command
		auto found = keyActionMap.find(event.key.code);

		if (found != keyActionMap.end() && !isRealtimeAction(found->second))
			commandQueue.push(actionCommandMap[found->second]);
	}
}

void PlayerInput::handleRealtimeInput(CommandQueue& commandQueue){

	//check if any assigned keys are pressed
	for (auto pair : keyActionMap){

		//push corresponding command to CommandQueue if so
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commandQueue.push(actionCommandMap[pair.second]);
	}
}

void PlayerInput::assignKey(PlayerAction action, sf::Keyboard::Key key){

	//remove key that already map to given action
	for (auto pair : keyActionMap){

		if (pair.second == action)
			keyActionMap.erase(pair.first);
	}

	//then assign the new key
	keyActionMap[key] = action;
}

sf::Keyboard::Key PlayerInput::getAssignedKey(PlayerAction action) const {

	for (auto pair : keyActionMap){

		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

bool PlayerInput::isRealtimeAction(PlayerAction action){

	switch (action){

		case PlayerAction::MoveLeft: case PlayerAction::MoveRight: case PlayerAction::MoveUp: case PlayerAction::MoveDown: case PlayerAction::Attack:
			return true;

		default:
			return false;
	}
}

void PlayerInput::initializeActions(){

	const float playerSpeed = 100.f;

	actionCommandMap[PlayerAction::MoveLeft].action = HeroMover(-playerSpeed, 0.f);
	actionCommandMap[PlayerAction::MoveRight].action = HeroMover(playerSpeed, 0.f);
	actionCommandMap[PlayerAction::MoveUp].action = HeroMover(0.f, -playerSpeed);
	actionCommandMap[PlayerAction::MoveDown].action = HeroMover(0.f, playerSpeed);
	actionCommandMap[PlayerAction::Attack].action = HeroAttacker();
}