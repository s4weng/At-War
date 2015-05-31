#ifndef _GAMECONTROLLER_HPP__
#define _GAMECONTROLLER_HPP__

//#include "TextureInfo.hpp" //ResourceContainer.hpp
#include "PlayerInput.hpp"
#include "StateStack.hpp" //Stack.hpp

class GameController {

public:

	GameController();
	void run();

private:

	void processInput();
	void update(sf::Time deltaTime);
	void render();

	void registerStates();

	static const sf::Time timePerFrame;

	sf::RenderWindow window;
	TextureContainer textureContainer;
	FontContainer fontContainer;
	PlayerInput playerInput;

	StateStack stateStack;
};

#endif