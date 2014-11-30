#include "merchant.h"
#include "game.h"
#include "player.h"
#include "goldPile.h"
#include "turnSummary.h"
#include "tile.h"
#include <sstream>

bool Merchant::hostile = false;

namespace {
	void setMerchantSprite(Renderable *obj) {
		obj->setSprite("M");
	}
}

Merchant::Merchant() : AbstractEnemy(30, 70, 5) {
	setMerchantSprite(this);
}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void Merchant::getHitBy(Player *p) {
	Character::getHitBy(static_cast<Character*>(p));
	this->setHostile(true);
}

/**
 *	Dispatch function as part of the Visitor pattern.
 */
void Merchant::strike(Player *p) {
	p->getHitBy(this);
}

/**
 *	Sets Merchant hostility. When non-hostile, Merchants always act as though
 *	the Player is out of range.
 */
void Merchant::setHostile(bool hostile) {
	Merchant::hostile = hostile;
}

/**
 *	Returns whether the Merchants are hostile.
 */
bool Merchant::isHostile() {
	return Merchant::hostile;
}

/**
 *	Applies the AI.
 *
 *	By default, this means we check if we can hit the Player. If so, we attack
 *	them. Otherwise, we move randomly.
 */
void Merchant::doTurn() {
	if (this->isHostile() && this->canHitPlayer()) {
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
 *	Merchants drop a MerchantHoard on death.
 */
void Merchant::die() {
	Tile *tile = this->getTile();
	GoldPile::GoldPileSize gps = GoldPile::MerchantHoard;

	if (Game::getInstance()->hasDLC(DLC::Inventory)) {
		// With the Inventory DLC active, physically drop the GoldPile.
		GoldPile *goldPile = new GoldPile(gps);
		tile->setContents(goldPile);
	} else {
		// Without the Inventory DLC, add the gold directly.
		int gold = static_cast<int>(gps);
		Game::getInstance()->getPlayer()->addGold(gold);

		// Also log it...
		std::ostringstream oss;
		oss << "Player picked up " << gold << " gold!";
		TurnSummary::add(oss.str());

		// ... and clear the Tile.
		tile->setContents(NULL);
	}

	// Go up to the super.
	Character::die();
}
