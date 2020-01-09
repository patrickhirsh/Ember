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
		_core = new _Ember::Core(options);
        while(true);
    }
}