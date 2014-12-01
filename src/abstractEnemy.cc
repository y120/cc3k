#include "abstractEnemy.h"

#include "game.h"
#include "player.h"
#include "floor.h"
#include "tile.h"
#include "goldPile.h"
#include "display.h"
#include "utilities.h"
#include <sstream>

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
 *	By default, on death, enemies drop a gold pile. This is either Normal or
 *	Small (equally likely).
 */
void AbstractEnemy::die() {
	Tile *tile = this->getTile();
	GoldPile::GoldPileSize gps = Game::getInstance()->rand(2)
		? GoldPile::SmallPile
		: GoldPile::NormalPile;

	if (Game::getInstance()->hasDLC(DLC::Inventory)) {
		// With the Inventory DLC active, physically drop the GoldPile.
		GoldPile *goldPile = new GoldPile(gps);
		tile->setContents(goldPile);
		// Go up to the super.
		Character::die();
	} else {
		// Without the Inventory DLC, add the gold directly.
		int gold = static_cast<int>(gps);
		Game::getInstance()->getPlayer()->addGold(gold);

		// Go up to the super.
		Character::die();

		// Also log it...
		std::ostringstream oss;
		oss << Game::getInstance()->getPlayer()->getName() << "picks up " <<
			gold << " gold!";
		Display::getInstance()->addMessage(oss.str());

		// ... and clear the Tile.
		tile->setContents(NULL);
	}

	// Note: we don't need to delete this, because a reference is kept in
	// Floor::enemies, and that will get deleted eventually.
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
//std::cerr << "Checking if we can hit: we're at " << getR() << " " << getC() << ", player at " << Game::getInstance()->getPlayer()->getR() << " " << Game::getInstance()->getPlayer()->getC() << '\n';
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
	return tile && tile->isPassableByEnemy();
}
