#include "MultiplayerServer.hpp"
#include "NetworkInfo.hpp"

EntityInfo::EntityInfo(sf::Vector2f position, sf::Int32 hitpoints): position(position), hitpoints(hitpoints){
}

MultiplayerServer::RemotePeer::RemotePeer(): ready(false), timedOut(false){

	socket.setBlocking(false);
}

MultiplayerServer::MultiplayerServer():
connectedPeers(0),
maxPeers(3),
heroCount(0),
listeningState(false),
waitingThreadEnd(false),
heroIDCount(1),
timeoutTime(sf::seconds(10.f)),
thread(&MultiplayerServer::executeServerThread, this){

	listenerSocket.setBlocking(false);
	peers[0].reset(new RemotePeer());
	thread.launch();
}

MultiplayerServer::~MultiplayerServer(){

	waitingThreadEnd = true;
	thread.wait();
}

void MultiplayerServer::executeServerThread(){

	setListeningState(true);

	sf::Time stepInterval = sf::seconds(1.f / 60.f);
	sf::Time stepTime = sf::Time::Zero;
	sf::Time tickInterval = sf::seconds(1.f / 20.f);
	sf::Time tickTime = sf::Time::Zero;
	sf::Clock stepClock, tickClock;

	while (!waitingThreadEnd){

		handleIncomingPackets();
		handleIncomingConnections();

		//update and tick run at different rates; so don't merge
		while (stepTime >= stepInterval){

			stepTime -= stepInterval;
		}

		//send server state to clients
		while (tickTime >= tickInterval){

			tick();
			tickTime -= tickInterval;
		}

		sf::sleep(sf::milliseconds(50));
	}
}

void MultiplayerServer::tick(){
}

void MultiplayerServer::handleIncomingPackets(){

	bool timedOut = false;

	for (PeerPtr& peer : peers){

		if (peer->ready){

			sf::Packet packet;

			while (peer->socket.receive(packet) == sf::Socket::Done){

				handleIncomingPacket(packet, *peer, timedOut);

				peer->lastReceivedPacket = clock.getElapsedTime();
				packet.clear();
			}

			if (clock.getElapsedTime() >= peer->lastReceivedPacket + timeoutTime){

				peer->timedOut = true;
				timedOut = true;
			}
		}
	}

	if (timedOut) handleDisconnections();
}

void handleIncomingPacket(sf::Packet& packet, RemotePeer& remotePeer, bool timedOut){

	sf::Int32 packetType;
	packet >> packetType;

	switch(packetType){

		case ClientPacketType::SpawnProjectile: {

			int projectileType;
			float posX, posY;
			packet >> projectileType >> posX >> posY;
			
		} break;

		case ClientPacketType::Collision: {

			sf::Int32 projectileID, heroID;
			packet >> projectileID >> heroID;

		} break;

		case ClientPacketType::PositionUpdate: {

			sf::Vector2f heroPosition;

			packet >> heroPosition.x >> heroPosition.y;
			playerHeroInfoMap[remotePeer->heroID].position = heroPosition;

		} break;

		case ClientPacketType::Disconnect: {

			remotePeer.timedOut = true;
			timedOut = true;

		} break;
	}
}

void MultiplayerServer::handleIncomingConnections(){

	if(listenerSocket.accept(peers[connectedPeers]->socket) == sf::TcpListener::Done){

		heroInfoMap[playerIDCount].position.x = currentView;
		heroInfoMap[playerIDCount].position.y = 250.f;
		heroInfoMap[playerIDCount].hitpoints = 100;

		sf::Packet packet;
		packet << static_cast<sf::Int32>(ServerPacketType::SpawnSelf);
		packet << heroIDCount;
		packet << heroInfoMap[playerIDCount].position.x;
		packet << heroInfoMap[playerIDCount].position.y;

		peers[connectedPeers]->heroID.push_back(playerIDCount);

		broadcast("A player joined.");
		passCurrentState(peers[connectedPeers]->socket);
		passNewPeer(playerIDCount);
		++heroIDCount;

		peers[connectedPeers]->socket.send(packet);
		peers[connectedPeers]->ready = true;
		peers[connectedPeers]->lastReceivedPacket = clock.getElapsedTime();
		++heroCount;
		++connectedPeers;

		if (connectedPeers >= maxPeers) setListeningState(false);
		else peers.push_back(PeerPtr (new RemotePeer()));
	}
}

//pass new peer's position to others
void MultiplayerServer::passNewPeer(sf::Int32 heroID){

	for (int i = 0; i < connectedPeers; ++i){

		if (peers[i]->ready){

			sf::Packet packet;
			packet << static_cast<sf::Int32>(ServerPacketType::PlayerConnect);
			packet << heroID << heroInfoMap[heroID].position.x << heroInfoMap[heroID].position.y;
			peers[i]->socket.send(packet);
		}
	}
}

//give current state to new peer
void MultiplayerServer::passCurrentState(sf::TcpSocket& socket){

	sf::Packet packet;
	packet << static_cast<sf::Int32>(ServerPacketType::InitialState);
	packet << currentView;
	packet << static_cast<sf::Int32>(heroCount);

	for (int i = 0; i < connectedPeers; ++i){

		if (peers[i]->ready){

			for (auto id : peers[i]->heroID)
				packet << id << heroInfoMap[id].position.x << heroInfoMap[id].position.y << heroInfoMap[id].hitpoints;
		}
	}

	socket.send(packet);
}

void MultiplayerServer::setListeningState(bool listen){

	if (listen){

		if (!listeningState) listeningState = (listenerSocket.listen(ServerPort) == sf::TcpListener::Done);
	}

	else {

		listenerSocket.close();
		listeningState = false;
	}
}

void MultiplayerServer::handleDisconnections(){

	for (auto itr = peers.begin(); itr != peers.end();){

		if ((*itr)->timedOut){

			for (auto id : (*itr)->heroID){

				sf::Packet packet;
				packet << static_cast<sf::Int32>(ServerPacketType::PlayerDisconnect) << id;
				sendAll(packet);
				heroInfoMap.erase(id);
			}

			--connectedPeers;
			heroCount -= (*itr)->heroID.size();

			itr = peers.erase(itr);

			if (connectedPeers < maxPeers){

				peers.push_back(PeerPtr(new RemotePeer()));
				setListeningState(true);
			}

			broadcast("A player left.");
		}

		else ++itr;
	}
}

void MultiplayerServer::sendAll(sf::Packet& packet){

	for (PeerPtr& peer, peers){

		if (peer->ready) peer->socket.send(packet);
	}
}

void MultiplayerServer::broadcast(const std::string& text){

	for (int i = 0; i < connectedPeers; ++i){

		if (peers[i]->ready){

			sf::Packet packet;
			packet << static_cast<sf::Int32>(ServerPacketType::Broadcast);
			packet << text;
			peers[i]->socket.send(packet);
		}
	}
}