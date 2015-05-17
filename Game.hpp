#ifndef _GAME_HPP__
#define _GAME_HPP__

#include "World.hpp"
#include "PlayerInput.hpp"

class Game : private sf::NonCopyable {

public:

	Game();

	void run();

private:

	void render();
	void processEvents();
	
	static const sf::Time timePerFrame;
	sf::RenderWindow window;
	World world;
	PlayerInput playerInput;
};

#endif