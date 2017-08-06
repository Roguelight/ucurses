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

			void setText(const std::vector<string>& inText);   
			/* 
			 * Performs vector copy assignment 
			 */

			void setText(const std::string& inText);    
			/* 
			 * Sets text at cursor position, 
			 * if invalid: create new line at end 
			 */

			void appendLine(const std::string& inText = "");
			/*
			 * Adds line to end and updates cursor to new position
			 */

			void appendText(const std::string& inText); 
			/* 
			 * Appends text at cursor position, 
			 * if invalid: append to last line 
			 */

			const std::string& getText() const;
			const std::string& getTextAt(short linepos = 0) const;

			void setCursor(int pos)  	{ cursor = pos; }
			int  getCursor()			{ return cursor; }

			void Next()					{ ++cursor; }
			void Prev()					{ --cursor; }

			void loadFromText(const std::string& filename);

			void Clear();

		protected:

			std::vector<std::string> text;

			unsigned int cursor = FIRST; // Line position

			void bindDefault() {}
			virtual void Update();
	};

}
