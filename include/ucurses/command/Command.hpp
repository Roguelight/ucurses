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
		Command() : function(nullptr) {}

        friend bool operator==(const Command& lhs, const int& rhs) 
        {
            if (lhs.key == rhs)
                return true;
            else
                return false;
        }
        
        void execute() { if (function) function(); }
		void disable() { key = -1; }
        
		delegate function;
        int key;

    };

    class CommandArray
    {
        public:

            CommandArray(size_t size = 8);

            void Add(int key, delegate func);
            void Clear();
            void Disable(int key); 
            
			void Process(int key); 

        private:

            vector<Command> commands;
    };

}
