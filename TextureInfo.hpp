#ifndef _TEXTUREINFO_HPP__
#define _TEXTUREINFO_HPP__

#include "ResourceContainer.hpp"

enum class textureSheet {

	background,
	standingArcher,
	walkingArcher,
	standingMage,
	walkingMage,
};

namespace sf {

	class Texture;
}

typedef ResourceContainer <sf::Texture, textureSheet> TextureContainer;

#endif