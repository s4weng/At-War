#ifndef _PLAYERINPUT_HPP
#define _PLAYERINPUT_HPP

#include "CommandQueue.hpp"
#include "Hero.hpp"

#include <map>

class PlayerInput {

public:

	PlayerInput();

	/*enum Action {

		MoveLeft,
		MoveRight,
		ActionCount
	};
*/
	void handleEvent(const sf::Event& event, CommandQueue& commandQueue);
	void handleRealtimeInput(CommandQueue& commandQueue);
	//void handleReleasedKey();

	void assignKey(Hero::Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Hero::Action action) const;

private:

	static bool isRealtimeAction(Hero::Action action);
	std::map<sf::Keyboard::Key, Hero::Action> keyActionMap;
	std::map<Hero::Action, Command> actionCommandMap;

	void initializeActions();
};

#endif