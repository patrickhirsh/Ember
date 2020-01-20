#pragma once
#include "EmberPCH.h"
#include "DMDObject.h"

namespace Ember
{
	class DMDText : public DMDObject
	{
		/* DMDObject Derived Implementation */
	public:
		Ember::Ref<_Ember::Raster> Rasterize	();
		~DMDText								() {};
	private:
		DMDText									() {};
	
		/* DMDText */
	public:
		static Ember::Ref<DMDText> Create		();
	};
}