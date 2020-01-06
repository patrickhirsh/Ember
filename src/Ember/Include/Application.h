#pragma once
#include "EmberPCH.h"

namespace Ember
{
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}