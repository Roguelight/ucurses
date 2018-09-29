/*
 * Mix-in class to avoid code duplication
 *
 * Handles all basic slider functionality without inheriting from ucurses component
 * Originally created for use with the SliderMenu
 *
 * Protected constructor enforces use through inheritance
 *
 */

#pragma once
#include <string>
#include <fstream>

namespace ucurses { 

	class basic_slider
	{
		public:

			basic_slider();
			basic_slider(const std::string& subject);

			void increment();                           	/* Encapsulated value increment */
			void decrement(); 

			inline float getValue() const					{ return value; }
			inline const std::string& getSubject() const	{ return subject; }

			void setSubject(const std::string& name)		{ subject = name; } 
			void setValue(float f) 							{ value = f; } 

		protected:

			float value;
			std::string subject;
	};

}
