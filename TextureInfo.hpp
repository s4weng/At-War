#ifndef _TEXTUREINFO_HPP__
#define _TEXTUREINFO_HPP__

#include "ResourceContainer.hpp"

enum class textureSheet {

	background,
	standingArcher,
	walkingArcher,
	standingArchmage,
	walkingArchmage,
};

namespace sf {

	class Texture;
}

typedef ResourceContainer <sf::Texture, textureSheet> TextureContainer;

#endif