/*
 *
 *
 */

#pragma once
#include <ctk/storage/Array.hpp>
#include <ucurses/window/State.hpp>

namespace ucurses {

	template <typename T>
	class ArrayInterface : public State
	{
		public:

			ArrayInterface(ctk::Array<T>& arr);


			void refreshFormat();
			void Display();

			void Select();

		protected:
			
			virtual void Initialize();

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



