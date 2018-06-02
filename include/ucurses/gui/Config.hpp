/*
 * Color configuration screen for UCurses
 *
 */

#pragma once
#include <ucurses/window/State.hpp>

namespace ucurses { 

	class SliderMenu;
	class Config : public State
	{
		public:

			void RefreshUI();
			void Escape();

			void Save();
			bool LoadSliders();

            // Default parameter for legacy compatibility
			static void Load(const std::string& filepath = ".resources/config/color_scheme.conf");
		
			static std::string config;

		protected:
			
			virtual void Initialize();

			SliderMenu* menu;
	};

}
