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
	    textureContainer.load(TextureSheet::Arrow, "Images/Arrow.png");
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
}