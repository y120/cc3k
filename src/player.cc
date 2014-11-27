#include "player.h"
#include "game.h"
#include "dlc.h"
#include "inventory.h"
#include "floor.h"
#include "tile.h"

// Protected constructor, does nothing.
Player::Player() {}

/**
 *	Constructs a Player. All Players have a base 50% dodge stat. Optionally
 *	creates the inventory.
 */
Player::Player(int hp, int atk, int def) : Character(hp, atk, def, 50), score(0),
	gold(0) {
	if (Game::getInstance()->hasDLC(DLC::Inventory)) {
		this->inventory = new Inventory();
	}
}

/**
 *	Destructor: free the inventory (if any).
 */
Player::~Player() {
	delete inventory;
}

int Player::getScore() const {
	return this->score;
}

int Player::getGold() const {
	return this->gold;
}

/**
 *	Adds some gold to the Player's pockets. When positive, this should also add
 *	to score. Gold can never go below 0.
 */
void Player::addGold(int d) {
	this->gold = std::max(0, this->getGold() + d);
	if (d > 0) {
		this->addScore(d);
	}
}

void Player::addScore(int d) {
	this->score += d;
}

Inventory* Player::getInventory() const {
	return this->inventory;
}

bool Player::canMove(int dr, int dc) const {
	return this->canMoveTo(this->getR() + dr, this->getC() + dc);
}

bool Player::canMoveTo(int r, int c) const {
	return this->canMoveTo(Game::getInstance()->getFloor()->getTile(r, c));
}

bool Player::canMoveTo(Tile *tile) const {
	return tile->isPassableByPlayer();
}

// See explanation in abstractEnemy.h
void Player::getHitBy(Human* e) {
	this->getHitBy(reinterpret_cast<AbstractEnemy*>(e));
}
void Player::getHitBy(Dwarf* e) {
	this->getHitBy(reinterpret_cast<AbstractEnemy*>(e));
}
void Player::getHitBy(Elf* e) {
	this->getHitBy(reinterpret_cast<AbstractEnemy*>(e));
}
void Player::getHitBy(Orc* e) {
	this->getHitBy(reinterpret_cast<AbstractEnemy*>(e));
}
void Player::getHitBy(Merchant* e) {
	this->getHitBy(reinterpret_cast<AbstractEnemy*>(e));
}
void Player::getHitBy(Dragon* e) {
	this->getHitBy(reinterpret_cast<AbstractEnemy*>(e));
}

void Player::die() {
	// TODO
}

Player* Player::tickEffects() {
	return this;
}

std::string Player::render() {
	return "@";
}
