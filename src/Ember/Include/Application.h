#pragma once
#include "EmberPCH.h"
#include "Core.h"

namespace Ember
{
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		/* Application initialization options. Set these in CreateApplication().
		Definition for this type (and its defaults) can be found in EmberMeta.h */
		Options options;
	private:
		_Ember::Core* _core;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}