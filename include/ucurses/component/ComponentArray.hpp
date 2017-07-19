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
            void RemoveAll();
            const int getSize() const;

        protected:

            std::vector<Component*> M_Components;
            /* 
             * Prefix M_ indicates owner of this data is responsible
             * for memory management of every instance of this data
             */
    };

}
