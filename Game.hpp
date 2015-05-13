#ifndef _GAME_HPP__
#define _GAME_HPP__

#include <SFML/Graphics.hpp>

class Game : private sf::NonCopyable {

public:

	Game();

	void run();
	void update(sf::Time elapsedTime);
	void render();
	void processEvents();

	void updatePlayerVelocity(float& velocity);
	void handleInput(sf::Keyboard::Key key);

private:

	enum direction {

		none,
		left,
		right
	};

	direction playerDirection;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	static const float playerVelocity;

	static const sf::Time timePerFrame;
	sf::RenderWindow window;
};

#endif