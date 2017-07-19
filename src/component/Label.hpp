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

            // Performs check if line exists, if so performs copy assignment
            void setTextAt(const std::string& inText, short linepos = 0); 
            void setText(const std::string& inText);

            /* Safe Appendage */
            
            // Performs check if line exists, if so applies operator+= 
            void appendText(const std::string& inText);
            void appendTextAt(const std::string& inText, short linepos = 0);
            void appendLine(const std::string& inText = "");

            const std::string& getText() const;
            const std::string& getTextAt(short linepos = 0) const;
            
            void Clear();

        protected:

            std::vector<std::string> text;

            void bindDefault() {}
            virtual void Update();
	};

}
