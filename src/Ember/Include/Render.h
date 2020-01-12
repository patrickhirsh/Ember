#pragma once
#include "EmberPCH.h"
#include "DMDObject.h"

#if VIRTUAL
#include <SFML/Graphics.hpp>
#endif

namespace _Ember
{
	////////////////////////////////////////////////////////////////////////////////
	// Base Render Class

	class Render
	{
	public:
		virtual ~Render					() { };
		virtual void RenderFrame		() = 0;
	protected:
		void initialize					(Ember::Options& options);
		int 							_panelWidth;
		int								_panelHeight;
		int								_panelCountX;
		int								_panelCountY;
		bool							_flipVertical;
		bool							_flipHorizontal;
	};

	////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////
	// Hardware Rendering

#if !VIRTUAL
	class RenderSystem : public Render
	{
	public:
		RenderSystem					(Ember::Options& options);
		~RenderSystem					();
		void RenderFrame				() { };
	private:
		rgb_matrix::GPIO*				_gpio;
		rgb_matrix::RGBMatrix*			_matrix;
		rgb_matrix::FrameCanvas*		_buffer;
	};
#endif

	////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////
	// Virtual Rendering

#if VIRTUAL
	class RenderSystem : public Render
	{
	public:
		RenderSystem					(Ember::Options& options);
		~RenderSystem					();
		void RenderFrame				() { };
	private:
		sf::RenderWindow*               _window;
    	sf::Image*                      _image;
    	sf::Texture*                    _texture;
    	sf::Sprite*                     _sprite;
		// buffer
		float 							_scaleFactor;
	};
#endif

	////////////////////////////////////////////////////////////////////////////////
}