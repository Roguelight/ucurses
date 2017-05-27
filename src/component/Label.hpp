/*
 *
 *
 */

#pragma once
#include <ucurses/component/Component.hpp>
#include <string>

namespace ucurses { 

	class Label : public Component
	{
		public:

            Label(coord x, coord y, Window* host);

            void setText(std::string inText);
            void appendText(std::string inText);

            const std::string& getText() const;


        protected:

            std::string text;

            void bindDefault() {}
            virtual void Update();

	};

}
