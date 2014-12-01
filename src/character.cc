#include "character.h"
#include "characterImpl.h"
#include "game.h"
#include "floor.h"
#include "tile.h"
#include "display.h"
#include <cmath>
#include <sstream>

// character.cc is considered self-explanatory.

// Protected constructor, does nothing. (impl left NULL.)
Character::Character() : pImpl(NULL) {}

Character::Character(int maxhp, int atk, int def, int dodge) :
	hit(false), pImpl(new CharacterImpl()) {
	this->setMaxHP(maxhp);
	this->setHP(maxhp);
	this->setAtk(atk);
	this->setDef(def);
	this->setDodge(dodge);
	this->setFloor(0);
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
	return Renderable::getR();
}

int Character::getC() const {
	return Renderable::getC();
}

int Character::getFloor() const {
	return this->pImpl->floor;
}

void Character::setFloor(int f) {
	this->pImpl->floor = f;
}

Tile *Character::getTile() const {
	return Game::getInstance()->getFloor(this->getFloor())->getTile(this->getR(), this->getC());
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
	Display::getInstance()->addMessage(oss.str());
	this->getTile()->setContents(NULL);
	this->r = -1;
	this->c = -1;
}

/**
 *	Damage formula given in PDF:
 *	ceil(100/(100+Def) * Atk)
 */
int Character::calculateDamage(Character *other) const {
//std::cerr << "Calculating damage. My def: " << getDef() << ", atk: " << other->getAtk() << '\n';
	int atk = std::max(0, other->getAtk());
	int def = this->getDef();
	return std::ceil(100.0 / (100 + def) * atk);
}

void Character::getHitBy(Character *other) {
	std::ostringstream oss;
	// First check dodge.
	if (Game::getInstance()->rand(100) < this->getDodge()) {
		this->hit = false;

		oss << other->getName() << " misses " << this->getName() << "!";
		Display::getInstance()->addMessage(oss.str());
		return;
	}

	this->hit = true;
	int dmg = this->calculateDamage(other);
	oss << other->getName() << " hits " << this->getName() << " for " << dmg <<
		" damage! (" << std::max(0, this->getHP() - dmg) << " HP remaining.)";
	Display::getInstance()->addMessage(oss.str());
	this->addHP(-dmg);
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
	//std::cerr << "Character - move " << dr << ' ' << dc << '\n';
	this->moveTo(this->getR() + dr, this->getC() + dc);
}

void Character::moveTo(int r, int c) {
	//std::cerr << "Character - moveTo " << r << ' ' << c << '\n';
	Tile *newTile = Game::getInstance()->getFloor()->getTile(r, c);
	this->moveTo(newTile);
}

void Character::moveTo(Tile *newTile) {
	//std::cerr << "Character - moveToTile " << newTile << '\n';
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
	this->r = newTile->getR();
	this->c = newTile->getC();
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
