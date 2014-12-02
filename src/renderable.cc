#include "renderable.h"
#include "display.h"

using namespace std;

Renderable::Renderable()
	: name("Unknown"), sprite("?"), colour(ColourType::WHITE),
		r(0), c(0)
{}

Renderable::Renderable(int row, int col)
	: name("Unknown"), sprite("?"), colour(ColourType::WHITE),
		r(row), c(col)
{}

Renderable::Renderable(string spr, int row, int col)
	: name(spr), sprite(spr), colour(ColourType::WHITE), r(row), c(col)
{}

Renderable::~Renderable() {}

string Renderable::getName() const {
	return name;
}

string Renderable::getSprite() const {
	return sprite;
}

string Renderable::getColour() const {
	string s = "";
	s = s + char('0' + (int(colour) / 10));
	s = s + char('0' + (int(colour) % 10));
	return s;
}

int Renderable::getR() const {
	return r;
}

int Renderable::getC() const {
	return c;
}

void Renderable::setName(const string &nam) {
	name = nam;
}

void Renderable::setSprite(const string &spr) {
	sprite = spr;
}

void Renderable::setColour(ColourType setc) {
	colour = setc;
}

void Renderable::moveSprite(int row, int col) {
	r = row;
	c = col;
}

// Renders the object to the Display
void Renderable::render() {
	Display::getInstance()->draw(this);
}