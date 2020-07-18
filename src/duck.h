#ifndef DUCKH
#define DUCKH

#include "game.h"

class Duck
{
	typedef struct sVec2d
	{
		float x;
		float y;
	}Vec2d;

	Vec2d _position;
	Vec2d _oldPosition;
	unsigned int _size;
	int _randDisplacementX;
	int _randDisplacementY;

public:
	Duck(unsigned int i);
	~Duck() {};

	Image& getSprite() { return ( _size==21 ? *Image::Get("data/mumduck.tga") : *Image::Get("data/ducky.tga") ); }
	int getX() { return round(_position.x) + _randDisplacementX; }
	int getY() { return round(_position.y) + _randDisplacementY; }
	float getOldX() { return _oldPosition.x; }
	float getOldY() { return _oldPosition.y; }
	int getSize() { return _size; }
	void setX(float x) { _oldPosition.x = _position.x; _position.x = x; }
	void setY(float y) { _oldPosition.y = _position.y; _position.y = y; }
	void setRandDisplacement(int randDisplacementX, int randDisplacementY)
	{ _randDisplacementX = randDisplacementX; _randDisplacementY = randDisplacementY; }

	void moveUp(double seconds_elapsed) { _oldPosition.y = _position.y; _position.y = MAX(_position.y - 100.0*seconds_elapsed, 54.0); };
	void moveDown(double seconds_elapsed) { _oldPosition.y = _position.y; _position.y = MIN(_position.y + 100.0*seconds_elapsed, 106.0); };
	void moveRight(double seconds_elapsed) { _oldPosition.x = _position.x; _position.x = MIN(_position.x + 100.0*seconds_elapsed, 106.0); };
	void moveLeft(double seconds_elapsed) { _oldPosition.x = _position.x; _position.x = MAX(_position.x - 100.0*seconds_elapsed, 1.0); };
	
};

#endif