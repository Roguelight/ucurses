// Copyright Wed Mar  8 22:49:41 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once
#include <ucurses/component/Component.hpp>
#include <functional>

namespace ucurses { 

	class TextEntry : public Component
	{
		public:

			TextEntry(Window* host, coord x = 0, coord y = 0); 

			void setSubject(string inString);
			string& getText();
			void setText(const std::string& inString);
			
            void getInput(); // *->E
            std::function<void()> onTextEnter;

		protected:

			virtual void Draw();
			void bindDefault();
			virtual void Process(int input);

			string subject;
			string input;

			// Commands


	};

}
