#include "introstage.h"
#include "gamestage.h"
#include "input.h"

#define COVER 0
#define STORY 1
#define CONTROLS 2

IntroStage::IntroStage()
{
	for (int i = 0; i < OPENSCREENS; i++)
		screens[i] = Image::Get("data/opening" + std::to_string(i) + ".tga");
};

void IntroStage::update(double seconds_elapsed)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
		screenID++;
	if (!(screenID - OPENSCREENS))
	{
		SDL_PauseAudio(0);
		Game::instance->synth.playSample("data/river.wav");
		Game::instance->current_stage = new GameStage();
	}
};

void IntroStage::render()
{
	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	Image framebuffer(128, 128); //do not change framebuffer size

	framebuffer.drawImage(*screens[screenID], 0, 0);

	switch (screenID)
	{
	case COVER:
	case STORY:
		framebuffer.drawText("Press Z to continue", 25, 105, *minifont, 4, 6);
		break;
	case CONTROLS:
		framebuffer.drawText("Press Z to start", 32, 109, *minifont, 4, 6);
		break;
	}

	//send image to screen
	Game::instance->showFramebuffer(&framebuffer);
};