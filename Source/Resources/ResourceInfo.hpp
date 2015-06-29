#ifndef _RESOURCEINFO_HPP__
#define _RESOURCEINFO_HPP__

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

enum class Music {

	mainTheme,
	gameplay,
};

enum class SoundEffect {

	shotArrow,
	castBlast,
	buttonSwitch,
	buttonPress
};

namespace sf {

	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

typedef ResourceContainer <sf::Texture, TextureSheet> TextureContainer;
typedef ResourceContainer <sf::Font, Fonts> FontContainer;
typedef ResourceContainer <sf::Shader, Shaders> ShaderHolder;
typedef ResourceContainer <sf::SoundBuffer, SoundEffect> SoundEffectHolder;

#endif