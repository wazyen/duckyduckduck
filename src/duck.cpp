#include "duck.h"



Duck::Duck(unsigned int i)
{
	if (i == 1)
	{
		_position.x = 54.0; _position.y = 70.0; _size = 21.0;
	}
	else
	{
		_position.x = 59.0; _position.y = 68.0 + 12.0 * i; _size = 11.0;
	}
	_oldPosition.x = _position.x;
	_oldPosition.y = _position.y;
}
