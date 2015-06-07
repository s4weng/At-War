#ifndef _SCENENODE_HPP__
#define _SCENENODE_HPP__

#include "Receiver.hpp"
#include "CommandQueue.hpp"

#include <memory>
#include <vector>
#include <set>


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {

public:

	typedef std::unique_ptr<SceneNode> sceneNodePtr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;

	SceneNode();

	void attachNode(sceneNodePtr node);
	sceneNodePtr detachNode(SceneNode& node);

	void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
	void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;
	virtual sf::FloatRect getBoundingRect() const; //set to empty rectangle for non-collideable entities

	void removeDead();
	virtual bool isDead() const;

	void update(sf::Time deltaTime, CommandQueue& commandQueue);

	virtual unsigned int getReceiver() const;
	void onCommand(const Command& command, sf::Time deltaTime);

protected:

	void setIsAttack(bool attack);
	bool getIsAttack();

	bool isAttack; //required for collision checks, set to false for non-collideable entities

private:

	std::vector<sceneNodePtr> children;
	SceneNode* parent;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates) const;

	virtual void updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue);
	void updateChildren(sf::Time deltaTime, CommandQueue& commandQueue);
};

bool collision(const SceneNode& node1, const SceneNode& node2);

#endif