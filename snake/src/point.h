#pragma once

struct point
{
	int x;
	int y;

	bool operator==(const point& other) const;
};