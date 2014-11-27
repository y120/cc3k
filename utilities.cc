#include "utilities.h"
#include <algorithm>
#include <cmath>

int Utilities::distance(int r, int c, int r2, int c2) {
	return std::max(abs(r - r2), (c - c2));
}

int Utilities::taxicabDistance(int r, int c, int r2, int c2) {
	return abs(r - r2) + abs(c - c2);
}
