#include "abstractPlayerEffect.h"

AbstractPlayerEffect::AbstractPlayerEffect(Player *base) : base(base) {}

AbstractPlayerEffect::~AbstractPlayerEffect() {
	delete this->base;
}

/**
 *	As stated in the header: by default, all getStat() functions just pipe the
 *	request through to the base.
 */
int AbstractPlayerEffect::getMaxHP() const {
	return base->getMaxHP();
}
int AbstractPlayerEffect::getAtk() const {
	return base->getAtk();
}
int AbstractPlayerEffect::getDef() const {
	return base->getDef();
}
int AbstractPlayerEffect::getDodge() const {
	return base->getDodge();
}
std::string AbstractPlayerEffect::getRace() const {
	return "AbstractPlayerEffect";
}

/**
 *	Applies a tick of the effect.
 *
 *	By default, this will not do anything special.
 *	If the effect is expired, then we mark this effect for deletion and return
 *	the cleaned up (ticked) base.
 */
Player* AbstractPlayerEffect::tickEffects() {
	// First lean up the base. Effects added later tick later.
	this->base = base->tickEffects();

	// Now if this is expired, set base to null and return base.
	if (this->isExpired()) {
		Player *temp = this->base;
		this->base = NULL;
		delete this;
		return temp;
	}
	// Otherwise, just return this.
	return this;
}

// BELOW HERE: All functions just pipe through to the base.

int AbstractPlayerEffect::getHP() const {
	return base->getHP();
}
int AbstractPlayerEffect::getR() const {
	return base->getR();
}
int AbstractPlayerEffect::getC() const {
	return base->getC();
}
Tile *AbstractPlayerEffect::getTile() const {
	return base->getTile();
}
int AbstractPlayerEffect::getFloor() const {
	return base->getFloor();
}
void AbstractPlayerEffect::setFloor(int f) {
	base->setFloor(f);
}
void AbstractPlayerEffect::move(int dr, int dc) {
	base->move(dr, dc);
}
void AbstractPlayerEffect::moveTo(int r, int c) {
	base->moveTo(r, c);
}
void AbstractPlayerEffect::moveTo(Tile* tile) {
	base->moveTo(tile);
}
void AbstractPlayerEffect::setMaxHP(int i) {
	base->setMaxHP(i);
}
void AbstractPlayerEffect::setHP(int i) {
	base->setHP(i);
}
void AbstractPlayerEffect::setAtk(int i) {
	base->setAtk(i);
}
void AbstractPlayerEffect::setDef(int i) {
	base->setDef(i);
}
void AbstractPlayerEffect::setDodge(int i) {
	base->setDodge(i);
}
void AbstractPlayerEffect::addMaxHP(int i) {
	base->addMaxHP(i);
}
void AbstractPlayerEffect::addHP(int i) {
	base->addHP(i);
}
void AbstractPlayerEffect::addAtk(int i) {
	base->addAtk(i);
}
void AbstractPlayerEffect::addDef(int i) {
	base->addDef(i);
}
void AbstractPlayerEffect::addDodge(int i) {
	base->addDodge(i);
}
bool AbstractPlayerEffect::isDead() const {
	return base->isDead();
}
void AbstractPlayerEffect::die() {
	base->die();
}
bool AbstractPlayerEffect::wasHit() const {
	return base->wasHit();
}
int AbstractPlayerEffect::getScore() const {
	return base->getScore();
}
int AbstractPlayerEffect::getGold() const {
	return base->getGold();
}
void AbstractPlayerEffect::addGold(int g) {
	base->addGold(g);
}
Inventory* AbstractPlayerEffect::getInventory() const {
	return base->getInventory();
}
bool AbstractPlayerEffect::canMove(int dr, int dc) const {
	return base->canMove(dr, dc);
}
bool AbstractPlayerEffect::canMoveTo(int r, int c) const {
	return base->canMoveTo(r, c);
}
bool AbstractPlayerEffect::canMoveTo(Tile *tile) const {
	return base->canMoveTo(tile);
}
void AbstractPlayerEffect::getHitBy(AbstractEnemy *e) {
	base->getHitBy(e);
}
void AbstractPlayerEffect::getHitBy(Human *e) {
	base->getHitBy(e);
}
void AbstractPlayerEffect::getHitBy(Dwarf *e) {
	base->getHitBy(e);
}
void AbstractPlayerEffect::getHitBy(Elf *e) {
	base->getHitBy(e);
}
void AbstractPlayerEffect::getHitBy(Orc *e) {
	base->getHitBy(e);
}
void AbstractPlayerEffect::getHitBy(Merchant *e) {
	base->getHitBy(e);
}
void AbstractPlayerEffect::getHitBy(Dragon *e) {
	base->getHitBy(e);
}
void AbstractPlayerEffect::strike(AbstractEnemy *e) {
	base->strike(e);
}
void AbstractPlayerEffect::addScore(int s) {
	base->addScore(s);
}
