#include "renderable.h"

using namespace std;

Renderable::Renderable()
	: name("Unknown"), sprite("?"), r(0), c(0)
{}

Renderable::Renderable(int row, int col)
	: name("Unknown"), sprite("?"), r(row), c(col)
{}

Renderable::Renderable(string spr, int row, int col)
	: name(spr), sprite(spr), r(row), c(col)
{}

Renderable::~Renderable() {}

string Renderable::getName() const {
	return name;
}

string Renderable::getSprite() const {
	return sprite;
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

void Renderable::move(int row, int col) {
	r = row;
	c = col;
}