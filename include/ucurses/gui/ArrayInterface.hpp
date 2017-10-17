/*
 *
 *
 */

#pragma once
#include <ctk/storage/Array.hpp>
#include <ucurses/window/Window.hpp>
#include <ucurses/window/Interface.hpp>

namespace ucurses {

	template <typename T>
	class ArrayInterface : public Interface
	{
		public:

			ArrayInterface(ctk::Array<T>& arr);

			virtual void Bind(Window* win);

		protected:

			Menu* actions;
			Label* header;
			ctk::Array<T>& arr;

	};
}

#include <ucurses/gui/ArrayInterface_def.hpp>



