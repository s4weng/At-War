#ifndef _TEXTUREINFO_HPP__
#define _TEXTUREINFO_HPP__

#include "ResourceContainer.hpp"

enum class textureSheet {

	background,
	standingArcher,
	walkingArcher,
	standingArchmage,
	walkingArchmage,
	titleBackground,
	menuBackground
};

enum class Fonts {

	main
};

namespace sf {

	class Texture;
	class Font;
}

typedef ResourceContainer <sf::Texture, textureSheet> TextureContainer;
typedef ResourceContainer <sf::Font, Fonts> FontContainer;

#endif