// Copyright Fri Mar 10 18:04:52 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/ComponentArray.hpp>


namespace ncursespp { namespace gui {

    ComponentArray::ComponentArray()
    {
        GlobalLogger::log(WARNING,"NCursespp::ComponentArray") << "Constructing component array without reserving space" << Sentinel::END;
    
    }

    ComponentArray::ComponentArray(size_t n)
    {
        GlobalLogger::log(TRACE,"NCursespp::ComponentArray") << "Constructing component array and allocating space for " << n << " elements" << Sentinel::END;
        M_Components.reserve(n);
    }

    ComponentArray::~ComponentArray()
    {
        GlobalLogger::log(TRACE,"NCursespp::ComponentArray") << "Destroying component array" << Sentinel::END;
        for (auto& component : M_Components)
        {
            delete component;
            component = nullptr;
        }
    }

    void ComponentArray::Add(Component* component)
    {
        M_Components.emplace_back(component);
    }

    void ComponentArray::Update()
    {
        for (auto& component : M_Components)
            component->Update();
    }

}}
