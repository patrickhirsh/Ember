#pragma once
#include "EmberPCH.h"


namespace _Ember
{
	/* Container for a DMDObject raster */
	class Raster
	{
	public:
		Raster(
			const std::tuple<int, int> 									origin, 
			const std::tuple<int, int> 									dimensions,
			const std::vector<std::vector<Ember::Color>> 				rawRaster) 
			:
			Origin(origin), Dimensions(dimensions), RawRaster(rawRaster) {}

		const std::tuple<int, int> 										Origin;
		const std::tuple<int, int>										Dimensions;
		const std::vector<std::vector<Ember::Color>> 					RawRaster;
	};

	/* Poll the state of Ember's data layer. Processes and compiles a queue of
	draw requests from all active objects. Polling draw requests will clear the
	queue of active objects. Performed once per engine tick. */
	const Ember::Ref<std::vector<Ember::Ref<_Ember::Raster>>> PollDrawRequests();
}

namespace Ember
{
	class DMDObject
	{
	/* DMDObject Management */
	public:
		friend const Ember::Ref<std::vector<Ember::Ref<_Ember::Raster>>> _Ember::PollDrawRequests();
	private: 
		static std::vector<Ember::Ref<DMDObject>>* _drawRequests;

	/* DMDObject Base */
	public:
		/* Registers this object for drawing during the next engine tick */
		void Draw														();

	/* DMDObject Derived */
	public:
		virtual ~DMDObject												() { };					
	protected:
		virtual Ember::Ref<_Ember::Raster> Rasterize					() = 0;
	};
}