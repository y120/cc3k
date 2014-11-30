#include <iostream>
#include "display.h"
#include "renderable.h"

using namespace std;

Display::Display()
	: out(&cout), message("")
{
	resize(30, 79);
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
	if (message.length() > 0) {
		message = message + " ";
	}
	message = message + msg;
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
	draw("Action: " + message, 29, 0);
}

void Display::render() {
	for (int l0 = 0; l0 < rSize; l0++) {
		*out << screenBuffer[l0] << endl;
	}
	messageHistory.push_back(message);
	message = "";
}