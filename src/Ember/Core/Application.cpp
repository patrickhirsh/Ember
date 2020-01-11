#include "Application.h"

namespace Ember
{
    Application::Application()
    {
		
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
		_Ember::Core::Run(options);
    }
}