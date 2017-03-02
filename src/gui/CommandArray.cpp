// Copyright Wed Mar  1 02:51:59 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/CommandArray.hpp>

namespace ncursespp { namespace gui {

	CommandArray::CommandArray()
    { 
        functions.reserve(16); 
        keys.reserve(16); 
        active.reserve(16);
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
    
    void CommandArray::Add(delegate func, int key)
    { 
        keys.push_back(key); 
        functions.push_back(func); 
        active.push_back(true);
    }

    void CommandArray::parseInput(int key) 
    {
        auto it = std::find(keys.begin(), keys.end(), key);
        if (it != keys.end())
        {
            index keyindex = it - keys.begin();
            functions[keyindex]();
            GlobalLogger::log(TRACE) << "Executing function" << Sentinel::END;
        }
    }
}}
