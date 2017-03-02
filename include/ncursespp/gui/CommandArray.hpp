// Copyright Wed Mar  1 02:51:59 2017
// Liam Rogers, All rights reserved.

/*
 * DOD Implementation of command system for Ncurses.
 */

#pragma once
#include <ncursespp/gui/types.hpp>
#include <functional>
#include <algorithm>
#include <vector>

#include <ctk/log/GlobalLogger.hpp>
 
using namespace std;
using namespace ctk::log;

namespace ncursespp { namespace gui {

    using delegate = std::function<void()>;

    class CommandArray
    {
        public:
            CommandArray() ;

            void Add(delegate func, int key) ;

            void Disable(int key); 
            

            void parseInput(int key);

        private:
            vector<delegate> functions;
            vector<int> keys; 
            vector<bool> active;
    };

}}
