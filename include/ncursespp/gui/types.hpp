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

    /*
     * Coordinates in ncurses a passed with the y axis first
     */ using coord = short;

    /*
     * Ncurses always passes the y coord in first
     * This wrapper will reverse this so x can be passed first
     */ struct coord2d
    {
        coord y;
        coord x;
        coord2d(coord inX, coord inY) : x(inX), y(inY)  {}
        coord2d(const coord2d& src) : x(src.x), y(src.y)  {}
        coord2d() : x(0), y(0)  {}
        coord2d operator-(coord2d other) { return coord2d(x - other.x, y - other.y); }
        coord2d operator+(coord2d other) { return coord2d(x + other.x, y + other.y); }
    };
    
    
}}
