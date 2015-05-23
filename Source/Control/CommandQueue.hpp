#ifndef _COMMANDQUEUE_HPP__
#define _COMMANDQUEUE_HPP__

#include "Command.hpp"
#include <queue>

class CommandQueue {

public:

	void push(const Command& command);
	Command pop();
	bool isEmpty() const;

private:

	std::queue<Command> commandQueue;
};

#endif