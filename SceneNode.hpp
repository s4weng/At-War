#ifndef _SCENENODE_HPP__
#define _SCENENODE_HPP__

#include <memory> //std::unique_ptr
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {

public:

	//scene node pointers will be used frequently
	typedef std::unique_ptr<SceneNode> sceneNodePtr;

	SceneNode();

	void attachNode(sceneNodePtr node);
	sceneNodePtr detachNode(SceneNode& node);

	void update(sf::Time deltaTime);

private:

	std::vector<sceneNodePtr> children;
	SceneNode* parent;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates) const;

	virtual void updateCurrent(sf::Time deltaTime);
	void updateChildren(sf::Time deltaTime);
};

#endif