#pragma once
#include "EmberPCH.h"
#include "DMDObject.h"

namespace Ember
{
	class DMDText : public DMDObject
	{
	public:
		static Ember::Ref<DMDText> Create		();
		_Ember::Raster* Rasterize				();
		~DMDText								() {};
	private:
		DMDText									() {};
	};
}