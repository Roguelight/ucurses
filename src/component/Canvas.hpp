/*
 * Canvas for drawing to a 2D array . Uses C style arrays and component
 * coord2d size for tracking array size. Provides low level access and does
 * not support dynamic allocation unlike Label.
 *
 * Stores symbol and color data for each cell allowing for individually colored
 * cells
 */

#pragma once
#include <ucurses/component/Component.hpp>
#include <ctk/storage/Array.hpp>


namespace ucurses { 

    class Canvas : public Component
    {
        public:

            Canvas(Window* win, coord2d size);

            //const ArrayXc* data;
            ctk::Array<Cell> cells;

            void Fill(char c, unsigned short color = 1);
            void Clear();
            void setSpread(bool b);

            void centerWindow();

            /* Refreshes component size for safe updating */
            //void setTarget(const ArrayXc* target, coord xsize = 0, coord ysize = 0);
            //void setTarget(const ArrayXc* target, coord2d size);

        protected:

            virtual void Draw();
            void bindDefault() {}

            // Used to print spaces between cells to give them a more square feel
            bool spread = false;
    };
}
