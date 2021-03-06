#include <ucurses/gui/ArrayInterface.hpp>

namespace ucurses {

	template <typename T>
	ArrayInterface<T>::ArrayInterface(ctk::Array<T>& arr) : arr(arr), format(ctk::Format::BINARY)
	{
	
	}

	template <typename T>
	void ArrayInterface<T>::Initialize()
	{
		target->setTitle("Array Interface");
        actions = new Menu(target, pos.x + 2, pos.y + 6);

        format_select = new HorizontalMenu(target, pos.x + 2, pos.y + 9);
		format_select->addItem("Binary");
		format_select->addItem("Dump");
		format_select->addItem("Form");

		actions->addItem("Display");
		actions->addItem("Add");
		actions->addItem("Inspect");

		header = new Label(target, pos.x + 2, pos.y + 4);
		header->setText("Array Size: " + to_string(arr.getSize()));

		obj_display = new Label(target, pos.x + 24, pos.y + 4);
        
		target->Commands.Add(10, bind(&ArrayInterface::Select, this));
	}

	template <typename T>
	void ArrayInterface<T>::Select()
	{
		switch (actions->getSelectedIndex())
		{
			case _actions::DISPLAY:
				Display();
				break;
		}
	}
	
	template <typename T>
	void ArrayInterface<T>::Display()
	{
		refreshFormat();
        const T* element = arr.Get(0);
		std::stringstream ss;
		element->Write(ss, format);
		obj_display->setText(ss.str());
	}

	template <typename T>
	void ArrayInterface<T>::refreshFormat()
	{
		switch (format_select->getSelectedIndex())
		{
			case 0:
				format = ctk::Format::BINARY;
				break;
			case 1:
				format = ctk::Format::TEXT_DUMP;
				break;
			case 2:
				format = ctk::Format::FORM;
				break;
		}
	}
	

}
