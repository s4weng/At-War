#ifndef _NETWORKINFO_HPP__
#define _NETWORKINFO_HPP__

#include <SFML/System/Vector2.hpp>

const unsigned short ServerPort = 5000;

enum ServerPacketType {

	Broadcast,
	Spawn,
	InitialState,
	PlayerEvent,
	PlayerRealtimeChange,
	PlayerConnect,
	PlayerDisconnect,
	SpawnEnemy,
	UpdateClientState,
	MissionSuccess
};

enum ClientPacketType {

	PlayerEvent,
	PlayerRealtimeChange,
	PositionUpdate,
	Quit
};

enum PlayerAction {

	MoveLeft,
	MoveRight,
	MoveUp,
	MoveDown,
	Attack,
	ActionCount
};

#endif