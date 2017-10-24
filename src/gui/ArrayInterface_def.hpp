namespace ucurses {

	template <typename T>
	ArrayInterface<T>::ArrayInterface(ctk::Array<T>& arr) : arr(arr), format(ctk::Format::BINARY)
	{
	
	}

	template <typename T>
	void ArrayInterface<T>::Bind(Window* win)
	{
		Interface::Bind(win);
		win->setTitle("Array Interface");
        actions = new Menu(win, pos.x + 2, pos.y + 6);
		actions->addItem("Display");
		actions->addItem("Add");
		actions->addItem("Inspect");
		header = new Label(win, pos.x + 2, pos.y + 4);
		header->setText("Array Size: " + to_string(arr.getSize()));
		obj_display = new Label(pos.x + 16, pos.y + 4, win);
        
		win->addCommand(10, bind(&ArrayInterface::Select, this));
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
        const T* element = arr.Get(0);
		std::stringstream ss;
		element->Write(ss, format);
		obj_display->setText(ss.str());
	}
	

}
