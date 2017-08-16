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

			Slider(coord x, coord y, Window* host);

			void bindDefault();

        protected:	
            
            virtual void Draw();
	};

}
