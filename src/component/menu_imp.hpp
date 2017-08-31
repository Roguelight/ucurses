#define NOSELECT -1

template <typename T>
menu_template<T>::menu_template()
{
	items.reserve(8);
	selection = NOSELECT;
}

template <typename T>
void menu_template<T>::removeItem(short id)
{
	if (selection != NOSELECT)
	{
		if (last()) 
			selection--;

		items.erase(items.begin() + id);

		if (items.empty())
			selection = NOSELECT;
	}
}

template <typename T>
T& menu_template<T>::addItem(const std::string& label)
{
	selection = 0;
	items.emplace_back(label);
	return items.back();
}

template <typename T>
void menu_template<T>::removeSelectedItem()
{
	short id = getSelectedIndex();
	removeItem(id);
}

template <typename T>
void menu_template<T>::removeAll()
{
	items.clear(); 
}

template <typename T>
void menu_template<T>::selectNext()
{
	if (!(items.empty()))
	{
		if (!last()) 
			++selection;
	}
	else
		selection = NOSELECT;
}

template <typename T>
void menu_template<T>::selectPrevious()

	if (!(items.empty()))
	{
		if (selection > 0)
			--selection;
	}
	else
		selection = NOSELECT;
}

template <typename T>
const T& menu_template<T>::getSelectedItem()
{
	if (selection != NOSELECT) 
		return getItem(selection); 
}

template <typename T>
const T& menu_template<T>::back()
{
	return items.back();
}

template <typename T>
short menu_template<T>::getSelectedIndex()
{
	return selection;
}

template <typename T>
const T& menu_template<T>::getItem(short id) 
{
	if (id < items.size())
		return items[id];
}

template <typename T>
const std::vector<T>& menu_template<T>::getItems() const
{
	return items;
}

template <typename T>
std::vector<T>& menu_template<T>::getItems()
{
	return items;
}
