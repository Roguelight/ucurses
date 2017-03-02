// Copyright Tue Feb 21 01:33:11 2017
// Liam Rogers, All rights reserved.

/*
 * Defines coordinate types used to make functions taking
 * x,y parameters more readable. 
 */

#pragma once
#include <functional>
#include <algorithm>

namespace ncursespp { namespace gui {

    using coord = short;
    /*
     * Coordinates in ncurses a passed with the y axis first
     */

    using index = unsigned short;

    struct coord2d
    {
        coord y;
        coord x;
        coord2d(coord inX, coord inY) : x(inX), y(inY)  {}
        coord2d(const coord2d& src) : x(src.x), y(src.y)  {}
        coord2d() : x(0), y(0)  {}
    };
    /*
     * Ncurses always passes the y coord in first
     * This wrapper will reverse this so x can be passed first
     */
    
    
}}
