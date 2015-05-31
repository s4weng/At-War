#include "TitleState.hpp"
#include "TextureInfo.hpp"

#include <SFML/Graphics.hpp>

TitleState::TitleState(StateStack& stateStack, ShareView shareView):
State(stateStack, shareView),
titleText(),
continueText(),
showText(true),
textFlash(sf::Time::Zero){

	background.setTexture(shareView.textureContainer->get(textureSheet::titleBackground));

	titleText.setFont(shareView.fontContainer->get(Fonts::main));
	titleText.setString("At War");
	titleText.setCharacterSize(50);
	//move the string according to its center
	sf::FloatRect bounds = titleText.getLocalBounds();
	titleText.setOrigin(bounds.width/2.f, bounds.height/2.f);
	titleText.setPosition(shareView.window->getView().getSize().x / 2.f, 28.f);

	continueText.setFont(shareView.fontContainer->get(Fonts::main));
	continueText.setString("Press any key to continue");
	continueText.setCharacterSize(18);
	bounds = continueText.getLocalBounds();
	continueText.setOrigin(bounds.width/2.f, bounds.height/2.f);
	continueText.setPosition(shareView.window->getView().getSize().x / 2.f, 475.f);
}

void TitleState::draw(){

	sf::RenderWindow& window = *getSharedView().window;
	window.draw(background);

	if(showText)
		window.draw(continueText);

	window.draw(titleText);
}

bool TitleState::update(sf::Time deltaTime){

	textFlash += deltaTime;

	if (textFlash >= sf::seconds(1.f)){

		showText = !showText;
		textFlash = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event& event){

	if (event.type == sf::Event::KeyReleased){

		requestStackPop();
		requestStackPush(StateID::Menu);
	}

	return true;
}