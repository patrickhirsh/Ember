#include "Render.h"

namespace _Ember
{

	////////////////////////////////////////////////////////////////////////////////
	// Hardware Rendering

#if !VIRTUAL
	RenderSystem::RenderSystem(Ember::Options& options)
	{
		// init Render
		initialize(options);

		// rgb-matrix options
		rgb_matrix::RGBMatrix::Options matrixOptions;
		matrixOptions.hardware_mapping = options.hardwareMapping;
		matrixOptions.rows = options.panelHeight;
		matrixOptions.cols = options.panelWidth;
		matrixOptions.chain_length = options.panelCountX;
		matrixOptions.parallel = options.panelCountY;
		matrixOptions.pwm_bits = options.pwmBits;
		matrixOptions.pwm_lsb_nanoseconds = options.pwnLsbNanoseconds;
		matrixOptions.pwm_dither_bits = options.pwnDitherBits;
		matrixOptions.scan_mode = options.scanMode;
		matrixOptions.row_address_type = options.rowAddressType;
		matrixOptions.multiplexing = options.multiplexing;
		matrixOptions.disable_hardware_pulsing = options.disableHardwarePulsing;
		matrixOptions.led_rgb_sequence = options.ledRgbSequence;
		matrixOptions.pixel_mapper_config = options.pixelMapperConfig;
		matrixOptions.panel_type = options.panelType;

		// init GPIO
		_gpio = new rgb_matrix::GPIO();
		_gpio->Init(options.gpioSlowdown);

		// init Hardware
		_matrix = new rgb_matrix::RGBMatrix(_gpio, matrixOptions);
		if (_matrix == nullptr) { LOG_ERROR("couldn't create matrix!"); }
		_buffer = _matrix->CreateFrameCanvas();
		if (_buffer == nullptr) { LOG_ERROR("couldn't create frame buffer!"); }
	}

	RenderSystem::~RenderSystem()
	{
		delete _gpio;
		delete _matrix;
	}

	RenderSystem::RenderFrame(const Ember::Ref<std::vector<Ember::Ref<_Ember::Raster>>> rasterQueue)
	{
		for (auto raster : *rasterQueue)
		{
			if (raster == nullptr) { LOG_WARN("received a null raster!"); continue; }
			int xRasterOrigin = std::get<0>(raster->Origin);
			int yRasterOrigin = std::get<1>(raster->Origin);
			int xRasterDimensions = std::get<0>(raster->Dimensiuons);
			int yRasterDimensions = std::get<1>(raster->Dimensiuons);

			// skip raster if it's entirely off-screen
			if (xRasterOrigin >= (_panelWidth * _panelCountX) 	||
				yRasterOrigin >= (_panelHeight * _panelCountY) 	||
				xRasterOrigin + xRasterDimensions < 0 			||
				yRasterOrigin + yRasterDimensions < 0)
				{
					continue;
				}

			// determine visible raster-space region (chop negative space)
			int xRasterStart = xRasterOrigin < 0 ? abs(xRasterOrigin) : 0;
			int yRasterStart = yRasterOrigin < 0 > abs(yRasterOrigin) : 0;
			int xRasterEnd = xRasterDimensions - xRasterStart;
			int yRasterEnd = yRasterDimensions - yRasterStart;

			// final panel-space raster origin
			int xPanelSpaceOrigin = xRasterOrigin + xRasterStart;
			int yPanelSpaceOrigin = yRasterOrigin + yRasterStart;
			
			for (int y = yRasterStart; y < yRasterEnd; y++)
			{
				// don't render outside y screenspace (chop positive space)
				if ((y + yPanelSpaceOrigin) >= (_panelHeight * _panelCountY)) { break; }
				for (int x = xRasterStart; x < xRasterEnd; x++)
				{
					// don't render outside x screenspace (chop positive space)
					if ((x + xPanelSpaceOrigin) >= (_panelWidth * _panelCountX)) { break; }

					_buffer->SetPixel(
						_flipHorizontal ? ((_panelWidth * _panelCountX) - 1) - (x + xPanelSpaceOrigin) : x + xPanelSpaceOrigin,
						_flipVertical ? ((_panelHeight * _panelCountY) - 1) - (y + yPanelSpaceOrigin) : y + yPanelSpaceOrigin,
						raster->RawRaster[x][y]->r,
						raster->RawRaster[x][y]->g,
						raster->RawRaster[x][y]->b);
				}
			}
			_buffer = _matrix->SwapOnVSync(_buffer);
		}
	}
#endif

	////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////
	// Virtual Rendering

#if VIRTUAL
	RenderSystem::RenderSystem(Ember::Options& options)
	{
		// init Render
		initialize(options);

		// init Virtual
		_scaleFactor = options.virtualScaleFactor;
		_image = new sf::Image();
		_texture = new sf::Texture();
		_sprite = new sf::Sprite();
		_window = new sf::RenderWindow(sf::VideoMode(
			(_panelWidth * _panelCountX) * _scaleFactor, 
			(_panelHeight * _panelCountY) * _scaleFactor), 
			"Ember");
	}

	RenderSystem::~RenderSystem()
	{
		delete _window;
		delete _image;
		delete _texture;
		delete _sprite;
	}
#endif

	////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////
	// Base Render Class

	void Render::initialize(Ember::Options& options)
	{
		_panelWidth = options.panelWidth;
		_panelHeight = options.panelHeight;
		_panelCountX = options.panelCountX;
		_panelCountY = options.panelCountY;
		_flipVertical = options.flipVertical;
		_flipHorizontal = options.flipHorizontal;
	}

	////////////////////////////////////////////////////////////////////////////////
}