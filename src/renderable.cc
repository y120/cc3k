#include "renderable.h"

using namespace std;

Renderable::Renderable()
	: name("Unknown"), sprite("?"), pos(0, 0)
{}

Renderable::Renderable(string spr, int row, int col)
	: name(spr), sprite(spr), pos(row, col)
{}

Renderable::~Renderable() {}

string Renderable::getName() const {
	return name;
}

string Renderable::getSprite() const {
	return sprite;
}

Point Renderable::getPosition() const {
	return pos;
}

void Renderable::setName(const string &nam) {
	name = nam;
}

void Renderable::setSprite(const string &spr) {
	sprite = spr;
}

void Renderable::move(const Point &pt) {
	pos = pt;
}

void Renderable::move(int row, int col) {
	pos.r = row;
	pos.c = col;
}