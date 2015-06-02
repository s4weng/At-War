#ifndef _SCENENODE_HPP__
#define _SCENENODE_HPP__

#include "Receiver.hpp"
#include "CommandQueue.hpp"

#include <memory>
#include <vector>


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {

public:

	typedef std::unique_ptr<SceneNode> sceneNodePtr;

	SceneNode();

	void attachNode(sceneNodePtr node);
	sceneNodePtr detachNode(SceneNode& node);

	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;

	void update(sf::Time deltaTime, CommandQueue& commandQueue);

	virtual unsigned int getReceiver() const;
	void onCommand(const Command& command, sf::Time deltaTime);

private:

	std::vector<sceneNodePtr> children;
	SceneNode* parent;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates) const;

	virtual void updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue);
	void updateChildren(sf::Time deltaTime, CommandQueue& commandQueue);
};

#endif