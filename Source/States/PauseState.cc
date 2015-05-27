#include "PauseState.hpp"
#include "TextureInfo.hpp"

PauseState::PauseState(StateStack& stateStack, ShareView shareView):
State(stateStack, shareView),
background(),
pausedText(),
options(),
optionIndex(0){

	sf::Font& font = shareView.fontContainer->get(Fonts::main);
	sf::Vector2f viewSize = shareView.window->getView().getSize();

	setText(font, viewSize);
	updateOption();
}

void PauseState::setText(sf::Font& font, sf::Vector2f viewSize){

	pausedText.setFont(font);
	pausedText.setString("Paused");
	pausedText.setCharacterSize(70);
	sf::FloatRect bounds = pausedText.getLocalBounds();
	pausedText.setOrigin(bounds.width/2.f, 150.f);
	pausedText.setPosition(0.5f*viewSize.x, 0.4f*viewSize.y);

	sf::Text resumeOption, menuOption, quitOption;
	resumeOption.setFont(font);
	menuOption.setFont(font);
	quitOption.setFont(font);
	resumeOption.setString("Resume");
	menuOption.setString("Return to Main Menu");
	quitOption.setString("Quit");

	bounds = resumeOption.getLocalBounds();
	resumeOption.setOrigin(bounds.width/2.f, bounds.height/2.f);
	resumeOption.setPosition(pausedText.getPosition() + sf::Vector2f(0.f, 20.f));
	options.push_back(resumeOption);

	bounds = menuOption.getLocalBounds();
	menuOption.setOrigin(bounds.width/2.f, bounds.height/2.f);
	menuOption.setPosition(resumeOption.getPosition() + sf::Vector2f(0.f, 35.f));
	options.push_back(menuOption);

	bounds = quitOption.getLocalBounds();
	quitOption.setOrigin(bounds.width/2.f, bounds.height/2.f);
	quitOption.setPosition(menuOption.getPosition() + sf::Vector2f(0.f, 35.f));
	options.push_back(quitOption);
}

void PauseState::draw(){

	sf::RenderWindow& window = *getSharedView().window;
	window.setView(window.getDefaultView());

	//transparent background for paused screen
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0,0,0,150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(pausedText);

	for (const sf::Text& text : options)
		window.draw(text);
}

bool PauseState::update(sf::Time deltaTime){

	return false;
}

bool PauseState::handleEvent(const sf::Event& event){

	if (event.type != sf::Event::KeyReleased)
		return false;

	if (event.key.code == sf::Keyboard::Escape)
		requestStackPop();

	if (event.key.code == sf::Keyboard::Return){

		if (optionIndex == Options::Resume){

			requestStackPop();
		}

		else if (optionIndex == Options::MainMenu){

			//clear instead of pop because there could be other states on top of GameState
			requestStateClear();
			requestStackPush(StateID::Menu);
		}

		else //Options::Quit
			requestStateClear();
	}

	else if (event.key.code == sf::Keyboard::Up){

		if (optionIndex > 0)
			--optionIndex;

		else
			optionIndex = options.size() - 1;

		updateOption();
	}

	else if (event.key.code == sf::Keyboard::Down){

		if (optionIndex < options.size() - 1)
			++optionIndex;

		else
			optionIndex = 0;

		updateOption();
	}

	return false;
}

void PauseState::updateOption(){

	if (options.empty())
		return;

	for (sf::Text& text : options)
		text.setColor(sf::Color::White);

	options[optionIndex].setColor(sf::Color::Yellow);
}