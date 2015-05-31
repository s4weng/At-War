#ifndef _TEXTUREINFO_HPP__
#define _TEXTUREINFO_HPP__

#include "ResourceContainer.hpp"

enum class textureSheet {

	background,
	standingArcher,
	walkingArcher,
	standingArchmage,
	walkingArchmage,
	standingDruid,
	walkingDruid,
	Arrow,
	Spell,
	titleBackground,
	menuBackground,
	settingsBackground,
	normalButton,
	selectedButton,
	pressedButton
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