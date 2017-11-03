/*
 *
 *
 */

#pragma once
#include <ctk/storage/Array.hpp>
#include <ucurses/window/Window.hpp>

namespace ucurses {

	template <typename T>
	class ArrayInterface : public Interface
	{
		public:

			ArrayInterface(ctk::Array<T>& arr);

			virtual void Bind(Window* win);

			void refreshFormat();
			void Display();

			void Select();

		protected:

			Menu* actions;
			HorizontalMenu* format_select;
			enum _actions { DISPLAY = 0, ADD };
			Label* header;
			Label* obj_display;
			ctk::Array<T>& arr;
			ctk::Format format;

	};
}

#include <ucurses/gui/ArrayInterface_def.hpp>



