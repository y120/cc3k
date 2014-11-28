#include "point.h"

using namespace std;

Point::Point()
	: r(0), c(0)
{}

Point::Point(int row, int col)
	: r(row), c(col)
{}

istream &operator>>(istream &in, Point &p) {
	in >> p.r >> p.c;
	return in;
}