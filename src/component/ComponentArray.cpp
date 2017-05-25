// Copyright Fri Mar 10 18:04:52 2017
// Liam Rogers, All rights reserved.

#include <ucurses/component/ComponentArray.hpp>
#include <ctk/log/GlobalLogger.hpp>
using namespace ctk::log;

namespace ucurses { 

    ComponentArray::ComponentArray()
    {
        M_Components.reserve(8);
    }

    ComponentArray::~ComponentArray()
    {
        for (auto& component : M_Components)
        {
            delete component;
            component = nullptr;
        }
    }

    void ComponentArray::Add(Component* component)
    {
        M_Components.push_back(component);
    }

    void ComponentArray::Update()
    {
        GlobalLogger::instance().log(TRACE) << "Updating components" << Sentinel::END;
        for (auto& component : M_Components)
            component->Update();
    }

    void ComponentArray::RemoveAll()
    {
        for (auto& component : M_Components)
        {
            delete component;
            component = nullptr;
        }
        M_Components.clear();
    
    }

}
