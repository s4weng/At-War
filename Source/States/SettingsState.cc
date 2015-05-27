#include "SettingsState.hpp"
#include "TextureInfo.hpp"
#include "KeyToString.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

SettingsState::SettingsState(StateStack& stateStack, ShareView shareView):
State(stateStack, shareView),
container(){

	background.setTexture(shareView.textureContainer->get(textureSheet::settingsBackground));

	walkLeftButton = std::make_shared<Button>(*shareView.fontContainer, *shareView.textureContainer);
	walkLeftButton->setPosition(80.f, 250.f);
//	walkLeftButton->setText("Move Left");

	walkRightButton = std::make_shared<Button>(*shareView.fontContainer, *shareView.textureContainer);
	walkRightButton->setPosition(80.f, 350.f);
//	walkRightButton->setText("Move Right");

	updateControl();
	walkLeftButton->setToggle(true);
	walkRightButton->setToggle(true);

	container.pack(walkLeftButton);
	container.pack(walkRightButton);

	auto menuButton = std::make_shared<Button>(*shareView.fontContainer, *shareView.textureContainer);
	menuButton->setPosition(80.f, 400.f);
	menuButton->setText("Return to Main Menu");
	menuButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	container.pack(menuButton);
}

void SettingsState::draw(){

	sf::RenderWindow& window = *getSharedView().window;

	window.draw(background);
	window.draw(container);
}

bool SettingsState::update(sf::Time deltaTime){

	return true;
}

bool SettingsState::handleEvent(const sf::Event& event){
	PlayerInput& playerInput = *getSharedView().playerInput;

	bool changeKeys = false;
		//std::cout << "key0 is " << keyToString(event.key.code) << std::endl;

	//assign new keys from player
	if (walkLeftButton->isActive()){
		std::cout << "activated left key " << std::endl;
		if (event.type == sf::Event::KeyReleased){

		std::cout << "released key is " << keyToString(event.key.code) << std::endl;
		//std::cout << "key2 is " << keyToString(event.key.code) << std::endl;

			changeKeys = true;
			getSharedView().playerInput->assignKey(Hero::Action::walkLeft, event.key.code);
			//getSharedView().playerInput->assignKey(Hero::Action::standLeft, event.key.code);
			//actionStringMap[Hero::Action::walkLeft] = keyToString(playerInput.getAssignedKey(Hero::Action::walkLeft));
			//std::cout << actionStringMap[Hero::Action::walkLeft] << std::endl;
			
			walkLeftButton->deactivate();
		}
	}

	/*if (walkRightButton->isActive()){
		std::cout << "shouldn't be here" << std::endl;
		if (event.type == sf::Event::KeyReleased){

			changeKeys = true;
			getSharedView().playerInput->assignKey(Hero::Action::walkRight, event.key.code);
			getSharedView().playerInput->assignKey(Hero::Action::standRight, event.key.code);
			walkRightButton->deactivate();		
		}
	}
*/
	if (changeKeys){
		std::cout << "left control changed: " << std::endl;
		updateControl();
	}
	else {

		std::cout << "no controls changed, passing key: " << keyToString(event.key.code) << std::endl;
		container.handleEvent(event);
	}

	return false;
}

void SettingsState::updateControl(){

	PlayerInput& playerInput = *getSharedView().playerInput;

	actionStringMap[Hero::Action::walkLeft] = keyToString(playerInput.getAssignedKey(Hero::Action::walkLeft));
	//actionStringMap[Hero::Action::walkRight] = keyToString(playerInput.getAssignedKey(Hero::Action::walkRight));
	
	std::cout << "left updated to: " << actionStringMap[Hero::Action::walkLeft] << std::endl;

	walkLeftButton->setText(actionStringMap[Hero::Action::walkLeft]);
	walkRightButton->setText(actionStringMap[Hero::Action::walkRight]);
}
