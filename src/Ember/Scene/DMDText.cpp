#include "DMDText.h"

namespace Ember
{
	Ember::Ref<DMDText> DMDText::Create()
	{
		Ember::Ref<DMDText> object(new DMDText());
		DMDObject::RegisterObject(object);
		return object;
	}

	_Ember::Raster* DMDText::Rasterize()
	{
		return nullptr;
	}
}