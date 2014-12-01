#include <iostream>
#include <algorithm>
#include "display.h"
#include "renderable.h"

using namespace std;

Display::Display()
	: out(&cout)
{
	resize(29, 79);
}

Display *Display::getInstance() {
	static Display singleton;
	return &singleton;
}

void Display::setOutput(std::ostream *os) {
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
	rSize = row;
	cSize = col;
}

void Display::addMessage(const string &msg) {
	messageHistory.push_back(msg);
}

void Display::clearMessages() {
	messageHistory.clear();
}

void Display::draw(const Renderable *ado) {
	draw(ado->getSprite(), ado->getR(), ado->getC());
}

void Display::draw(const string &sprite, int row, int col) {
	screenBuffer[row % rSize].replace(
		col % cSize, sprite.length(), sprite
	);
}

void Display::drawMessage() {
	int start = messageHistory.size() - 3;
	if (start < 0) {
		start = 0;
	}
	for (int l0 = 0; l0 < std::min(3, int(messageHistory.size())); l0++) {
		draw("Action: " + messageHistory[start + l0], 26 + l0, 20);
	}
}

void Display::render() {
	string reset = "";
	for (int l0 = 0; l0 < cSize; l0++) {
		reset = reset + ' ';
	}
	for (int l0 = 0; l0 < rSize; l0++) {
		*out << screenBuffer[l0] << endl;
		screenBuffer[l0] = reset;
	}
}