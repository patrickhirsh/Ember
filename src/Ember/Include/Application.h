#pragma once
#include "EmberPCH.h"
#include "Core.h"

namespace Ember
{
	class Application
	{
	public:
		Application();
		void Run();

		virtual ~Application();
		virtual void Tick() = 0;
		virtual void OnEvent() = 0;

		/* Application initialization options. These should be set prior to 
		returning the Application* in the Ember::CreateApplication() implementation.
		Definition for this type (and its defaults) can be found in EmberMeta.h */
		Options options;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}