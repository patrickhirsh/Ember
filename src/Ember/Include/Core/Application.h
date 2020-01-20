#pragma once
#include "EmberPCH.h"
#include "Core.h"

namespace Ember
{
	////////////////////////////////////////////////////////////////////////////////
	// Ember Application

	class Application
	{
	public:
		Application();
		void Run(
			Options Options,
			std::function<void()> DerivedApplicationTick,
			std::function<void()> DerivedApplicationOnEvent);

		virtual ~Application();
		virtual void Tick() = 0;
		virtual void OnEvent() = 0;
	};

	/* Used to pass derived ember application metadata back to the Ember Engine */
	struct ApplicationToken
	{
	public:
		ApplicationToken(
			Application* 			application,			// pointer to derived application
			Options 				options,				// ember engine initialization options (see EmberMeta.h)
			std::function<void()> 	applicationTick,		// pointer to derived Tick() method (callback)
			std::function<void()> 	applicationOnEvent) 	// pointer to derived OnEvent() method (callback)
			: 
			_application(application), _options(options), 
			_applicationTick(applicationTick), _applicationOnEvent(applicationOnEvent) {}

		Application* 			_application;			
		Options 				_options;				
		std::function<void()>	_applicationTick;		
		std::function<void()>	_applicationOnEvent;	
	};

	/* This function should create an instance of the client's derived ember application
	class, and pass it within the ApplicationToken - along with ember initialization
	options (see EmberMeta.h) and pointers to the derived Tick() and OnEvent() functions. eg:

	ApplicationToken Ember::CreateApplication()
	{
		auto instance = new DerivedEmberApplication();
		return ApplicationToken(
			instance,
			Options(),
			std::bind(&Sandbox::Tick, instance),
			std::bind(&Sandbox::OnEvent, instance));
	}
	=== To be defined in CLIENT === */
	ApplicationToken CreateApplication();

	////////////////////////////////////////////////////////////////////////////////
}