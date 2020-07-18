#ifndef ROCKH
#define ROCKH

#include "image.h"
#define MIN(a,b) (a)<(b)?(a):(b)
#define MAX(a,b) (a)>(b)?(a):(b)
class Rock
{
	typedef struct sVec2d
	{
		float x;
		float y;
	}Vec2d;

	Vec2d _position;
	unsigned int _size;
	float _speed;

public:
	Rock(float i);
	~Rock() {};

	Image getSprite() { return *Image::Get("data/rock.tga"); }
	int getX() { return round(_position.x); }
	int getY() { return round(_position.y); }
	int getSize() { return _size; }
	void moveDown(double seconds_elapsed) { _position.y = _position.y + _speed*seconds_elapsed; };

};

#endif