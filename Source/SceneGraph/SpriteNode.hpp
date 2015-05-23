#ifndef _SPRITENODE_HPP__
#define _SPRITENODE_HPP__

#include "SceneNode.hpp"

//class to plug sf::Sprite into our scene graph
class SpriteNode : public SceneNode {

public:

	SpriteNode(const sf::Texture& texture, const sf::IntRect textureRect);

private:

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite sprite;
};

#endif