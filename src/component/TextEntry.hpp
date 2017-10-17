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

			TextEntry(coord x, coord y, Window* host); 

			void bindDefault();
			void setSubject(string inString);
			string& getText();
			void setText(const std::string& inString);

		protected:

			virtual void Draw();
			std::function<void()> onEnter;


			string subject;
			string input;

			// Commands

			void getInput(); // *->E

	};

}
