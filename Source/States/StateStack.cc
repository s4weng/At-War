#include "StateStack.hpp"

#include <cassert>
#include <iostream>

StateStack::StateStack(State::ShareView shareView):
requestList(),
stateStack(),
shareView(shareView),
factories() {
}

State::statePtr StateStack::createState(StateID stateID){

	auto result = factories.find(stateID);
	assert(result != factories.end());

	return (result->second)(); //invoke and return factory function
}

void StateStack::handleEvent(const sf::Event& event){

	//iterate from highest state down
	for (auto itr = stateStack.rbegin(); itr != stateStack.rend(); ++itr){

		std::cout << "iterating stacks" << std::endl;
		//if any state returns false, don't late any state below it handle same event
		if (!(*itr)->handleEvent(event))
			break;
	}

	std::cout << "executing stack requests" << std::endl;
	executeRequests();
}

void StateStack::update(sf::Time deltaTime){

	//same logic as handle event
	for (auto itr = stateStack.rbegin(); itr != stateStack.rend(); ++itr){

		if (!(*itr)->update(deltaTime))
			break;
	}
}

void StateStack::draw(){

	//draws active states from bottom to top
	for (State::statePtr& state : stateStack)
		state->draw();
}

void StateStack::pushState(StateID stateID){

	requestList.push_back(Request(Action::Push, stateID));
}

void StateStack::popState(){

	requestList.push_back(Request(Action::Pop));
}

void StateStack::clearStates(){

	requestList.push_back(Request(Action::Clear));
}

bool StateStack::isEmpty() const {

	return stateStack.empty();
}

StateStack::Request::Request(Action action, StateID stateID):
action(action),
stateID(stateID){
}

void StateStack::executeRequests(){

	for (Request request : requestList){

		switch (request.action) {

			case Action::Push:
				stateStack.push_back(createState(request.stateID));
				break;

			case Action::Pop:
				stateStack.pop_back();
				break;

			case Action::Clear:
				stateStack.clear();
				break;
		}
	}

	requestList.clear();
}