#include "point.h"

bool point::operator==(const point& other) const
{
	return x == other.x and y == other.y;
}
