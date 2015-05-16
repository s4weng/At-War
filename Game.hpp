#ifndef _GAME_HPP__
#define _GAME_HPP__

//#include "AnimatedSprite.hpp"
#include "TextureInfo.hpp"
#include "World.hpp"

class Game : private sf::NonCopyable {

public:

	Game();

	void run();
	void render();
	void processEvents();

private:

	static const sf::Time timePerFrame;
	sf::RenderWindow window;
	World world;
};

#endif