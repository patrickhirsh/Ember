#pragma once

/* This file contains definitions of types used accross Ember's API */
namespace Ember
{
	/* === EMBER APPLICATION INITIALIZATION OPTIONS ===
	Options for initializing a new Ember application. Ember uses Hzeller's rpi-rgb-led-matrix-lib 
	to interface with DMD hardware. Documentation for these hardware options can be found in: 
	"Ember/lib/rpi-rgb-led-matrix/include/led-matrix.h" */
	struct Options
	{
		/* === EMBER INIT OPTIONS === */
		int				panelWidth = 64;			// width of a single panel
		int				panelHeight = 32;			// height of a single panel
		int				panelCountX = 4;			// number of panels horizontal in the panel array
		int				panelCountY = 2;			// number of panels vertically in the panel array
		bool			flipVertical = false;		// flip output orientation vertically
		bool			flipHorizontal = false;		// flip output orientation horizontally

		/* === RPI-RGB-LED-MATRIX-LIB INIT OPTIONS === */
		const char* 	hardwareMapping = "regular";
		int				gpioSlowdown = 3;
		int				pwmBits = 11;
		int 			pwnLsbNanoseconds = 130;
		int 			pwnDitherBits = 0;
		int				scanMode = 0;
		int				rowAddressType = 0;
		int				multiplexing = 0;
		bool			disableHardwarePulsing = false;
		const char*		ledRgbSequence = "RGB";
		const char*		pixelMapperConfig = NULL;
		const char*		panelType = NULL;

		/* === VIRTUAL DISPLAY INIT OPTIONS === */
		float 			virtualScaleFactor = 3;
	};

	struct Color
	{
		Color() : r(0), g(0), b(0), a(0) {}
		Color(uint8_t rr, uint8_t gg, uint8_t bb, uint8_t aa) : r(rr), g(gg), b(bb), a(aa) {}
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};
}