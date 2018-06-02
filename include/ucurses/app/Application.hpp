#pragma once

#include <ctk/application/Application.hpp>
#include <ucurses/ucurses.hpp>

namespace ucurses {

    class Application : public ctk::Application
    {

        public:

            Application();

        protected:

            virtual void processInput();
            UCurses gui;
            Window* appwindow;

            void setName(const std::string& inName);

        private:

            virtual void Render();
    };
}
