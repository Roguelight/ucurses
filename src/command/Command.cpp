// Copyright Wed Mar  1 02:51:59 2017
// Liam Rogers, All rights reserved.

#include <ucurses/command/Command.hpp>

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
    }/*
    * Less expensive to access a single bit than remove the index
    * from all vectors
    */
    
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
			parse(command, key);
    }
}
