#ifndef _MULTIPLAYERSERVER_HPP__
#define _MULTIPLAYERSERVER_HPP__

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>

#include <vector>
#include <memory>
#include <map>


struct EntityInfo {

	EntityInfo(sf::Vector2f position, sf::Int32 hitpoints);

	sf::Vector2f position;
	sf::Int32 hitpoints;
};

//we'll use fixed-size sf::Int32 to achieve consistency between sender/receiver
class MultiplayerServer {

public:

	MultiplayerServer();
	~MultiplayerServer();

private:

	struct RemotePeer {

		RemotePeer();
		sf::TcpSocket socket;
		sf::Time lastReceivedPacket;
		std::vector<sf::Int32> heroID;
		bool ready;
		bool timedOut;
	};

	typedef std::unique_ptr<RemotePeer> PeerPtr;

	void setListeningState(bool listen);
	void tick();
	void executeServerThread();
	void handleIncomingPacket(sf::Packet& packet, RemotePeer& remotePeer, bool& timedOut);
	void handleIncomingPackets();
	void handleIncomingConnections();
	void handleDisconnections();
	void passCurrentState(sf::TcpSocket& socket);
	void passNewPeer(sf::Int32 heroID);
	void sendAll(sf::Packet& packet);
	void broadcast(const std::string& text);

	int connectedPeers, maxPeers;
	int heroCount;
	bool listeningState;
	bool waitingThreadEnd;

	sf::Int32 playerIDCount, enemyIDCount;
	std::map<sf::Int32, EntityInfo> playerHeroInfoMap;
	std::map<sf::Int32, EntityInfo> enemyHeroInfoMap;
	std::map<sf::Int32, EntityInfo> projectileInfoMap;

	std::vector<PeerPtr> peers; //one is invalid (length n+1)

	sf::TcpListener listenerSocket;
	sf::Clock clock;
	sf::Time timeoutTime;
	sf::Thread thread;
};

#endif