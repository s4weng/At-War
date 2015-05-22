#ifndef _STATESTACK_HPP__
#define _STATESTACK_HPP__

#include "State.hpp"

class StateStack : private sf::NonCopyable {

public:

	enum class Action {

		Push,
		Pop,
		Clear
	};

	explicit StateStack(State::ShareView shareView);
	template <typename T>
	void registerState(StateID stateID);

	void handleEvent(const sf::Event& event);
	void update(sf::Time deltaTime);
	void draw();

	//stack operations
	void pushState(StateID stateID);
	void popState();
	void clearStates();
	bool isEmpty() const;

private:

	State::statePtr createState(StateID stateID);

	//can't alter stack during event/update iteration, so have State classes request stack operations
	struct Request {

		explicit Request(Action action, StateID = StateID::None);

		Action action;
		StateID stateID;
	};

	void executeRequests();

	std::vector<Request> requestList;
	std::vector<State::statePtr> stateStack;
	State::ShareView shareView;
	std::map<StateID, std::function<State::statePtr()>> factories;
};

template <typename T>
void StateStack::registerState(StateID stateID){

	//set up mapping from state ID to corresponding factory function to create state
	factories[stateID] = [this] () {

		return State::statePtr(new T(*this, shareView));
	};
}

#endif