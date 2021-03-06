// Copyright Fri Mar 10 18:04:52 2017
// Liam Rogers, All rights reserved.

#include <ucurses/component/ComponentArray.hpp>
#include <ucurses/component/Component.hpp>

namespace ucurses { 

	ComponentArray::ComponentArray()
	{
		M_Components.reserve(8);
	}

	ComponentArray::~ComponentArray()
	{
		for (auto& component : M_Components)
			delete component;
	}

	void ComponentArray::Add(Component* component)
	{
		M_Components.push_back(component);
	}

	void ComponentArray::Update()
	{
		for (auto& component : M_Components)
			component->Update();
	}
	
	void ComponentArray::Process(int input)
	{
		for (auto& component : M_Components)
			component->_process(input);
	}

	void ComponentArray::Clear()
	{
		for (auto& component : M_Components)
			delete component;

		M_Components.clear();

	}

	const int ComponentArray::getSize() const
	{
		return M_Components.size();
	}

	const int ComponentArray::getCapacity() const
	{
		return M_Components.capacity();
	}

}
