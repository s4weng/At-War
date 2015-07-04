#include "MenuState.hpp"
#include "ResourceInfo.hpp"
#include "Button.hpp"

MenuState::MenuState(StateStack& stateStack, ShareView shareView):
State(stateStack, shareView),
container() {

	background.setTexture(shareView.textureContainer->get(TextureSheet::menuBackground));

	auto singleplayerButton = std::make_shared<Button>(shareView);
	singleplayerButton->setPosition(450.f, 110.f);
	singleplayerButton->setText("Singleplayer");
	singleplayerButton->setCallback([this] () {

		requestStackPop();
		requestStackPush(StateID::Game);
	});

	auto multiplayerButton = std::make_shared<Button>(shareView);
	multiplayerButton->setPosition(450.f, 175.f);
	multiplayerButton->setText("Multiplayer");
	multiplayerButton->setCallback([this] () {

		requestStackPop();
		requestStackPush(StateID::MultiGame);
	});

	auto settingsButton = std::make_shared<Button>(shareView);
	settingsButton->setPosition(450.f, 240.f);
	settingsButton->setText("Settings");
	settingsButton->setCallback([this] () {

		requestStackPush(StateID::Settings);
	});

	auto quitButton = std::make_shared<Button>(shareView);
	quitButton->setPosition(450.f, 305.f);
	quitButton->setText("Quit");
	quitButton->setCallback([this] () {

		requestStackPop();
	});	

	container.pack(singleplayerButton);
	container.pack(multiplayerButton);
	container.pack(settingsButton);
	container.pack(quitButton);
}

void MenuState::draw(){

	sf::RenderWindow& window = *getSharedView().window;

	window.setView(window.getDefaultView());
	window.draw(background);
	window.draw(container);
}

bool MenuState::update(sf::Time deltaTime){

	return true;
}

bool MenuState::handleEvent(const sf::Event& event){

	container.handleEvent(event);
	return false;
}