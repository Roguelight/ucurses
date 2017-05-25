// Copyright Wed Mar  1 02:51:59 2017
// Liam Rogers, All rights reserved.

/*
 * DOD Implementation of command system for Ncurses.
 */

#pragma once
#include <ucurses/gui/types.hpp>
#include <functional>
#include <algorithm>
#include <vector>


namespace ucurses {

    using namespace std;
    using index = short;
    using delegate = std::function<void()>;

    struct Command
    {
        Command(int inKey, delegate inFunction) : key(inKey), function(inFunction) {};
        void execute() { function(); }
        delegate function;
        int key;
        friend bool operator==(const Command& lhs, const int& rhs) 
        {
            if (lhs.key == rhs)
                return true;
            else
                return false;
        }

    };

    class CommandArray
    {
        public:

            CommandArray();

            void Add(int key, delegate func);
            void Clear();
            void Disable(int key); 
            

            bool Parse(int key);
            /*
             * returns true if match found,
             * this will allow for a chain of reponsibility
             */

        private:
            vector<Command> commands;
            vector<bool> switches;
    };

}
