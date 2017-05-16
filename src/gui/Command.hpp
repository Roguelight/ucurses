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

#include <ctk/log/GlobalLogger.hpp>
 
using namespace std;
using namespace ctk::log;

using delegate = std::function<void()>;

namespace ucurses { namespace gui {

    using index = short;

    class CommandArray
    {
        public:

            CommandArray();

            void Add(int key, delegate func) ;
            void Clear();
            void Disable(int key); 
            

            bool Parse(int key);
            /*
             * returns true if match found,
             * this will allow for a chain of reponsibility
             */

        private:
            vector<delegate> functions;
            vector<int> keys; 
            vector<bool> active;

            const size_t size = 8;
    };

}}
