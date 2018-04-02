// Copyright Wed Mar  1 02:51:59 2017
// Liam Rogers, All rights reserved.

#include <ucurses/command/Command.hpp>
#include <iostream>

namespace ucurses { 

	CommandArray::CommandArray(size_t size)
	{ 
		commands.reserve(size); 
	}

	void CommandArray::Disable(int key)
	{ 
		auto it = std::find(commands.begin(), commands.end(), key); // Linear search
		if (it != commands.end())
		{
			commands[it - commands.begin()].disable();
		}
	}

	void CommandArray::Add(int key, delegate func)
	{ 
		commands.push_back(Command(key, func)); 
	}

	void CommandArray::Clear()
	{
		commands.clear();
	}

	void CommandArray::Process(int key) 
	{
		auto parse = [](Command& command, int key) { if (command.key == key) command.execute(); };
		for (auto& command : commands)
        {
            if (key != 27)
			    parse(command, key);
		}
	}
            
    void CommandArray::write_form(std::ostream& stream) const
    {
        if (stream)
        {
            stream << "<Size>: " << commands.size() << std::endl;
            for (auto& command : commands)
                command.write_form(stream);
        }
    }
    
    void Command::write_form(std::ostream& stream) const
    {
        if (stream)
        {
            stream << "<Key> " << key;
            stream << "\n<Delegate> ";
            if (function)
                stream << "Set";
            else
                stream << "Null";
            stream << std::endl;
        }
    }
}
