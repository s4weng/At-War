#include "CommandQueue.hpp" //Command.hpp, SceneNode.hpp

void CommandQueue::push(const Command& command){

	commandQueue.push(command);
}

Command CommandQueue::pop(){

	Command command = commandQueue.front();
	commandQueue.pop();
	return command;
}

bool CommandQueue::isEmpty() const {

	return commandQueue.empty();
}