#ifndef _RECEIVER_HPP__
#define _RECEIVER_HPP__


namespace Receiver {
	
	//bit shifting allows us to use operator | for combined receivers
	enum Receiver {

		None = 0,
		Scene = 1 << 0,
		PlayerHero = 1 << 1,
		EnemyHero = 1 << 2,
		PlayerProjectile = 1 << 3,
		EnemyProjectile = 1 << 4,
		SoundEffect = 1 << 5,

		Hero = PlayerHero | EnemyHero,
		Projectile = PlayerProjectile | EnemyProjectile
	};
}

#endif