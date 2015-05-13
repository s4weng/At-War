#ifndef _GAME_HPP__
#define _GAME_HPP__

#include "AnimatedSprite.hpp"

#include <SFML/Graphics.hpp>

class Game : private sf::NonCopyable {

public:

	Game();

	void run();
	void update(sf::Time elapsedTime);
	void render();
	void processEvents();

	void setAnimation();
	void updatePlayerVelocity(float& velocity);
	void updateCurrentAnimation();
	void handleInput(sf::Keyboard::Key key);

private:

	enum animationAction {

		standRight,
		standLeft,
		walkRight,
		walkLeft,
	};

	animationAction playerAction;
	sf::Texture playerTextureWalk, playerTextureStand;

	//Different animation declarations
	Animation walkingRight, walkingLeft;
	Animation standingRight, standingLeft;

	Animation *currentAnimation;
	AnimatedSprite playerSprite;

	static const float playerVelocity;

	static const sf::Time timePerFrame;
	sf::RenderWindow window;
};

#endif