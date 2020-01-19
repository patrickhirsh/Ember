#include "DMDObject.h"

namespace _Ember
{
	const Ember::Ref<std::vector<Ember::Ref<Raster>>> PollDrawRequests()
	{
		Ember::Ref<std::vector<Ember::Ref<Raster>>> rasterQueue(new std::vector<Ember::Ref<Raster>>()); 
		for (auto object : *Ember::DMDObject::_drawRequests)
		{
			rasterQueue->push_back(object->Rasterize());
		}
		Ember::DMDObject::_drawRequests->clear();
		return rasterQueue;
	}
}

namespace Ember
{
	std::vector<Ember::Ref<DMDObject>>* DMDObject::_drawRequests = new std::vector<Ember::Ref<DMDObject>>();

	void DMDObject::Draw()
	{
		_drawRequests->push_back(Ember::Ref<DMDObject>(this));
	}
}