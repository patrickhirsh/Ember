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

	Core* Core::GetInstance()
	{
		return _instance;
	}

	void Core::Run(Ember::Options options)
	{
		if (_running)
		{
			LOG_ERROR("an instance of Ember is already running");
			return;
		}

		_instance->initialize(options);
		_instance->run();
		_instance->terminate();
	}

	void Core::initialize(Ember::Options& options)
	{
		LOG_INFO("========== Ember Startup ==========");


		// listen for interupts
		signal(SIGTERM, InterruptHandler);
    	signal(SIGINT, InterruptHandler);

		LOG_INFO("Initializing " << (VIRTUAL ? "Virtual" : "Hardware") << " Render System...");
		_render = new RenderSystem(options);

		LOG_INFO("Startup Complete!");
		_running = true;
	}

	void Core::run()
	{
		while(!interruptReceived)
		{

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