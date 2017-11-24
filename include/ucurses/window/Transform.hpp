/*
 * All objects that have a position and can be moved will
 * use this mix in class. Initially created to remove redundant
 * transform code in Component and Interface classes
 */

namespace ucurses {

	class Transform
	{
		public:

			Transform();

			void setPosition(coord x, coord y);
			coord2d pos;



	};

}
