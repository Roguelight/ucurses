// Copyright Fri Mar 10 18:04:52 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once

namespace ncursespp { namespace gui {

    class ComponentArray
    {

        public:

            ComponentArray(size_t n); // Size supplied by the window host

            void Add(Component* component);

        protected:

            vector<Component*, size_t> M_Components;

    }

}}
