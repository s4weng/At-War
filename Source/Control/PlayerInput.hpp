#ifndef _PLAYERINPUT_HPP
#define _PLAYERINPUT_HPP

#include "CommandQueue.hpp"

#include <map>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Network/TcpSocket.hpp>

class PlayerInput : private sf::NonCopyable {

public:

	PlayerInput(sf::TcpSocket* socket, );

	enum class PlayerAction {

		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Attack
	};

	void handleEvent(const sf::Event& event, CommandQueue& commandQueue);
	void handleRealtimeInput(CommandQueue& commandQueue);
	void handleRealtimeNetworkInput(CommandQueue& commandQueue);

	void assignKey(PlayerAction action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(PlayerAction action) const;

private:

	static bool isRealtimeAction(PlayerAction action);
	std::map<sf::Keyboard::Key, PlayerAction> keyActionMap;
	std::map<PlayerAction, Command> actionCommandMap;

	void initializeActions();
};

#endif