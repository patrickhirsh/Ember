#pragma once
#include "EmberPCH.h"
#include "Render.h"

namespace _Ember
{
	class Core
	{
	public:
		Core(Ember::Options& options);
		~Core();
	private:
		Render* _render; 
	};
}