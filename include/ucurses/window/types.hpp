// Copyright Tue Feb 21 01:33:11 2017
// Liam Rogers, All rights reserved.

/*
 * Defines coordinate types used to make functions taking
 * x,y parameters more readable. 
 */

#pragma once
#include <functional>
#include <algorithm>

namespace ucurses { 

	using coord = short;
	/*
	 * Ncurses always passes the y coord in first
	 * This wrapper will reverse this so x can be passed first
	 */ 
	struct coord2d
	{
		short y;
		short x;
		coord2d(short inX, short inY) : x(inX), y(inY)  {}
		coord2d(const coord2d& src) : x(src.x), y(src.y)  {}
		coord2d() : x(0), y(0)  {}

		coord2d& operator+=(const coord2d rhs) 
		{ 
			this->x += rhs.x;
			this->y += rhs.y;
		}
		coord2d& operator-=(const coord2d rhs) 
		{ 
			this->x -= rhs.x;
			this->y -= rhs.y;
		}
	};
		
	inline coord2d operator-(coord2d lhs, coord2d rhs) 
	{ 
		lhs -= rhs;
		return lhs;
	}
	inline coord2d operator+(coord2d lhs, coord2d rhs) 
	{ 
		lhs += rhs;
		return lhs;
	}


}
