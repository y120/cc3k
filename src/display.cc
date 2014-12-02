#include <iostream>
#include <algorithm>
#include "display.h"
#include "renderable.h"
#include "game.h"			// for DLC support

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
	for (int l0 = 0; l0 < row; l0++) {
		screenBuffer[l0].resize(col);
		for (int l1 = 0; l1 < col; l1++) {
			screenBuffer[l0][l1] = " ";
		}
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
	string sprite = ado->getSprite();
	if (Game::getInstance()->hasDLC(DLC::Colour)) {
		sprite = string("\033[") + ado->getColour() + "m" + sprite +
				 "\033[97m";	// reset to white
	}
	drawChar(sprite, ado->getR(), ado->getC());
}

void Display::draw(const string &sprite, int row, int col) {
	for (int l0 = 0; l0 < int(sprite.length()); l0++) {
		screenBuffer[row % rSize][(l0 + col) % cSize] = string("") + sprite[l0];
	}
}

void Display::drawChar(const string &sprite, int row, int col) {
	screenBuffer[row][col] = sprite;
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
	vector<string> buffer(rSize, "");
	for (int l0 = 0; l0 < rSize; l0++) {
		for (int l1 = 0; l1 < cSize; l1++) {
			buffer[l0].append(screenBuffer[l0][l1]);
		}
	}
	for (int l0 = 0; l0 < rSize; l0++) {
		*out << buffer[l0] << endl;
	}
	// reset screenbuffer
	resize(rSize, cSize);
}