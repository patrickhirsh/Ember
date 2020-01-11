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
			LOG_ERROR("An instance of Ember is already running");
			return;
		}

		_instance->initialize(options);
		_instance->run();
		_instance->terminate();
	}

	void Core::initialize(Ember::Options& options)
	{
		// listen for interupts
		signal(SIGTERM, InterruptHandler);
    	signal(SIGINT, InterruptHandler);

		_render = new RenderSystem(options);
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
		delete _render;

		_render = nullptr;
		_running = false;
	}

	////////////////////////////////////////////////////////////////////////////////
}