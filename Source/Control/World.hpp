#ifndef _WORLD_HPP__
#define _WORLD_HPP__

#include "Hero.hpp" //Entity.hpp, SceneNode.hpp, ResourceContainer.hpp, TextureInfo.hpp, Data.hpp
#include "SpriteNode.hpp"
#include "CommandQueue.hpp" //Command.hpp

#include <array>
#include <SFML/Window.hpp>

class World : private sf::NonCopyable {

public:

	explicit World(sf::RenderWindow& window);
	void update(sf::Time);
	void draw();
	CommandQueue& getCommandQueue();

private:

	//normal enums so LayerCount's index can be used directly as int
	enum Layer {

		Background,
		Ground,
		LayerCount
	};

	sf::RenderWindow& window;
	sf::View view;
	sf::FloatRect worldBounds;
	sf::Vector2f playerSpawnPosition;

	Hero* playerHero;
	Hero* enemyHero;
	TextureContainer textureContainer;
	SceneNode sceneGraph;
	std::array<SceneNode*, LayerCount> sceneLayers;
	float scrollSpeed;
	CommandQueue commandQueue;

	void loadTextures();
	void initScene();
	void checkPlayerBounds();
	bool moveTowards();
	void updateEntities();
};

#endif
