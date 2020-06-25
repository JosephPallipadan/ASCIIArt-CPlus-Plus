#pragma once

#include <vector>
#include <stdlib.h>

#include "Command.hpp"

enum class Directions
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class Pen
{
	std::vector<Pen> undoStack;
	std::vector<std::vector<char>> canvas;
	Directions direction{ Directions::RIGHT };
	char symbol{ '#' };
	int posX{ 0 };
	int posY{ 0 };
	int boundX{ 10 };
	int boundY{ 10 };

	void resizeCanvas(int newBoundX, int newBoundY)
	{
		this->boundX = newBoundX;
		this->boundY = newBoundY;

		this->canvas.resize(newBoundY);
		for (std::vector<char>& row : canvas)
		{
			row = std::vector<char>(newBoundX, ' ');
		}
	}

public:
	Pen()
	{
		resizeCanvas(10, 10);
	}

	Pen(const Pen& other)
	{
		canvas = other.canvas;
		boundX = other.boundX;
		boundY = other.boundY;
		posX = other.posX;
		posY = other.posY;
		symbol = other.symbol;
		direction = other.direction;
	}
	
	void execute(Command& command)
	{
		Commands type = command.getCommand();
		if(type != Commands::UNDO && type != Commands::DISPLAY && type != Commands::CLEAR)
			undoStack.push_back(Pen(*this));

		std::vector<int> parameters = command.getParameters();
		switch (command.getCommand())
		{
		case Commands::BOUNDS:
		{
			resizeCanvas(parameters[1], parameters[0]);
			break;
		}

		case Commands::PEN_POS:
		{
			this->posY = parameters[0];
			this->posX = parameters[1];
			break;
		}

		case Commands::PEN_SYM:
		{
			this->symbol = static_cast<char>(parameters[0]);
			break;
		}

		case Commands::STEP:
		{
			takeSteps(parameters[0]);
			break;
		}

		case Commands::DRAW:
		{
			this->canvas[this->posY][this->posX] = this->symbol;
			break;
		}

		case Commands::ROTATE:
		{
			int newDirection = (static_cast<int>(this->direction) + parameters[0]) % 4;
			this->direction = static_cast<Directions>(newDirection);
			break;
		}

		case Commands::UNDO:
		{
			Pen previous = *(undoStack.end() - 1);
			undoStack.pop_back();
			canvas = previous.canvas;
			boundX = previous.boundX;
			boundY = previous.boundY;
			posX = previous.posX;
			posY = previous.posY;
			symbol = previous.symbol;
			direction = previous.direction;
			break;
		}

		case Commands::DISPLAY:
		{
			generateOutput();
			break;
		}

		case Commands::CLEAR:
		{
			system("CLS");
			break;
		}

		default:
			break;
		}
	}

	void takeSteps(int stepCount)
	{
		int xOffset = 0;
		int yOffset = 0;
		switch (this->direction)
		{
		case Directions::UP:
		{
			yOffset = -1;
			break;
		}

		case Directions::RIGHT:
		{
			xOffset = 1;
			break;
		}

		case Directions::DOWN:
		{
			yOffset = 1;
			break;
		}

		case Directions::LEFT:
		{
			xOffset = -1;
			break;
		}

		}

		this->posX = (this->posX + xOffset * stepCount) % this->boundX;
		this->posY = (this->posY + yOffset * stepCount) % this->boundY;

		if (this->posX < 0)
		{
			this->posX = this->boundX + this->posX;
		}
		if (this->posY < 0)
		{
			this->posY = this->boundY + this->posY;
		}

		/*while (stepCount-- > 0)
		{
			this->posX = (this->posX + xOffset) % this->boundX;
			this->posY = (this->posY + yOffset) % this->boundY;

			if (this->posX == -1)
			{
				this->posX = this->boundX - 1;
			}
			if (this->posY == -1)
			{
				this->posY = this->boundY - 1;
			}
		}*/
	}

	void generateOutput()
	{
		std::string output;
		for (std::vector<char>& row : canvas)
		{
			for (char ch : row)
			{
				output += ch;
			}
			output += "\n";
		}
		std::cout << output;
	}
};