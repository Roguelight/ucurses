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

			Label(coord x, coord y, Window* host);

			/* Safe sets ;) */ 

			void setText(const std::string& inText);    

			void appendText(const std::string& inText); 
			void appendLine(const std::string& inText = "");

			const std::string& getText() const;

			void loadFromFile(const std::string& filename);

			void Clear();

		protected:

			std::string text;

			void bindDefault() {}
			virtual void Draw();
	};

}
