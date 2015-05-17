#ifndef _RECEIVER_HPP__
#define _RECEIVER_HPP__

//bit shifting allows us to use operator | for combined receivers
enum Receiver {

	None = 0,
	Scene = 1 << 0,
	PlayerHero = 1 << 1,
	AlliedHero = 1 << 2,
	EnemyHero = 1 << 3,
};

#endif