#pragma once

/* RGB Matrix Library */
// https://github.com/hzeller/rpi-rgb-led-matrix
#include "../../../lib/rpi-rgb-led-matrix/include/led-matrix.h"
#include "../../../lib/rpi-rgb-led-matrix/include/threaded-canvas-manipulator.h"
#include "../../../lib/rpi-rgb-led-matrix/include/pixel-mapper.h"
#include "../../../lib/rpi-rgb-led-matrix/include/graphics.h"

namespace Ember
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}