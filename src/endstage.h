#ifndef ENDSTAGEH
#define ENDSTAGEH

#include "gamestage.h"
#include "game.h"

class EndStage : public Stage
{
	unsigned int _savedDucks;
	unsigned int _score;
	Image* minifont = Image::Get("data/mini-font-white-4x6.tga");
	Image* screen;
public:
	EndStage(unsigned int savedDucks, unsigned int score) : _savedDucks(savedDucks), _score(score)
	{
		Game::instance->highscore = MAX(Game::instance->highscore, score);
		screen = Image::Get("data/end" + std::to_string(_savedDucks) + ".tga");
	};
	~EndStage() {};

	void update(double seconds_elapsed);
	void render();
};

#endif