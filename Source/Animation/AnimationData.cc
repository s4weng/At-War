#include "AnimationData.hpp"

#include <iostream>

AnimationData::AnimationData(TextureContainer& textureContainer){

	loadTextures(textureContainer);
	initHeroAnimations(textureContainer);
}

void AnimationData::loadTextures(TextureContainer& textureContainer){

    try {

		textureContainer.load(TextureSheet::Archer, "Images/Archer.png");
		textureContainer.load(TextureSheet::Druid, "Images/Druid.png");
		textureContainer.load(TextureSheet::Crusader, "Images/Crusader.png");
    }

    catch (std::runtime_error& exception){

    	std::cout << "Exception occurred: " << exception.what() << std::endl;
    	return;
    }
}


Animation* AnimationData::getAnimation(Hero::Action action, Hero::HeroClass heroClass){

	auto animation = &(heroAnimations[action][heroClass]);
	return animation;
}


void AnimationData::initHeroAnimations(TextureContainer& textureContainer){

	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Archer].setSpriteSheet(textureContainer.get(TextureSheet::Archer));
	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Archer].addFrame(sf::IntRect(2, 2, 36, 66));

	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Archer].setSpriteSheet(textureContainer.get(TextureSheet::Archer));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Archer].addFrame(sf::IntRect(53, 3, 33, 65));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Archer].addFrame(sf::IntRect(90, 3, 41, 65));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Archer].addFrame(sf::IntRect(135, 2, 32, 65));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Archer].addFrame(sf::IntRect(171, 3, 35, 65));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Archer].addFrame(sf::IntRect(209, 2, 34, 66));

	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].setSpriteSheet(textureContainer.get(TextureSheet::Archer));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].addFrame(sf::IntRect(2, 75, 42, 65));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].addFrame(sf::IntRect(48, 70, 45, 70));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].addFrame(sf::IntRect(96, 74, 36, 65));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].setLooped(false);

	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Archer].setSpriteSheet(textureContainer.get(TextureSheet::Archer));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Archer].addFrame(sf::IntRect(7, 145, 29, 56));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Archer].setLooped(false);

	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Archer].setSpriteSheet(textureContainer.get(TextureSheet::Archer));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Archer].addFrame(sf::IntRect(61, 143, 36, 58));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Archer].addFrame(sf::IntRect(105, 163, 29, 38));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Archer].addFrame(sf::IntRect(138, 173, 40, 28));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Archer].setLooped(false);

	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Crusader].setSpriteSheet(textureContainer.get(TextureSheet::Crusader));
	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Crusader].addFrame(sf::IntRect(4, 2, 49, 87));

	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Crusader].setSpriteSheet(textureContainer.get(TextureSheet::Crusader));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Crusader].addFrame(sf::IntRect(82, 3, 52, 86));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Crusader].addFrame(sf::IntRect(136, 0, 56, 89));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Crusader].addFrame(sf::IntRect(204, 3, 61, 86));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Crusader].addFrame(sf::IntRect(274, 5, 64, 84));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Crusader].addFrame(sf::IntRect(346, 5, 58, 84));

	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Crusader].setSpriteSheet(textureContainer.get(TextureSheet::Crusader));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Crusader].addFrame(sf::IntRect(4, 95, 69, 104));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Crusader].addFrame(sf::IntRect(86, 95, 50, 104));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Crusader].addFrame(sf::IntRect(152, 95, 90, 104));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Crusader].setLooped(false);

	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Crusader].setSpriteSheet(textureContainer.get(TextureSheet::Crusader));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Crusader].addFrame(sf::IntRect(21, 216, 85, 73));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Crusader].setLooped(false);

	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Crusader].setSpriteSheet(textureContainer.get(TextureSheet::Crusader));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Crusader].addFrame(sf::IntRect(117, 203, 86, 58));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Crusader].addFrame(sf::IntRect(112, 214, 98, 75));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Crusader].addFrame(sf::IntRect(320, 214, 82, 75));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Crusader].setLooped(false);


	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Druid].setSpriteSheet(textureContainer.get(TextureSheet::Druid));
	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Druid].addFrame(sf::IntRect(4, 4, 38, 75));

	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Druid].setSpriteSheet(textureContainer.get(TextureSheet::Druid));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Druid].addFrame(sf::IntRect(63, 4, 34, 74));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Druid].addFrame(sf::IntRect(101, 4, 37, 74));

	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Druid].setSpriteSheet(textureContainer.get(TextureSheet::Druid));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Druid].addFrame(sf::IntRect(4, 81, 41, 72));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Druid].addFrame(sf::IntRect(47, 81, 48, 72));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Druid].setLooped(false);

	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Druid].setSpriteSheet(textureContainer.get(TextureSheet::Druid));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Druid].addFrame(sf::IntRect(6, 156, 34, 68));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Druid].setLooped(false);

	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Druid].setSpriteSheet(textureContainer.get(TextureSheet::Druid));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Druid].addFrame(sf::IntRect(60, 162, 37, 63));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Druid].addFrame(sf::IntRect(102, 162, 38, 63));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Druid].addFrame(sf::IntRect(144, 162, 34, 63));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Druid].setLooped(false);
}