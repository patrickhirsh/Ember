#pragma once
#include "EmberPCH.h"

#if VIRTUAL
#include <SFML/Graphics.hpp>
#endif

namespace _Ember
{
	class Render
	{
	public:
		virtual ~Render					() { };
		virtual void DisplayFrame		() = 0;
	protected:
		void initialize					(Ember::Options& options);
		int 							_panelWidth;
		int								_panelHeight;
		int								_panelCountX;
		int								_panelCountY;
		bool							_flipVertical;
		bool							_flipHorizontal;
	};

#if !VIRTUAL
	class HardwareRender : public Render
	{
	public:
		HardwareRender					(Ember::Options& options);
		~HardwareRender					();
		void DisplayFrame				() { };
	private:
		rgb_matrix::GPIO*				_gpio;
		rgb_matrix::RGBMatrix*			_matrix;
		rgb_matrix::FrameCanvas*		_buffer;
	};
#endif

#if VIRTUAL

#define VIRTUAL_BUFFER_SIZE

	class VirtualRender : public Render
	{
	public:
		VirtualRender					(Ember::Options& options);
		~VirtualRender					();
		void DisplayFrame				() { };
	private:
		sf::RenderWindow*               _window;
    	sf::Image*                      _image;
    	sf::Texture*                    _texture;
    	sf::Sprite*                     _sprite;
		// buffer
		float 							_scaleFactor;
	};
#endif
}