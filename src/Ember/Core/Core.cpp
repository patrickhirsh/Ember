#include "Core.h"

namespace _Ember
{
	Core::Core(Ember::Options& options)
	{
		_render = new RenderSystem(options);
	}

	Core::~Core()
	{
		return;
	}
}