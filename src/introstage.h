#ifndef INTROSTAGEH
#define INTROSTAGEH

#include "stage.h"

#define OPENSCREENS 3

class IntroStage : public Stage
{
	short screenID = 0;
	Image* minifont = Image::Get("data/mini-font-white-4x6.tga");
	Image* screens[OPENSCREENS];
public:
	IntroStage();
	~IntroStage() {};

	void update(double seconds_elapsed);
	void render();
};

#endif