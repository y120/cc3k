#include "dragon.h"

#include "game.h"
#include "player.h"
#include "tile.h"
#include "utilities.h"
#include <cmath>

namespace {
	void setDragonSprite(Renderable *obj) {
		obj->setSprite("D");
	}
}

//Dragon::Dragon() : AbstractEnemy(150, 20, 20), hoard(NULL) {
//	setDragonSprite(this);
//}

/**
 *	On initialisation, set the hoard that the Dragon guards.
 */
Dragon::Dragon(Tile *hoard) : AbstractEnemy(150, 20, 20), hoard(hoard) {
	setDragonSprite(this);
}
/*
 *	Note that we don't use a destructor because the Dragon does not own the
 *	Tile, it just knows about it.
 */

//Dragon::setHoard(DragonHoard *hd) {
//	hoard = hd;
//}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void Dragon::getHitBy(Player *p) {
	Character::getHitBy(static_cast<Character*>(p));
}

/**
 *	Dispatch function as part of the Visitor pattern.
 */
void Dragon::strike(Player *p) {
	p->getHitBy(this);
}

/**
 *	Dragons have a special kind of turn. Unlike regular enemies, they always
 *	stay in the same spot. Thus, only if they can hit a player will they do
 *	anything.
 */
void Dragon::doTurn() {
	if (this->canHitPlayer()) {
		this->strike(Game::getInstance()->getPlayer());
	} 
}

/**
 *	Dragons can hit the Player if they're within 1 tile of themselves or their
 *	treasure hoard.
 */
bool Dragon::canHitPlayer() const {
	// distance to me
	int distance = std::min(
		// distance to me
		Utilities::distance(this->getR(), this->getC(),
				Game::getInstance()->getPlayer()->getR(), Game::getInstance()->getPlayer()->getC()),
		// distance to my hoard
		Utilities::distance(this->hoard->getR(), this->hoard->getC(),
				Game::getInstance()->getPlayer()->getR(), Game::getInstance()->getPlayer()->getC())
	);
	return distance <= 1;
}
