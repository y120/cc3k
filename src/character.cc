#include "character.h"
#include "characterImpl.h"
#include "game.h"
#include "floor.h"
#include "tile.h"
#include "turnSummary.h"
#include <cmath>
#include <sstream>

// character.cc is considered self-explanatory.

// Protected constructor, does nothing. (impl left NULL.)
Character::Character() {}

Character::Character(int maxhp, int atk, int def, int dodge) :
	hit(false), pImpl(new CharacterImpl()) {
	this->setMaxHP(maxhp);
	this->setHP(maxhp);
	this->setAtk(atk);
	this->setDef(def);
	this->setDodge(dodge);
}

Character::~Character() {
	delete this->pImpl;
}

int Character::getMaxHP() const {
	return this->pImpl->stats.maxhp;
}

int Character::getHP() const {
	return this->pImpl->stats.hp;
}

int Character::getAtk() const {
	return this->pImpl->stats.atk;
}

int Character::getDef() const {
	return this->pImpl->stats.def;
}

int Character::getDodge() const {
	return this->pImpl->stats.dodge;
}

int Character::getR() const {
	return this->pImpl->pos.r;
}

int Character::getC() const {
	return this->pImpl->pos.c;
}

Tile *Character::getTile() const {
	return Game::getInstance()->getFloor()->getTile(this->getR(), this->getC());
}

bool Character::isDead() const {
	return this->getHP() == 0;
}

/**
 *	By default, when a Character dies, a message is printed and its position is
 *	set to -1, -1.
 */
void Character::die() {
	std::ostringstream oss;
	oss << this->getName() << " dies.";
	TurnSummary::add(oss.str());
	this->pImpl->pos.r = -1;
	this->pImpl->pos.c = -1;
}

/**
 *	Damage formula given in PDF:
 *	ceil(100/(100+Def) * Atk)
 */
int Character::calculateDamage(Character *other) const {
	return std::ceil(100 / 100 + (this->getDef()) * other->getAtk());
}

void Character::getHitBy(Character *other) {
	// First check dodge.
	if (Game::getInstance()->rand(100) < this->getDodge()) {
		this->hit = false;
		return;
	}

	this->hit = true;
	this->addHP(-this->calculateDamage(other));
}

bool Character::wasHit() const {
	return this->hit;
}

void Character::setMaxHP(int maxhp) {
	this->pImpl->stats.maxhp = maxhp;
}

// By default, we cap the HP at MaxHP and floor it at 0. We need to check for
// death, and use the appropriate handler.
void Character::setHP(int hp) {
	hp = std::max(0, std::min(hp, this->getMaxHP()));
	this->pImpl->stats.hp = hp;
	if (hp == 0) {
		this->die();
	}
}

void Character::setAtk(int atk) {
	this->pImpl->stats.atk = atk;
}

void Character::setDef(int def) {
	this->pImpl->stats.def = def;
}

void Character::setDodge(int dodge) {
	this->pImpl->stats.dodge = dodge;
}

void Character::move(int dr, int dc) {
	this->moveTo(this->getR() + dr, this->getC() + dc);
}

void Character::moveTo(int r, int c) {
	Tile *newTile = Game::getInstance()->getFloor()->getTile(r, c);
	this->moveTo(newTile);
}

void Character::moveTo(Tile *newTile) {
	// First, check the newTile is valid.
	if (newTile == NULL || newTile->isOccupied()) {
		return;
	}

	// Then, clear the old tile (if any) and set the new one.
	Tile *oldTile = this->getTile();
	if (oldTile != NULL) {
		oldTile->setContents(NULL);
	}
	newTile->setContents(this);
	this->pImpl->pos.r = newTile->getR();
	this->pImpl->pos.c = newTile->getC();
}

void Character::addMaxHP(int dMaxHP) {
	this->setMaxHP(this->getMaxHP() + dMaxHP);
}

void Character::addHP(int dHP) {
	this->setHP(this->getHP() + dHP);
}

void Character::addAtk(int dAtk) {
	this->setAtk(this->getAtk() + dAtk);
}

void Character::addDef(int dDef) {
	this->setDef(this->getDef() + dDef);
}

void Character::addDodge(int dDodge) {
	this->setDodge(this->getDodge() + dDodge);
}
