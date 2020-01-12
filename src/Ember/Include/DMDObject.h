#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <set>
#include <stdio.h>
#include <vector>
#include "Memory.h"
#include "Log.h"
#include "EmberMeta.h"

namespace _Ember
{
	/* Container for a DMDObject raster */
	class Raster
	{
	public:
		Raster(
			const Ember::Ref<const std::tuple<int, int>> 							origin, 
			const Ember::Ref<const std::tuple<int, int>> 							dimensions,
			const Ember::Ref<const std::vector<std::vector<Ember::Color>>> 			raster) :
			_origin(origin), _dimensions(dimensions), _raster(raster) {}

		const Ember::Ref<const std::tuple<int, int>> GetOrigin						() const { return _origin; }
		const Ember::Ref<const std::tuple<int, int>> GetDimensions					() const { return _dimensions; }
		const Ember::Ref<const std::vector<std::vector<Ember::Color>>> GetRaster	() const { return _raster; }
	private:
		const Ember::Ref<const std::tuple<int, int>> 								_origin;
		const Ember::Ref<const std::tuple<int, int>>								_dimensions;
		const Ember::Ref<const std::vector<std::vector<Ember::Color>>> 				_raster;
	};
}

namespace Ember
{
	class DMDObject
	{
	public: 	// static
		static const std::set<Ember::Ref<DMDObject>>* const GetObjects	();
	protected: 	// static
		static void RegisterObject										(Ember::Ref<DMDObject> object);
	private: 	// static
		static std::set<Ember::Ref<DMDObject>>*		 					_objects;

	public:
		virtual _Ember::Raster* Rasterize								() = 0;
	protected:
		virtual ~DMDObject												() { };
	};
}