// Copyright Wed Mar  1 02:51:59 2017
// Liam Rogers, All rights reserved.

#include <ucurses/command/Command.hpp>

namespace ucurses { 

	CommandArray::CommandArray()
    { 
        commands.reserve(8); 
        switches.reserve(8); 
    }

    void CommandArray::Disable(int key)
    { 
        auto it = std::find(commands.begin(), commands.end(), key); // Linear search
        if (it != commands.end())
        {
            switches[it - commands.begin()] = false;
        }
    }/*
    * Less expensive to access a single bit than remove the index
    * from all vectors
    */
    
    void CommandArray::Add(int key, delegate func)
    { 
        commands.push_back(Command(key, func)); 
        switches.push_back(true);
    }

    void CommandArray::Clear()
    {
        commands.clear();
        switches.clear();
    }

    bool CommandArray::Parse(int key) 
    {
        if (!(commands.empty())) 
        {
            auto it = std::find(commands.begin(), commands.end(), key);
            if (it != commands.end())
            {
                commands[it - commands.begin()].execute();
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
}
