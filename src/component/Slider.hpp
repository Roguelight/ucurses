/*
 * Command binding should be organised by the UI Context
 * 
 * Volume |-------------------|
 */

#pragma once
#include <ucurses/component/Component.hpp>
#include <ucurses/component/basic_slider.hpp>

namespace ucurses { 

	class Slider : public Component, public basic_slider
	{
		public:

			Slider(Window* host, coord x = 0, coord y = 0);

			void bindDefault();

        protected:	
            
            virtual void Draw();
	};

}
