#include "MenuState.hpp"
#include "ResourceInfo.hpp"
#include "Button.hpp"

MenuState::MenuState(StateStack& stateStack, ShareView shareView):
State(stateStack, shareView),
container() {

	background.setTexture(shareView.textureContainer->get(TextureSheet::menuBackground));

	auto playButton = std::make_shared<Button>(shareView);
	playButton->setPosition(450.f, 150.f);
	playButton->setText("Play");
	playButton->setCallback([this] () {

		requestStackPop();
		requestStackPush(StateID::Game);
	});

	auto settingsButton = std::make_shared<Button>(shareView);
	settingsButton->setPosition(450.f, 200.f);
	settingsButton->setText("Settings");
	settingsButton->setCallback([this] () {

		requestStackPush(StateID::Settings);
	});

	auto quitButton = std::make_shared<Button>(shareView);
	quitButton->setPosition(450.f, 250.f);
	quitButton->setText("Quit");
	quitButton->setCallback([this] () {

		requestStackPop();
	});	

	container.pack(playButton);
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