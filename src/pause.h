#ifndef PAUSESTAGEH
#define PAUSESTAGEH

#include "endstage.h"

class Pause : public Stage
{
	Image _framebuffer;
	Image* _font = Image::Get("data/bitmap-font-white.tga");
public:
	Pause(Image framebuffer) : _framebuffer(framebuffer) { _framebuffer.drawText("PAUSED", 86, 0, *_font); };
	~Pause() {};

	void update(double seconds_elapsed);
	void render();
};

#endif