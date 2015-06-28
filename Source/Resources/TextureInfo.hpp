#ifndef _TEXTUREINFO_HPP__
#define _TEXTUREINFO_HPP__

#include "ResourceContainer.hpp"

enum class TextureSheet {

	Background,
	Archer,
	Mage,
	Druid,
	Wolf,
	Arrow,
	MiniBlast,
	MiniBlast1, //remove
	Longsword,
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

enum class Shaders {

	brightness,
	downSample,
	gaussianBlur,
	add
};

namespace sf {

	class Texture;
	class Font;
	class Shader;
}

typedef ResourceContainer <sf::Texture, TextureSheet> TextureContainer;
typedef ResourceContainer <sf::Font, Fonts> FontContainer;
typedef ResourceContainer <sf::Shader, Shaders> ShaderHolder;

#endif