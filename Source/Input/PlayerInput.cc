#include "PlayerInput.hpp"
#include "KeyToString.hpp"

#include <iostream>

#include <algorithm>

struct HeroMover {

	HeroMover(float x, float y) : velocity(x, y){
	}

	void operator() (SceneNode& sceneNode, sf::Time) const {

		Hero &hero = static_cast<Hero&>(sceneNode); //command is performed on SceneNode
		hero.setVelocity(hero.getVelocity() + velocity);
	}

	sf::Vector2f velocity;
};

struct HeroAttacker {

	void operator() (SceneNode& sceneNode, sf::Time) const {

		Hero &hero = static_cast<Hero&>(sceneNode);
		hero.launchAttack();
	}
};

PlayerInput::PlayerInput(){

	keyActionMap[sf::Keyboard::Left] = Hero::Action::walkLeft;
	keyActionMap[sf::Keyboard::Right] = Hero::Action::walkRight;
	keyActionMap[sf::Keyboard::Up] = Hero::Action::walkUp;
	keyActionMap[sf::Keyboard::Down] = Hero::Action::walkDown;
	keyActionMap[sf::Keyboard::Space] = Hero::Action::attack;


	//map initialize key to action bindings
	initializeActions();

	//set commands for only player to receive
	for (auto& pair : actionCommandMap)
		pair.second.receiver = Receiver::PlayerHero;

	std::cout << "keys are set" << std::endl;
}

void PlayerInput::handleEvent(const sf::Event& event, CommandQueue& commandQueue){

	if (event.type == sf::Event::KeyPressed){

		//check if pressed key is in keyActionMap, push to CommandQueue with corresponding command
		auto found = keyActionMap.find(event.key.code);

		if (found != keyActionMap.end() && !isRealtimeAction(found->second)){

			std::cout << "found key: " << keyToString(event.key.code) << std::endl;
			commandQueue.push(actionCommandMap[found->second]);
		}
	}
}

void PlayerInput::handleRealtimeInput(CommandQueue& commandQueue){

	//check if any assigned keys are pressed
	for (auto pair : keyActionMap){

		//push corresponding command to CommandQueue if so
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second)){

			std::cout << "found rtkey: " << keyToString(pair.first) << std::endl;	
			commandQueue.push(actionCommandMap[pair.second]);
		}
	}
}

void PlayerInput::assignKey(Hero::Action action, sf::Keyboard::Key key){

	//remove key that already map to given action
	/*for (auto pair : keyActionMap){

		if (pair.second == action)
			keyActionMap.erase(pair.first);
	}*/

	for (auto itr = keyActionMap.begin(); itr != keyActionMap.end(); )
	{
		if (itr->second == action)
			keyActionMap.erase(itr++);
		else
			++itr;
	}

	//then assign the new key
	keyActionMap[key] = action;
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

		case Hero::Action::walkLeft: case Hero::Action::walkRight: case Hero::Action::walkUp: case Hero::Action::walkDown:
			return true;

		default:
			return false;
	}
}

void PlayerInput::initializeActions(){

	const float playerSpeed = 100.f;

	actionCommandMap[Hero::Action::walkLeft].action = HeroMover(-playerSpeed, 0.f);
	actionCommandMap[Hero::Action::walkRight].action = HeroMover(playerSpeed, 0.f);
	actionCommandMap[Hero::Action::walkUp].action = HeroMover(0.f, -playerSpeed);
	actionCommandMap[Hero::Action::walkDown].action = HeroMover(0.f, playerSpeed);
	actionCommandMap[Hero::Action::attack].action = HeroAttacker();
}