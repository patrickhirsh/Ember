#pragma once
#include "EmberPCH.h"
#include "Render.h"
#include "DMDObject.h"

namespace _Ember
{
	////////////////////////////////////////////////////////////////////////////////
	// Core

	class Core
	{
	public:
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

	////////////////////////////////////////////////////////////////////////////////
}