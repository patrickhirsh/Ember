#pragma once
#include "EmberPCH.h"

namespace Ember
{
	class DMDObject
	{
	public:
		virtual DMDObject* Create() = 0;
		virtual void Destroy() = 0;
	};
}