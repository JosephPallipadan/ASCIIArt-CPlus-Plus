#pragma once

#include <vector>

enum class Commands 
{
	BOUNDS,
	PEN_POS,
	PEN_SYM,
	STEP,
	DRAW,
	ROTATE,
	LOOP,
	UNDO,
	DISPLAY,
	CLEAR,
};

class Command
{
	std::vector<int> parameters;
	Commands command;
public:
	Command(Commands command, std::vector<int> parameters)
	{
		this->command = command;
		this->parameters = parameters;
	}

	Commands getCommand()
	{
		return this->command;
	}

	std::vector<int> getParameters()
	{
		return this->parameters;
	}
};