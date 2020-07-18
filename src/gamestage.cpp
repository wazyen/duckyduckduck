#include "gamestage.h"
#include "utils.h"
#include "input.h"
#include "pause.h"

GameStage::GameStage()
{
	int i = 5;
	while (i--)
	{
		if (i < 4)
		{
			Duck* duck = new Duck(i + 1);
			ducks.push(duck);
			if (i == 0)
				mumDuck = duck;
		}
	}
};

GameStage::~GameStage()
{
	while (!ducks.empty())
	{
		Duck* duck = ducks.front();
		ducks.pop();
		delete duck;
	}
	while (!rocks.empty())
	{
		Rock* rock = rocks.front();
		rocks.pop();
		delete rock;
	}

};

void GameStage::update(double seconds_elapsed)
{
	if(ducksAlive==1 || score == 1000)
		Game::instance->current_stage = new EndStage(ducksAlive-1, score);

	//Read the keyboard state, to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
		mumDuck->moveUp(seconds_elapsed);
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
		mumDuck->moveDown(seconds_elapsed);
	if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) //if key left
		mumDuck->moveLeft(seconds_elapsed);
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key right
		mumDuck->moveRight(seconds_elapsed);

	if (Input::wasKeyPressed(SDL_SCANCODE_C)) //if key C was pressed
		nUpdates = 9900;
	if (Input::wasKeyPressed(SDL_SCANCODE_S)) //if key S was pressed
	{
		started = true;
		nUpdates = 0;
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_P)) //if key P was pressed
	{
		SDL_PauseAudio(-1);
		Game::instance->game_stage = Game::instance->current_stage;
		if (Game::instance->pause_stage != NULL)
			delete Game::instance->pause_stage;
		Game::instance->current_stage = new Pause(framebuffer);
	}

	std::stack<Duck*> duckStack;
	int i = ducksAlive;
	while (i--)
	{
		Duck* duck = ducks.front();
		ducks.pop();
		ducks.push(duck);
		duckStack.push(duck);
	}
	i = ducksAlive;
	float x = 0.0, y = 0.0;
	while (i--)
	{
		Duck* duck = duckStack.top();
		duckStack.pop();
		if (nUpdates % 15 == 0)
			duck->setRandDisplacement(rand() % 3 - 1, rand() % 3 - 1);
		if (i < ducksAlive - 1) //if little duck
		{
			duck->setX((duck->getOldX() + x) / 2.0); //we interpolate the ducky's position with the one of the duck in front of him
			duck->setY(y);
			x = 0.0;
		}
		else //if mum duck
			x = 5.0;
		y = duck->getOldY() + duck->getSize() + 1;
		x += duck->getOldX();
	}

	nUpdates++;

	if (!started)
		return;

	score = nUpdates / 10;

	i = rocks.size();
	while (i--)
	{
		bool del = false;
		Rock* rock = rocks.front();
		rocks.pop();
		rock->moveDown(seconds_elapsed);
		int y = rock->getY();
		if (y > 50) //From this y position on, the rock can collide with ducks
		{
			int j = ducksAlive;
			std::queue<Duck*> duckCheck = ducks;
			while (j--)
			{
				Duck* duck = duckCheck.front();
				duckCheck.pop();
				if (rock->getY() + rock->getSize() >= duck->getY() &&
					rock->getY() <= duck->getY() + duck->getSize() &&
					rock->getX() + rock->getSize() >= duck->getX() &&
					rock->getX() <= duck->getX() + duck->getSize() )
				{
					ducks.pop();
					ducksAlive--;
					del = true;
					Game::instance->synth.playSample("data/quack.wav", 1);
					continue;
				}
			}
		}
		if (y < 128 && del == false)
			rocks.push(rock);
		else
			delete rock;
	}
	if (nUpdates % 60 == 30)
		rocks.push(new Rock(rand()%108));
};

void GameStage::render()
{
	framebuffer.drawImage(*Image::Get("data/river" + std::to_string((nUpdates / 10) % 5) + ".tga"), 0, 0); //paint river background


	int i = ducksAlive;
	while (i--)
	{
		Duck* duck = ducks.front();
		ducks.pop();
		ducks.push(duck);
		framebuffer.drawImage(duck->getSprite(), duck->getX(), duck->getY());

	}
	i = rocks.size();
	while (i--)
	{
		Rock* rock = rocks.front();
		rocks.pop();
		rocks.push(rock);
		framebuffer.drawImage(rock->getSprite(), rock->getX(), rock->getY());
	}
	framebuffer.drawText("Score: " + std::to_string(score), 0, 0, *Image::Get("data/bitmap-font-white.tga"));	//prints score

	//send image to screen
	Game::instance->showFramebuffer(&framebuffer);
};