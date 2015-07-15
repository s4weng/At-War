#ifndef _NETWORKINFO_HPP__
#define _NETWORKINFO_HPP__

const unsigned short ServerPort = 5000;

enum ServerPacketType {

	Broadcast, //string message; broadcasts a message on every player's screen
	EntityUpdate, //sf::Int32 id, sf::Int32 hitpoints, unsigned int heroFaction, float posX, float posY; passes new position of any entity
	SpawnSelf, //sf::Int32 id, float posX, float posY; tells a player to spawn itself upon initialization
	InitialState, //float battlefieldViewWidth; passes the current view to new player
	SpawnEnemy, //sf::Int32 id, sf::Int32 hitpoints, float posX, float posY; passes newly spawned enemy
	SpawnProjectile, //sf::Int32 id, int projectileType, float posX, float posY; passes newly spawned projectile
	PlayerConnect, //sf::Int32 id, float posX, float posY; passes newly connected player spawn
	PlayerDisconnect, //sf::Int32 id; informs of another player's disconnection
};

enum ClientPacketType {

	SpawnProjectile, //int projectileType, float posX, float posY; request for a projectile spawn
	Collision, //sf::Int32 projectileID, sf::Int32 heroID; informs server of a collision between two entities
	PositionUpdate, //float posX, float posY; passes new position of player
	Disconnect //No parameters
};

#endif