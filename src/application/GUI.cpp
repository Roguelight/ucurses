// Copyright Sun Feb 19 02:16:35 2017
// Liam Rogers, All rights reserved.

#include <ncursespp/application/GUI.hpp>

namespace ncursespp { namespace application {

	GUI::GUI()
	{
        GlobalLogger::log(TRACE) << "Initialising ncursespp GUI" << Sentinel::END;
	}

	GUI::~GUI()
	{
        GlobalLogger::log(TRACE) << "Destroying ncursespp GUI" << Sentinel::END;
        
	}

    void GUI::Render()
    {
        Windows.Render();
    }

    void GUI::Update()
    {
        Windows.Update();
    }

    

}}
