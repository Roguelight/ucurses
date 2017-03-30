// Copyright Fri Mar 10 18:04:52 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/gui/ComponentArray.hpp>


namespace ncursespp { namespace gui {

    ComponentArray::ComponentArray()
    {
        M_Components.reserve(8);
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

    void ComponentArray::RemoveAll()
    {
        GlobalLogger::log(TRACE,"NCursespp::ComponentArray") << "Removing all components from array" << Sentinel::END;
        for (auto& component : M_Components)
        {
            delete component;
            component = nullptr;
        }
        M_Components.clear();
    
    }

}}
