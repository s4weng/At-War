#include "SettingsState.hpp"
#include "ResourceInfo.hpp"
#include "KeyToString.hpp"

#include <SFML/Graphics.hpp>

SettingsState::SettingsState(StateStack& stateStack, ShareView shareView):
State(stateStack, shareView),
container(){

	background.setTexture(shareView.textureContainer->get(TextureSheet::settingsBackground));

	walkUpButton = std::make_shared<Button>(shareView);
	walkUpButton->setPosition(50.f, 30.f);
	upText.setFont(shareView.fontContainer->get(Fonts::main));
	upText.setString("Up");
	upText.setCharacterSize(27);
	upText.setPosition(360.f, 50.f);

	walkDownButton = std::make_shared<Button>(shareView);
	walkDownButton->setPosition(50.f, 95.f);
	downText.setFont(shareView.fontContainer->get(Fonts::main));
	downText.setString("Down");
	downText.setCharacterSize(27);
	downText.setPosition(360.f, 115.f);

	walkLeftButton = std::make_shared<Button>(shareView);
	walkLeftButton->setPosition(50.f, 160.f);
	leftText.setFont(shareView.fontContainer->get(Fonts::main));
	leftText.setString("Left");
	leftText.setCharacterSize(27);
	leftText.setPosition(360.f, 180.f);

	walkRightButton = std::make_shared<Button>(shareView);
	walkRightButton->setPosition(50.f, 225.f);
	rightText.setFont(shareView.fontContainer->get(Fonts::main));
	rightText.setString("Right");
	rightText.setCharacterSize(27);
	rightText.setPosition(360.f, 245.f);

	attackButton = std::make_shared<Button>(shareView);
	attackButton->setPosition(50.f, 290.f);
	attackText.setFont(shareView.fontContainer->get(Fonts::main));
	attackText.setString("Attack");
	attackText.setCharacterSize(27);
	attackText.setPosition(360.f, 310.f);

	updateControl();
	walkUpButton->setToggle(true);
	walkDownButton->setToggle(true);
	walkLeftButton->setToggle(true);
	walkRightButton->setToggle(true);
	attackButton->setToggle(true);

	container.pack(walkUpButton);
	container.pack(walkDownButton);
	container.pack(walkLeftButton);
	container.pack(walkRightButton);
	container.pack(attackButton);

	auto menuButton = std::make_shared<Button>(shareView);
	menuButton->setPosition(50.f, 400.f);
	menuButton->setText("Main Menu");
	menuButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	container.pack(menuButton);
}

void SettingsState::draw(){

	sf::RenderWindow& window = *getSharedView().window;

	window.draw(background);
	window.draw(container);

	window.draw(upText);
	window.draw(downText);
	window.draw(leftText);
	window.draw(rightText);
	window.draw(attackText);
}

bool SettingsState::update(sf::Time deltaTime){

	return true;
}

bool SettingsState::handleEvent(const sf::Event& event){

	PlayerInput& playerInput = *getSharedView().playerInput;

	bool changeKeys = false;

	//assign new keys from player
	if (walkUpButton->isActive()){

		if (event.type == sf::Event::KeyReleased){

			changeKeys = true;
			getSharedView().playerInput->assignKey(PlayerInput::PlayerAction::MoveUp, event.key.code);			
			walkUpButton->deactivate();
		}
	}

	if (walkDownButton->isActive()){

		if (event.type == sf::Event::KeyReleased){

			changeKeys = true;
			getSharedView().playerInput->assignKey(PlayerInput::PlayerAction::MoveDown, event.key.code);			
			walkDownButton->deactivate();
		}
	}

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

	if (attackButton->isActive()){

		if (event.type == sf::Event::KeyReleased){

			changeKeys = true;
			getSharedView().playerInput->assignKey(PlayerInput::PlayerAction::Attack, event.key.code);
			attackButton->deactivate();		
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

	actionStringMap[PlayerInput::PlayerAction::MoveUp] = keyToString(playerInput.getAssignedKey(PlayerInput::PlayerAction::MoveUp));
	actionStringMap[PlayerInput::PlayerAction::MoveDown] = keyToString(playerInput.getAssignedKey(PlayerInput::PlayerAction::MoveDown));
	actionStringMap[PlayerInput::PlayerAction::MoveLeft] = keyToString(playerInput.getAssignedKey(PlayerInput::PlayerAction::MoveLeft));
	actionStringMap[PlayerInput::PlayerAction::MoveRight] = keyToString(playerInput.getAssignedKey(PlayerInput::PlayerAction::MoveRight));
	actionStringMap[PlayerInput::PlayerAction::Attack] = keyToString(playerInput.getAssignedKey(PlayerInput::PlayerAction::Attack));

	walkUpButton->setText(actionStringMap[PlayerInput::PlayerAction::MoveUp]);
	walkDownButton->setText(actionStringMap[PlayerInput::PlayerAction::MoveDown]);
	walkLeftButton->setText(actionStringMap[PlayerInput::PlayerAction::MoveLeft]);
	walkRightButton->setText(actionStringMap[PlayerInput::PlayerAction::MoveRight]);
	attackButton->setText(actionStringMap[PlayerInput::PlayerAction::Attack]);
}