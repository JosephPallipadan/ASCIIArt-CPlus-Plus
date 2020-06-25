#pragma once

#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <algorithm>

#include "Command.hpp"
#include "Pen.hpp"
class CanvasDrawer
{
	bool ended{ false };
	bool inLoop{ false };
	Pen pen;

public:
	void start()
	{
		analyzeAndExecute(readLine());
	}

	void analyzeAndExecute(std::string line)
	{
		if (line == "")
		{
			end();
			return;
		}
		if (line[0] == '#')
		{
			analyzeAndExecute(readLine());
			return;
		}
		Command command = createCommand(line);
		if (command.getCommand() == Commands::LOOP)
		{
			std::vector<std::string> loopLines = readLoopLines();
			executeCommandSequence(getCommandSequence(loopLines), command.getParameters()[0]);
		}
		else
		{
			pen.execute(command);
		}
		analyzeAndExecute(readLine());
	}

	std::vector<std::string> readLoopLines()
	{
		std::vector<std::string> loopLines;
		std::string loopLine = readLine();
		int loopNestCount = 0;
		while (loopNestCount > 0 || loopLine != "end loop")
		{
			if (loopLine.substr(0, 4) == "loop")
			{
				loopNestCount++;
			}
			else if (loopLine == "end loop")
			{
				loopNestCount--;
			}
			loopLines.push_back(loopLine);
			loopLine = readLine();
		}
		return loopLines;
	}

	std::vector<std::string> readLoopLines(std::vector<std::string> lines, std::vector<std::string>::iterator start)
	{
		std::vector<std::string> loopLines;
		auto loopLine = start;
		
		int loopNestCount = 0;
		while (loopNestCount > 0 || *loopLine != "end loop")
		{
			if (loopLine->substr(0, 4) == "loop")
			{
				loopNestCount++;
			}
			else if (*loopLine == "end loop")
			{
				loopNestCount--;
			}
			loopLines.push_back(*loopLine);
			loopLine++;
		}
		return loopLines;
	}

	Command createCommand(std::string line)
	{
		const std::map<std::string, Commands> commandMapping{
			{"bounds", Commands::BOUNDS},
			{"pen-pos", Commands::PEN_POS},
			{"pen-sym", Commands::PEN_SYM},
			{"step", Commands::STEP},
			{"draw", Commands::DRAW},
			{"rotate", Commands::ROTATE},
			{"undo", Commands::UNDO},
			{"loop", Commands::LOOP},
			{"display", Commands::DISPLAY},
			{"clear", Commands::CLEAR},
		};

		std::vector<std::string> deconstructed = separateLineBySpace(line);
		std::string commandString = deconstructed.at(0);

		Commands commandType = commandMapping.at(commandString);
		
		std::vector<int> parameters;
		auto stringToInt = [] (std::string string) -> int { return  string != "" ? std::stoi(string) : 0; };
		std::transform(deconstructed.begin() + 1, deconstructed.end(), std::back_inserter(parameters), stringToInt);
		return Command(commandType, parameters);
	}

	std::vector<Command> getCommandSequence(std::vector<std::string>& lines)
	{
		std::vector<Command> sequence;
		for (auto it = lines.begin(); it != lines.end(); it++)
		{
			Command command = createCommand(*it);
			if (command.getCommand() == Commands::LOOP) 
			{
				std::vector<Command> loopCommands;
				std::vector<std::string> loopLines = readLoopLines(lines, it + 1);
				for (std::string& line : loopLines) 
				{
					loopCommands.push_back(createCommand(line));
				}
				int repCount = command.getParameters()[0];
				while (repCount-- > 0)
				{
					for (Command& loopCommand : loopCommands)
					{
						sequence.push_back(loopCommand);
					}
				}
				it += loopLines.size() + 1;
			}
			else
			{
				sequence.push_back(command);
			}
		}
		return sequence;
	}

	void executeCommandSequence(std::vector<Command> commands, int repCount)
	{
		while(repCount-- > 0) 
		{
			for (Command& command : commands)
			{
				pen.execute(command);
			}
		}
	}

	std::string readLine() 
	{
		std::string line{};
		if (std::getline(std::cin, line))
		{
			return line;
		}
		else
		{
			return "";
		}
	}

	std::vector<std::string> separateLineBySpace(std::string& line)
	{
		std::vector<std::string> result;
		line += " ";
		for (std::string::size_type i = 0, prev = 0; i < line.length(); i++)
		{
			if (line.at(i) == ' ')
			{
				result.push_back(line.substr(prev, i-prev));
				prev = i + 1;
			}
		}
		return result;
	}

	void end()
	{
		std::cout << "Final Output: \n";
		pen.generateOutput();
	}
};