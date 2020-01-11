#pragma once
#include "EmberPCH.h"
#include "Render.h"

namespace _Ember
{
	class Core
	{
	public:
		static Core* GetInstance	();
		static void Run				(Ember::Options options);

	private:
		Core						() { };
		static Core* 				_instance;
		static bool 				_running;
		
		void initialize				(Ember::Options& options);
		void run 					();
		void terminate				();
		
		Render* 					_render; 
	};
}