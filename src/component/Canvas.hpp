/*
 * Canvas for drawing to a 2D array . Uses C style arrays and component
 * coord2d size for tracking array size. Provides low level access and does
 * not support dynamic allocation unlike Label.
 *
 */

#pragma once
#include <ucurses/component/Component.hpp>
#include <Eigen/Dense>

using namespace Eigen;
typedef Array<char, Dynamic, Dynamic> ArrayXc;

namespace ucurses { 

	class Canvas : public Component
	{
		public:

			Canvas(Window* win, coord x = 0, coord y = 0);

			const ArrayXc* data;

			/* Refreshes component size for safe updating */
			void setTarget(const ArrayXc& target, coord xsize, coord ysize);
			void setTarget(const ArrayXc& target, coord2d size);

		protected:

			virtual void Draw();
			void bindDefault() {}

	};

}
