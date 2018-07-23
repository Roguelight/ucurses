// Copyright Fri Mar 10 18:04:52 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once
#include <vector>

namespace ucurses { 

	class Component;

	class ComponentArray
	{
		public:

			ComponentArray();
			~ComponentArray();

			void Add(Component* component);
			void Update();
			void Clear();
			const int getSize() const;
			const int getCapacity() const; 

			void Process(int input);

		protected:

			std::vector<Component*> M_Components;
	};

}
