#ifndef GAMESTAGEH
#define GAMESTAGEH

#include "introstage.h"
#include "duck.h"
#include "rock.h"
#include <queue>
#include <stack>

class GameStage : public Stage
{
	Image framebuffer = Image(128, 128);
	std::queue<Duck*> ducks;
	std::queue<Rock*> rocks;
	Duck* mumDuck;
	unsigned int ducksAlive = 4;
	long nUpdates = 0;
	int score = 0;
	bool started = false;
public:
	GameStage();
	~GameStage();

	void update(double seconds_elapsed);
	void render();
};

#endif GAMESATGEH