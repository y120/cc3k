#include "abstractEnemy.h"
#include "utilities.h"

#include "game.h"
#include "player.h"
#include "floor.h"
#include "tile.h"
#include "goldPile.h"
#include "turnSummary.h"

// Pipe the constructor through.
AbstractEnemy::AbstractEnemy(int maxhp, int atk, int def) : Character(maxhp, atk, def, 0) {}

/*
 *	Explanation: we require each subclass to implement a default getHitBy
 *	function. Then, for each race with a racial interaction, a specific getHitBy
 *	method may be written.
 *
 *	When no such getHitBy method exists, we call the default one. This can be
 *	achieved by performing a reinterpret_cast to force calling the default. We
 *	can't use a dynamic_cast in this case because Player is an abstract class.
 *
 *	This is kind of hacky, but it works... :-)
 */
void AbstractEnemy::getHitBy(Shade *p) {
	this->getHitBy(reinterpret_cast<Player*>(p));
}
void AbstractEnemy::getHitBy(Drow *p) {
	this->getHitBy(reinterpret_cast<Player*>(p));
}
void AbstractEnemy::getHitBy(Vampire *p) {
	this->getHitBy(reinterpret_cast<Player*>(p));
}
void AbstractEnemy::getHitBy(Troll *p) {
	this->getHitBy(reinterpret_cast<Player*>(p));
}
void AbstractEnemy::getHitBy(Goblin *p) {
	this->getHitBy(reinterpret_cast<Player*>(p));
}

/**
 *	By default, on death, enemies drop a hoard. This is either Normal or Small
 *	(equally likely).
 */
void AbstractEnemy::die() {
	Tile *tile = this->getTile();
	GoldPile *goldPile;

	if (Game::getInstance()->rand(2) == 0) {
		goldPile = new GoldPile(GoldPile::SmallPile);
	} else {
		goldPile = new GoldPile(GoldPile::NormalPile);
	}
	tile->setContents(goldPile);

	// Go up to the super.
	Character::die();
	// Note: we don't need to delete this, because a reference is kept in
	// Floor::enemies, and that will get deleted eventually.
}

/**
 *	Applies a tick of the effects.
 *	By default, this means nothing for enemies.
 */
Character *AbstractEnemy::tickEffects() {
	return this;
}

/**
 *	Applies the AI.
 *
 *	By default, this means we check if we can hit the Player. If so, we attack
 *	them. Otherwise, we move randomly.
 */
void AbstractEnemy::doTurn() {
	if (this->canHitPlayer()) {
		this->strike(static_cast<Player*>(Game::getInstance()->getPlayer()));
	} else {
		// First, check if there's a position we can possibly move to.
		bool canMove = false;
		for (int dr = -1; dr <= 1; dr++) {
			for (int dc = -1; dc <= 1; dc++) {
				canMove |= this->canMove(dr, dc);
			}
		}

		if (!canMove) {
			return;
		}

		// If there is, then we make a random movement. We can do a while(true)
		// here because we've already checked to see it's possible.
		while (true) {
			int dr = Game::getInstance()->rand(-1, 1);
			int dc = Game::getInstance()->rand(-1, 1);
			if (this->canMove(dr, dc)) {
				this->move(dr, dc);
				break;
			}
		}
	}
}

/**
 *	Checks whether this enemy can hit the player. By default, enemies have a
 *	range of 1.
 */
bool AbstractEnemy::canHitPlayer() const {
	int distance = Utilities::distance(this->getR(), this->getC(),
		Game::getInstance()->getPlayer()->getR(), Game::getInstance()->getPlayer()->getC());
	return distance <= 1;
}

bool AbstractEnemy::canMove(int dr, int dc) const {
	return this->canMoveTo(this->getR() + dr, this->getC() + dc);
}

bool AbstractEnemy::canMoveTo(int r, int c) const {
	return this->canMoveTo(Game::getInstance()->getFloor()->getTile(r, c));
}

bool AbstractEnemy::canMoveTo(Tile *tile) const {
	return tile->isPassableByEnemy();
}
