/*
 *
 *
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

            void appendText(const std::string& inText); 
			/* 
			 * Appends text at line, 
			 * if invalid: append to last line 
			 */
            void setText(const std::string& inText);    // Sets text at line
			/* 
			 * Sets text at line, 
			 * if invalid: create new line at end 
			 */

			void appendLine(const std::string& inText = "");
			
			void setCursor(int pos)  	{ cursor = pos; }
			int getCursor()				{ return cursor; }

			void Next()					{ ++cursor; }
			void Prev()					{ --cursor; }

            const std::string& getText() const;
            const std::string& getTextAt(short linepos = 0) const;
			void loadFromFile(const std::string& filename);
            
            void Clear();

        protected:

            std::vector<std::string> text;
			unsigned int cursor = FIRST;

            void bindDefault() {}
            virtual void Update();
	};

}
