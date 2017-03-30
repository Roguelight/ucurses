// Copyright Wed Mar  1 02:51:59 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/Command.hpp>

namespace ncursespp { namespace gui {

	CommandArray::CommandArray()
    { 
        GlobalLogger::log(TRACE, "Command:") << "Constructing Command Array with default size: " << size << Sentinel::END;
        functions.reserve(size); 
        keys.reserve(size); 
        active.reserve(size);
    }

    void CommandArray::Disable(int key)
    { 
        auto it = std::find(keys.begin(), keys.end(), key);
        if (it != keys.end())
        {
            index keyindex = it - keys.begin();
            active[keyindex] = false;
        }
    }/*
    * Less expensive to access a single bit than remove the index
    * from all vectors
    */
    
    void CommandArray::Add(int key, delegate func)
    { 
        keys.push_back(key); 
        functions.push_back(func); 
        active.push_back(true);
    }

    void CommandArray::Clear()
    {
        GlobalLogger::log(TRACE, "Command:") << "Clearing commands from Command array" << Sentinel::END;
        keys.clear();
        functions.clear();
        active.clear();
    }

    bool CommandArray::Parse(int key) 
    {
        if (!(keys.empty())) 
        {
            auto it = std::find(keys.begin(), keys.end(), key);
            if (it != keys.end())
            {
                GlobalLogger::log(TRACE, "Command") << "Executing function at key: " << key << Sentinel::END;
                index keyindex = it - keys.begin();
                functions[keyindex]();
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
}}
