/*
 * UCurses GUI Object
 *
 * Provide safe, efficient and easy window management with pre-defined widgets for any terminal
 * application.
 *
 * Fixes x, y coordinate confusion by using x as first parameter in all position/size functions.
 *
 * nodelay() is required for windows that need to continuously update graphics for animations, clocks etc.
 *
 */

#pragma once
#include <string>

#include <ucurses/app/Color.hpp>
#include <ucurses/window/WindowContainer.hpp>
#include <ucurses/window/types.hpp>

namespace ucurses { 

	class UCurses
	{
		public:

			/* Construction */ 

			UCurses();
			~UCurses();
			void Run();                                     /* Application loop for input blocking programs */
			void Start();									/* Performs initial render before delaying for certain windows */

			/* Loop functions - In intended order */

			void handleInput();					            /* Executes all commands mapped to input */
			void Render();									/* Finally updates actual screen with all data from virtual windows */

			/* Windows */

			Window* createWindow(coord2d size, coord2d pos);	/* Size specific constructor */
			Window* createWindow();								/* Returns a window of maximum size */
			Window* getActiveWindow();

			void addCommand(int key, delegate function);		/* Application specific commands. Close/Tabbing etc. */
            
			coord2d getSize()	const;                         	/* Returns size of terminal screen */ 
			bool Running() const;
    
            void loadConfig(const std::string& filepath);

		protected:

			void removeAll();

			CommandArray Commands;	
			std::vector<string> tips;

		private:

			WindowContainer Windows;
			ColorContainer Colors;
			void End(); 
			
			bool running;
			bool help;

		public:

			void setHelp(bool b);
			bool showHelp();
			const std::vector<string>& getTips() const; 
	};
}
