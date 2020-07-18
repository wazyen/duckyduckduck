#ifndef STAGEH
#define STAGEH

#include "game.h"

class Stage
{
public:
	Stage() {};
	~Stage() {};

	virtual void update(double seconds_elapsed) = 0;
	virtual void render() = 0;
};

#endif STAGEH