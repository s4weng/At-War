#ifndef _SOUNDNODE_HPP__
#define _SOUNDNODE_HPP__

#include "SceneNode.hpp"
#include "SoundPlayer.hpp" //ResourceInfo.hpp

class SoundNode : public SceneNode {

public:

	explicit SoundNode(SoundPlayer& soundPlayer);

	void playSound(SoundEffect soundEffect, sf::Vector2f position);
	virtual unsigned int getReceiver() const;

private:

	SoundPlayer& soundPlayer;
};

#endif