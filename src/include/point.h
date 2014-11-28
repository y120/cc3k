#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>

struct Point {
	int r;
	int c;
	Point();
	Point(int, int);
	friend std::istream &operator>>(std::istream &, Point &);
};

#endif