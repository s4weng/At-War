#include "AnimationData.hpp"

#include <iostream>

AnimationData::AnimationData(TextureContainer& textureContainer){

	loadTextures(textureContainer);
	initHeroAnimations(textureContainer);
	initProjectileAnimations(textureContainer);
}

void AnimationData::loadTextures(TextureContainer& textureContainer){

    try {

		textureContainer.load(TextureSheet::Archer, "Images/Archer.png");
		textureContainer.load(TextureSheet::Mage, "Images/Mage.png");
		textureContainer.load(TextureSheet::Druid, "Images/Druid.png");
		textureContainer.load(TextureSheet::Wolf, "Images/Wolf.png");

    	textureContainer.load(TextureSheet::Arrow, "Images/Projectiles.png");
    	textureContainer.load(TextureSheet::MiniBlast1, "Images/Projectiles.png");
    	textureContainer.load(TextureSheet::MiniBlast, "Images/Projectiles.png");
    	textureContainer.load(TextureSheet::Longsword, "Images/Projectiles.png");
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

Animation* AnimationData::getAnimation(Projectile::Action action, Projectile::Type projectileType){

	auto animation = &(projectileAnimations[action][projectileType]);
	return animation;
}

void AnimationData::initHeroAnimations(TextureContainer& textureContainer){

	//see spritesheets; width and height are same per frame for each class
	int width = 70, height = 75;
	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Archer].setSpriteSheet(textureContainer.get(TextureSheet::Archer));
	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Archer].addFrame(sf::IntRect(0, 0, width, height));

	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Archer].setSpriteSheet(textureContainer.get(TextureSheet::Archer));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Archer].addFrame(sf::IntRect(width, 0, width, height));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Archer].addFrame(sf::IntRect(2*width, 0, width, height));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Archer].addFrame(sf::IntRect(3*width, 0, width, height));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Archer].addFrame(sf::IntRect(0, height+1, width, height));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Archer].addFrame(sf::IntRect(width, height+1, width, height-1));

	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].setSpriteSheet(textureContainer.get(TextureSheet::Archer));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].addFrame(sf::IntRect(2*width, height+1, width, height-1));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].addFrame(sf::IntRect(3*width, height+1, width, height-1));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].addFrame(sf::IntRect(0, 2*height+1, width, height-1));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].addFrame(sf::IntRect(width, 2*height+1, width, height-1));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].addFrame(sf::IntRect(2*width, 2*height+1, width, height-1));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].addFrame(sf::IntRect(3*width, 2*height+1, width, height-1));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].setLooped(false);
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Archer].setFrameTime(sf::seconds(0.05f)); //default frame time is 0.13f

	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Archer].setSpriteSheet(textureContainer.get(TextureSheet::Archer));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Archer].addFrame(sf::IntRect(0, 3*height+1, width, height-1));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Archer].addFrame(sf::IntRect(width, 3*height+1, width, height-1));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Archer].addFrame(sf::IntRect(2*width, 3*height+1, width, height-1));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Archer].setLooped(false);
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Archer].setFrameTime(sf::seconds(0.2f));

	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Archer].setSpriteSheet(textureContainer.get(TextureSheet::Archer));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Archer].addFrame(sf::IntRect(3*width, 3*height+1, width, height-1));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Archer].setLooped(false);


	width = 110, height = 110;
	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Mage].setSpriteSheet(textureContainer.get(TextureSheet::Mage));
	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Mage].addFrame(sf::IntRect(0, 0, width, height));

	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Mage].setSpriteSheet(textureContainer.get(TextureSheet::Mage));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Mage].addFrame(sf::IntRect(width, 0, width, height));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Mage].addFrame(sf::IntRect(2*width, 0, width, height));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Mage].addFrame(sf::IntRect(3*width, 0, width, height));

	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Mage].setSpriteSheet(textureContainer.get(TextureSheet::Mage));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Mage].addFrame(sf::IntRect(0, height, width, height));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Mage].addFrame(sf::IntRect(width, height, width, height));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Mage].addFrame(sf::IntRect(2*width, height, width, height));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Mage].setLooped(false);

	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Mage].setSpriteSheet(textureContainer.get(TextureSheet::Mage));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Mage].addFrame(sf::IntRect(3*width, height, width, height));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Mage].addFrame(sf::IntRect(0, 2*height, width, height));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Mage].addFrame(sf::IntRect(width, 2*height, width, height));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Mage].addFrame(sf::IntRect(2*width, 2*height, width, height));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Mage].addFrame(sf::IntRect(3*width, 2*height, width, height));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Mage].setLooped(false);

	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Mage].setSpriteSheet(textureContainer.get(TextureSheet::Mage));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Mage].addFrame(sf::IntRect(0, 3*height, width, height));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Mage].setLooped(false);


	width = 70, height = 75;
	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Druid].setSpriteSheet(textureContainer.get(TextureSheet::Druid));
	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Druid].addFrame(sf::IntRect(0, 0, width, height));

	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Druid].setSpriteSheet(textureContainer.get(TextureSheet::Druid));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Druid].addFrame(sf::IntRect(width, 0, width, height));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Druid].addFrame(sf::IntRect(2*width, 0, width, height));

	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Druid].setSpriteSheet(textureContainer.get(TextureSheet::Druid));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Druid].addFrame(sf::IntRect(3*width, 0, width, height));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Druid].addFrame(sf::IntRect(0, height, width, height));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Druid].setLooped(false);

	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Druid].setSpriteSheet(textureContainer.get(TextureSheet::Druid));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Druid].addFrame(sf::IntRect(width, height, width, height));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Druid].addFrame(sf::IntRect(2*width, height, width, height));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Druid].addFrame(sf::IntRect(3*width, height, width, height));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Druid].setLooped(false);
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Druid].setFrameTime(sf::seconds(0.2f));

	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Druid].setSpriteSheet(textureContainer.get(TextureSheet::Druid));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Druid].addFrame(sf::IntRect(0, 2*height, width, height));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Druid].setLooped(false);


	width = 120, height = 90;
	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Wolf].setSpriteSheet(textureContainer.get(TextureSheet::Wolf));
	heroAnimations[Hero::Action::Stand][Hero::HeroClass::Wolf].addFrame(sf::IntRect(0, 0, width, height));

	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Wolf].setSpriteSheet(textureContainer.get(TextureSheet::Wolf));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Wolf].addFrame(sf::IntRect(width, 0, width, height));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Wolf].addFrame(sf::IntRect(2*width, 0, width, height));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Wolf].addFrame(sf::IntRect(3*width, 0, width, height));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Wolf].addFrame(sf::IntRect(0, height, width, height));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Wolf].addFrame(sf::IntRect(width, height, width, height));
	heroAnimations[Hero::Action::Walk][Hero::HeroClass::Wolf].addFrame(sf::IntRect(2*width, height, width, height));

	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Wolf].setSpriteSheet(textureContainer.get(TextureSheet::Wolf));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Wolf].addFrame(sf::IntRect(3*width, height, width, height));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Wolf].addFrame(sf::IntRect(0, 2*height, width, height));
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Wolf].setLooped(false);
	heroAnimations[Hero::Action::Attack][Hero::HeroClass::Wolf].setFrameTime(sf::seconds(0.2f));

	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Wolf].setSpriteSheet(textureContainer.get(TextureSheet::Wolf));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Wolf].addFrame(sf::IntRect(width, 2*height, width, height));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Wolf].addFrame(sf::IntRect(2*width, 2*height, width, height));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Wolf].addFrame(sf::IntRect(3*width, 2*height, width, height));
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Wolf].setLooped(false);
	heroAnimations[Hero::Action::Fall][Hero::HeroClass::Wolf].setFrameTime(sf::seconds(0.25f));

	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Wolf].setSpriteSheet(textureContainer.get(TextureSheet::Wolf));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Wolf].addFrame(sf::IntRect(0, 3*height, width, height));
	heroAnimations[Hero::Action::Flinch][Hero::HeroClass::Wolf].setLooped(false);
}

void AnimationData::initProjectileAnimations(TextureContainer& textureContainer){

	projectileAnimations[Projectile::Action::Flying][Projectile::Type::Arrow].setSpriteSheet(textureContainer.get(TextureSheet::Arrow));
	projectileAnimations[Projectile::Action::Flying][Projectile::Type::Arrow].addFrame(sf::IntRect(0, 0, 31, 5));

	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::Arrow].setSpriteSheet(textureContainer.get(TextureSheet::Arrow));
	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::Arrow].addFrame(sf::IntRect(34, 0, 33, 13));
	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::Arrow].addFrame(sf::IntRect(70, 0, 31, 29));
	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::Arrow].setLooped(false);

	projectileAnimations[Projectile::Action::Flying][Projectile::Type::MiniBlast].setSpriteSheet(textureContainer.get(TextureSheet::MiniBlast));
	projectileAnimations[Projectile::Action::Flying][Projectile::Type::MiniBlast].addFrame(sf::IntRect(0, 33, 26, 8));

	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::MiniBlast].setSpriteSheet(textureContainer.get(TextureSheet::MiniBlast));
	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::MiniBlast].addFrame(sf::IntRect(0, 33, 26, 8));
	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::MiniBlast].setLooped(false);

	projectileAnimations[Projectile::Action::Flying][Projectile::Type::MiniBlast1].setSpriteSheet(textureContainer.get(TextureSheet::MiniBlast1));
	projectileAnimations[Projectile::Action::Flying][Projectile::Type::MiniBlast1].addFrame(sf::IntRect(0, 33, 26, 8));

	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::MiniBlast1].setSpriteSheet(textureContainer.get(TextureSheet::MiniBlast1));
	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::MiniBlast1].addFrame(sf::IntRect(0, 33, 26, 8));
	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::MiniBlast1].setLooped(false);

	projectileAnimations[Projectile::Action::Flying][Projectile::Type::Longsword].setSpriteSheet(textureContainer.get(TextureSheet::Longsword));
	projectileAnimations[Projectile::Action::Flying][Projectile::Type::Longsword].addFrame(sf::IntRect(0, 10, 30, 15));

	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::Longsword].setSpriteSheet(textureContainer.get(TextureSheet::Longsword));
	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::Longsword].addFrame(sf::IntRect(0, 10, 30, 15));
	projectileAnimations[Projectile::Action::Breaking][Projectile::Type::Longsword].setLooped(false);
}