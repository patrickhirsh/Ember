#include "Render.h"

namespace _Ember
{
#if !VIRTUAL
	HardwareRender::HardwareRender(Ember::Options& options)
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
		_buffer = _matrix->CreateFrameCanvas();
	}

	HardwareRender::~HardwareRender()
	{
		delete _gpio;
		delete _matrix;
	}
#endif

#if VIRTUAL
	VirtualRender::VirtualRender(Ember::Options& options)
	{
		// init Render
		initialize(options);

		// init VirtualRender
		_scaleFactor = options.virtualScaleFactor;
		_image = new sf::Image();
		_texture = new sf::Texture();
		_sprite = new sf::Sprite();
		_window = new sf::RenderWindow(sf::VideoMode(
			(_panelWidth * _panelCountX) * _scaleFactor, 
			(_panelHeight * _panelCountY) * _scaleFactor), 
			"Ember");
	}

	VirtualRender::~VirtualRender()
	{
		delete _window;
		delete _image;
		delete _texture;
		delete _sprite;
	}
#endif

	void Render::initialize(Ember::Options& options)
	{
		_panelWidth = options.panelWidth;
		_panelHeight = options.panelHeight;
		_panelCountX = options.panelCountX;
		_panelCountY = options.panelCountY;
		_flipVertical = options.flipVertical;
		_flipHorizontal = options.flipHorizontal;
	}
}