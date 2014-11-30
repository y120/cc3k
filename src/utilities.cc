#include "utilities.h"
#include <algorithm>
#include <cmath>
#include <iostream>

int Utilities::distance(int r, int c, int r2, int c2) {
std::cerr << "dist-calc: " << r << " " << c << " " << r2 << " " << c2 << '\n';
	return std::max(abs(r - r2), abs(c - c2));
}

int Utilities::taxicabDistance(int r, int c, int r2, int c2) {
	return abs(r - r2) + abs(c - c2);
}
