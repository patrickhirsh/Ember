#include "Application.h"

namespace Ember
{
    Application::Application()
    {
		
    }

    Application::~Application()
    {

    }

    void Application::Run(
		Options Options,
		std::function<void()> DerivedApplicationTick,
		std::function<void()> DerivedApplicationOnEvent
	)
    {
		_Ember::Core::Run(
			Options, 
			DerivedApplicationTick, 
			DerivedApplicationOnEvent);
    }
}