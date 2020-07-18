#include "pause.h"
#include "input.h"

void Pause::update(double seconds_elapsed)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_P)) //if key Esc was pressed
	{
		SDL_PauseAudio(0);
		Game::instance->pause_stage = Game::instance->current_stage;
		Game::instance->current_stage = Game::instance->game_stage;
	}
};

void Pause::render()
{
	//send image to screen
	Game::instance->showFramebuffer(&_framebuffer);
};