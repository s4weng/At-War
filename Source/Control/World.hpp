#ifndef _WORLD_HPP__
#define _WORLD_HPP__

#include "SpriteNode.hpp"
#include "CommandQueue.hpp" //Command.hpp
#include "AnimationData.hpp" //Hero.hpp -> Entity, SceneNode, TextureInfo, Data
#include "SoundNode.hpp"
#include "BloomEffect.hpp"
#include "SoundPlayer.hpp"

#include <array>
#include <SFML/Window.hpp>

extern const std::vector<HeroData> heroDataTable;
extern const std::vector<ProjectileData> projectileDataTable;

class World : private sf::NonCopyable {

public:

	explicit World(sf::RenderWindow& window, SoundPlayer& soundPlayer);
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

	struct SpawnPoint {

		SpawnPoint(Hero::HeroClass heroClass, float x, float y);

		Hero::HeroClass heroClass;
		float x;
		float y;
	};

	sf::RenderWindow& window;
	sf::View view;
	sf::View battlefield;
	sf::FloatRect worldBounds;
	sf::Vector2f playerSpawnPosition;
	sf::RenderTexture sceneTexture;

	TextureContainer textureContainer;
	AnimationData animationData;
	Hero* playerHero;
	SceneNode sceneGraph;
	std::array<SceneNode*, LayerCount> sceneLayers;
	CommandQueue commandQueue;
	std::vector<SpawnPoint> enemySpawns;
	std::vector<std::shared_ptr<Hero>> currentEnemies;
	BloomEffect bloomEffect;
	SoundPlayer& soundPlayer;

	void updateBattlefieldView();
	void removeDeadEnemies();
	void removeOutsideBounds();
	bool checkReceivers(SceneNode::Pair& colliders, Receiver::Receiver first, Receiver::Receiver second);
	void handleCollisions();
	void loadTextures();
	void initScene();
	void adjustView(sf::Time deltaTime);
	void checkPlayerBounds();
	void moveEnemies();
	bool moveTowards(std::shared_ptr<Hero> enemyHero);
	void updateEntities();
	void spawnEnemies();
	void addEnemySpawns();
	void addEnemySpawn(Hero::HeroClass heroClass, float x, float y);
};

#endif
