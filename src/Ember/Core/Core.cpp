#include "Core.h"

namespace _Ember
{
	////////////////////////////////////////////////////////////////////////////////
	// Core

	/* statics */
	Core* Core::_instance = new Core();
	bool Core::_running = false;

	/* interupt management */
	volatile bool interruptReceived = false;
	static void InterruptHandler(int signo)
	{
		interruptReceived = true;
	}

	void Core::Run(
			Ember::Options options,
			std::function<void()> ApplicationTick,
			std::function<void()> ApplicationOnEvent
	)
	{
		if (_running)
		{
			LOG_ERROR("an instance of Ember is already running");
			return;
		}
		_instance->initialize(options);
		_instance->run(ApplicationTick);
		_instance->terminate();
	}

	void Core::initialize(Ember::Options& options)
	{
		// listen for interupts
		signal(SIGTERM, InterruptHandler);
    	signal(SIGINT, InterruptHandler);

		// system startup
		LOG_INFO("========== Ember Startup ==========");
		LOG_INFO("Initializing " << (VIRTUAL ? "Virtual" : "Hardware") << " Render System...");
		_render = new RenderSystem(options);
		
		_running = true;
		LOG_INFO("Startup Complete!");
	}

	void Core::run(std::function<void()> ApplicationTick)
	{
		while(!interruptReceived)
		{
			ApplicationTick();
			_render->RenderFrame(PollDrawRequests());
		}
	}

	void Core::terminate()
	{
		LOG_INFO("========== Ember Shutdown ==========");
		LOG_INFO("Terminating " << (VIRTUAL ? "Virtual" : "Hardware") << " Render System...");
		delete _render;
		_render = nullptr;

		_running = false;
		LOG_INFO("Shutting Down");
	}

	////////////////////////////////////////////////////////////////////////////////
}