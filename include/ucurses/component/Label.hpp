/*
 * Label for displaying text in paragraph form. 
 * Uses cursor to mark current line. 
 *
 * Most functions use cursor position and will append a new line if
 * label is empty for safe array access
 */

#pragma once
#include <ucurses/component/Component.hpp>
#include <string>
#include <vector>

#define FIRST 0
namespace ucurses { 

	class Label : public Component
	{
		public:

			Label(Window* host, coord x = 0, coord y = 0);

			/* Safe sets ;) */ 

			void setText(const std::string& inText);    

			void appendText(const std::string& inText); 
			void appendLine(const std::string& inText = "");

			const std::string& getText() const;
			std::string& getText();

			void loadFromFile(const std::string& filename);

			void Clear();

		protected:

			std::string text;

			virtual void Draw();
	};

}
