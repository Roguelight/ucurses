/*
 *
 *
 */

#pragma once


namespace ucurses { 

	class Slider
	{
		public:

			Slider(coord x, coord y, Window* host);

			virtual void bindDefault();

            void increment();                           /* Encapsulated value increment */
            void decrement(); 

            float getValue()                            { return value; }

        protected:	
            
            virtual void Draw();

            float value;

	};

}
