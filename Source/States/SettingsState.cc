#include "SettingsState.hpp"
#include "ResourceInfo.hpp"
#include "KeyToString.hpp"

#include <SFML/Graphics.hpp>

SettingsState::SettingsState(StateStack& stateStack, ShareView shareView):
State(stateStack, shareView),
container(){

	background.setTexture(shareView.textureContainer->get(TextureSheet::settingsBackground));

	walkLeftButton = std::make_shared<Button>(shareView);
	walkLeftButton->setPosition(80.f, 250.f);

	walkRightButton = std::make_shared<Button>(shareView);
	walkRightButton->setPosition(80.f, 300.f);

	updateControl();
	walkLeftButton->setToggle(true);
	walkRightButton->setToggle(true);

	container.pack(walkLeftButton);
	container.pack(walkRightButton);

	auto menuButton = std::make_shared<Button>(shareView);
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

	//assign new keys from player
	if (walkLeftButton->isActive()){

		if (event.type == sf::Event::KeyReleased){

			changeKeys = true;
			getSharedView().playerInput->assignKey(PlayerInput::PlayerAction::MoveLeft, event.key.code);			
			walkLeftButton->deactivate();
		}
	}

	if (walkRightButton->isActive()){

		if (event.type == sf::Event::KeyReleased){

			changeKeys = true;
			getSharedView().playerInput->assignKey(PlayerInput::PlayerAction::MoveRight, event.key.code);
			walkRightButton->deactivate();		
		}
	}

	if (changeKeys)
		updateControl();
	
	else 
		container.handleEvent(event);

	return false;
}

void SettingsState::updateControl(){

	PlayerInput& playerInput = *getSharedView().playerInput;

	actionStringMap[PlayerInput::PlayerAction::MoveLeft] = keyToString(playerInput.getAssignedKey(PlayerInput::PlayerAction::MoveLeft));
	actionStringMap[PlayerInput::PlayerAction::MoveRight] = keyToString(playerInput.getAssignedKey(PlayerInput::PlayerAction::MoveRight));
	
	walkLeftButton->setText(actionStringMap[PlayerInput::PlayerAction::MoveLeft]);
	walkRightButton->setText(actionStringMap[PlayerInput::PlayerAction::MoveRight]);
}