#include "DMDObject.h"

namespace Ember
{
	std::set<Ember::Ref<DMDObject>>* DMDObject::_objects = new std::set<Ember::Ref<DMDObject>>();

	const std::set<Ember::Ref<DMDObject>>* const DMDObject::GetObjects()
	{
		// check for deleted objects before returning updated object list
		std::vector<Ember::Ref<DMDObject>> expired;
		for (auto object : *_objects)
		{
			// dereference during iteration creates an addition reference (so, <= 2)
			if (object.use_count() <= 2) { expired.push_back(object); }
		}
		for (auto object : expired)
		{
			_objects->erase(object);
		}
		return _objects;
	}

	void DMDObject::RegisterObject(Ember::Ref<DMDObject> object)
	{
		bool located = false;
		for (auto existingObject : *_objects)
		{
			if (existingObject == object)
			{
				located = true;
				break;
			}
		}
		if (!located)
		{
			_objects->insert(object);
		}
		else
		{
			LOG_WARN("tried to register an existing DMDObject!");
		}
	}
}