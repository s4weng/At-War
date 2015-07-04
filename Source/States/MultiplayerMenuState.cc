#include "MultiplayerMenuState.hpp"
#include "ResourceInfo.hpp"
#include "Button.hpp"

MultiplayerMenuState::MultiplayerMenuState(StateStack& stateStack, ShareView shareView):
State(stateStack, shareView),
container() {

	background.setTexture(shareView.textureContainer->get(TextureSheet::menuBackground));

	auto hostButton = std::make_shared<Button>(shareView);
	hostButton->setPosition(450.f, 110.f);
	hostButton->setText("Host");
	hostButton->setCallback([this] () {

		requestStackPop();
		requestStackPush(StateID::HostGame);
	});

	auto joinButton = std::make_shared<Button>(shareView);
	joinButton->setPosition(450.f, 175.f);
	joinButton->setText("Join");
	joinButton->setCallback([this] () {

		requestStackPop();
		requestStackPush(StateID::JoinGame);
	});

	auto menuButton = std::make_shared<Button>(shareView);
	menuButton->setPosition(450.f, 240.f);
	menuButton->setText("Main Menu");
	menuButton->setCallback([this] () {

		requestStackPop();
	});

	container.pack(hostButton);
	container.pack(joinButton);
	container.pack(menuButton);
}

void MultiplayerMenuState::draw(){

	sf::RenderWindow& window = *getSharedView().window;

	window.setView(window.getDefaultView());
	window.draw(background);
	window.draw(container);
}

bool MultiplayerMenuState::update(sf::Time deltaTime){

	return true;
}

bool MultiplayerMenuState::handleEvent(const sf::Event& event){

	container.handleEvent(event);
	return false;
}