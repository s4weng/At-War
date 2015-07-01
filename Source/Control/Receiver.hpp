#ifndef _RECEIVER_HPP__
#define _RECEIVER_HPP__


namespace Receiver {
	
	//bit shifting allows us to use operator | for combined receivers
	enum Receiver {

		None = 0,
		Scene = 1 << 0,
		PlayerHero = 1 << 1,
		AlliedHero = 1 << 2,
		EnemyHero = 1 << 3,
		PlayerProjectile = 1 << 4,
		EnemyProjectile = 1 << 5,
		SoundEffect = 1 << 6,

		Hero = PlayerHero | AlliedHero | EnemyHero,
		Projectile = PlayerProjectile | AlliedProjectile | EnemyProjectile
	};
}

#endif