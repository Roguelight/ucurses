// Copyright Fri Mar 10 18:04:52 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/ComponentArray.hpp>


namespace ncursespp { namespace gui {

    ComponentArray::ComponentArray(size_t n)
    {
        M_Components.reserve(n);
    }

    ComponentArray::Add(Component* component)
    {
        M_Components.emplace_back(component);
    }

}}
