
#pragma once
#include <ucurses/component/Component.hpp>
#include <ucurses/component/Menu.hpp>

namespace ucurses {

	class HorizontalMenu : public Menu
	{

		public:

			HorizontalMenu(Window* target, coord x = 0, coord y = 0);

		protected:

			virtual void Draw();
			virtual void Process(int input);
			virtual void bindDefault();

	};

}
