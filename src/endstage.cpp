#include "endstage.h"
#include "input.h"

void EndStage::update(double seconds_elapsed)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
		Game::instance->current_stage = new GameStage(); //start new game
	if (Input::wasKeyPressed(SDL_SCANCODE_X)) //if key X was pressed
		Game::instance->must_exit = true; //exit game
};

void EndStage::render()
{
	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	Image framebuffer(128, 128); //do not change framebuffer size

	framebuffer.drawImage(*screen, 0, 0);
	framebuffer.drawText("Your score: " + std::to_string(_score), 32, 95, *minifont, 4, 6);
	framebuffer.drawText("Highscore: " + std::to_string(Game::instance->highscore), 32, 102, *minifont, 4, 6);
	framebuffer.drawText("Press Z to restart", 26, 112, *minifont, 4, 6);
	framebuffer.drawText("Press X to quit", 32, 119, *minifont, 4, 6);

	//send image to screen
	Game::instance->showFramebuffer(&framebuffer);
};