/*
 * Dynamic Command Array that uses C++ std::function objects to encapsulate commands.
 * This approach does not require new object definition for each command however state
 * cannot be stored this way to support operations like undo history.
 */

#pragma once
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

        delegate function;
        int key;

        friend bool operator==(const Command& lhs, const int& rhs) 
        {
            if (lhs.key == rhs)
                return true;
            else
                return false;
        }
        
        void execute() { function(); }

    };

    class CommandArray
    {
        public:

            CommandArray();

            void Add(int key, delegate func);
            void Clear();
            void Disable(int key); 
            

            bool Parse(int key); 
            /* Returns 'true' if match found */

        private:
            vector<Command> commands;
            vector<bool> switches;
    };

}
