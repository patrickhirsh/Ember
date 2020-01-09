#include "Core.h"

namespace _Ember
{
	Core::Core(Ember::Options& options)
	{
#if VIRTUAL
		_render = new VirtualRender(options);
#else
		_render = new HardwareRender(options);
#endif
	}

	Core::~Core()
	{
		return;
	}
}