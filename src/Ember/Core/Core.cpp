#include "Core.h"

namespace _Ember
{
	Core* Core::_instance = new Core();
	bool Core::_running = false;

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
		_running = true;
		_render = new RenderSystem(options);
	}

	void Core::run()
	{
		while(true);
	}

	void Core::terminate()
	{
		delete _render;

		_render = nullptr;
		_running = false;
	}
}