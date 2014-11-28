#include <iostream>
#include "display.h"
#include "renderable.h"
#include "point.h"

using namespace std;

Display::Display()
	: out(&cout)
{
	resize(30, 79);
}

Display *Display::getInstance() {
	static Display singleton;
	return &singleton;
}

void Display::setSource(std::ostream *os) {
	out = os;
}

void Display::resize(int row, int col) {
	screenBuffer.resize(row);
	string reset = "";
	for (int l0 = 0; l0 < col; l0++) {
		reset = reset + ' ';
	}
	for (int l0 = 0; l0 < row; l0++) {
		//screenBuffer[l0].resize(col);
		screenBuffer[l0] = reset;
	}
	size.r = row;
	size.c = col;
}

void Display::draw(const Renderable *ado) {
	draw(ado->getSprite(), ado->getPosition().r, ado->getPosition().c);
}

void Display::draw(const string &sprite, int row, int col) {
	screenBuffer[row % size.r].replace(
		col % size.c, sprite.length(), sprite
	);
}

void Display::render() const {
	for (int l0 = 0; l0 < size.r; l0++) {
		*out << screenBuffer[l0] << endl;
	}
}