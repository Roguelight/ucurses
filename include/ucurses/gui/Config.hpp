/*
 * Color configuration screen for UCurses
 *
 */

#pragma once
#include <ucurses/window/Interface.hpp>

namespace ucurses { 

	class SliderMenu;
	class Config : public Interface
	{
		public:

			void RefreshUI();
			void Escape();

			void Save();
			bool LoadSliders();
			static void Load();
		
			static std::string config;

		protected:
			
			virtual void Initialize();

			SliderMenu* menu;
	};

}
