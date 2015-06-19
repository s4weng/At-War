#ifndef _ANIMATIONDATA_HPP_
#define _ANIMATIONDATA_HPP_

#include "Hero.hpp"
#include "TextureInfo.hpp"

#include <array>

class Animation;

class AnimationData {

public:

	AnimationData(TextureContainer& textureContainer);
	Animation* getAnimation(Hero::Action action, Hero::HeroClass heroClass);
	Animation* getAnimation(Projectile::Action action, Projectile::Type projectileType);

private:

	void loadTextures(TextureContainer& textureContainer);
	void initHeroAnimations(TextureContainer& textureContainer);
	void initProjectileAnimations(TextureContainer& textureContainer);

	std::array<std::array<Animation, Hero::HeroClass::classCount>, Hero::Action::actionCount> heroAnimations;
	std::array<std::array<Animation, Projectile::Type::typeCount>, Projectile::Action::actionCount> projectileAnimations;
};

#endif