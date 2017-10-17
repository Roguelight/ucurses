namespace ucurses {

	template <typename T>
	ArrayInterface<T>::ArrayInterface(ctk::Array<T>& arr) : arr(arr)
	{
	
	}

	template <typename T>
	void ArrayInterface<T>::Bind(Window* win)
	{
		Interface::Bind(win);
		win->setTitle("Array Interface");
        actions = new Menu(pos.x + 2, pos.y + 6, win);
		actions->addItem("Display");
		actions->addItem("Add");
		actions->addItem("Inspect");
		header = new Label(pos.x + 2, pos.y + 4, win);
		header->setText("Array Size: " + to_string(arr.getSize()));
	}


}
