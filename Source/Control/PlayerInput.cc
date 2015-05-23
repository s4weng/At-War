#include "PlayerInput.hpp"
#include "CommandQueue.hpp"
#include "Hero.hpp"

#include <algorithm>

struct HeroMover {

	HeroMover(float x, float y = 0.f) : velocity(x, y){
	}

	void operator() (SceneNode& node, sf::Time) const { //remove sf::Time?

		Hero &hero = static_cast<Hero&>(node); //command is performed on SceneNode
		hero.setVelocity(hero.getVelocity().x + velocity.x, velocity.y);
	}

	sf::Vector2f velocity;
};

PlayerInput::PlayerInput(){

	keyActionMap[sf::Keyboard::Left] = Hero::Action::walkLeft;
	keyActionMap[sf::Keyboard::Right] = Hero::Action::walkRight;

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

void PlayerInput::assignKey(Hero::Action action, sf::Keyboard::Key key){

	//remove keys that already map to given action
	for (auto pair : keyActionMap){

		if (pair.second == action)
			keyActionMap.erase(pair.first);
	}
}

sf::Keyboard::Key PlayerInput::getAssignedKey(Hero::Action action) const {

	for (auto pair : keyActionMap){

		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

bool PlayerInput::isRealtimeAction(Hero::Action action){

	switch (action){

		case Hero::Action::walkLeft: case Hero::Action::walkRight:
			return true;

		default:
			return false;
	}
}

void PlayerInput::initializeActions(){

	const float playerSpeed = 100.f;

	actionCommandMap[Hero::Action::walkLeft].action = HeroMover(-playerSpeed);
	actionCommandMap[Hero::Action::walkRight].action = HeroMover(playerSpeed);
}