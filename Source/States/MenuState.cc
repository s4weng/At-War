#include "MenuState.hpp"
#include "TextureInfo.hpp"

MenuState::MenuState(StateStack& stateStack, ShareView shareView):
State(stateStack, shareView),
options(),
optionIndex(0){

	sf::Texture& texture = shareView.textureContainer->get(textureSheet::menuBackground);
	sf::Font& font = shareView.fontContainer->get(Fonts::main);
	sf::Vector2f viewSize = shareView.window->getView().getSize();

	background.setTexture(texture);

	setText(font, viewSize);
	updateOption();
}

void MenuState::setText(sf::Font& font, sf::Vector2f viewSize){

	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	playOption.setCharacterSize(50);
	sf::FloatRect bounds = playOption.getLocalBounds();
	playOption.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	playOption.setPosition(viewSize.x / 1.3f, viewSize.y / 3.f);
	options.push_back(playOption);

	sf::Text settingOption;
	settingOption.setFont(font);
	settingOption.setString("Settings");
	settingOption.setCharacterSize(50);
	bounds = settingOption.getLocalBounds();
	settingOption.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	settingOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 70.f));
	options.push_back(settingOption);

	sf::Text quitOption;
	quitOption.setFont(font);
	quitOption.setString("Quit");
	quitOption.setCharacterSize(50);
	bounds = quitOption.getLocalBounds();
	quitOption.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	quitOption.setPosition(settingOption.getPosition() + sf::Vector2f(0.f, 70.f));
	options.push_back(quitOption);	
}

void MenuState::draw(){

	sf::RenderWindow& window = *getSharedView().window;

	window.setView(window.getDefaultView());
	window.draw(background);

	for (const sf::Text& text : options)
		window.draw(text);
}

bool MenuState::update(sf::Time deltaTime){

	return true;
}

bool MenuState::handleEvent(const sf::Event& event){

	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return){

		if (optionIndex == Options::Play){

			requestStackPop();
			requestStackPush(StateID::Game);
		}

		else if (optionIndex == Options::Quit)
			requestStackPop();
	}

	else if (event.key.code == sf::Keyboard::Up){

		if (optionIndex > 0)
			--optionIndex;

		else
			optionIndex = options.size()-1;

		updateOption();
	}

	else if (event.key.code == sf::Keyboard::Down){

		if (optionIndex < options.size() - 1)
			++optionIndex;

		else
			optionIndex = 0;

		updateOption();
	}

	return true;
}

void MenuState::updateOption(){

	if (options.empty())
		return;

	for (sf::Text& text : options)
		text.setColor(sf::Color::Black);

	options[optionIndex].setColor(sf::Color::Blue);
}