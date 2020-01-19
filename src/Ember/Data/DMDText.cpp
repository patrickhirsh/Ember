#include "DMDText.h"

namespace Ember
{
	Ember::Ref<DMDText> DMDText::Create()
	{
		return Ember::Ref<DMDText>(new DMDText());
	}

	Ember::Ref<_Ember::Raster> DMDText::Rasterize()
	{
		return nullptr;
	}
}