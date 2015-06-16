#ifndef _TEXTUREINFO_HPP__
#define _TEXTUREINFO_HPP__

#include "ResourceContainer.hpp"

enum class TextureSheet {

	Background,
	Archer,
	Druid,
	Arrow,
	MiniBlast,
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

typedef ResourceContainer <sf::Texture, TextureSheet> TextureContainer;
typedef ResourceContainer <sf::Font, Fonts> FontContainer;

#endif