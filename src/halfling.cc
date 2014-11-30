#include "halfling.h"
#include "player.h"

namespace {
	void setHalflingSprite(Renderable *obj) {
		obj->setSprite("L");
	}
}

/**
 *	Halfling racial ability: 50% chance to dodge.
 */
Halfling::Halfling() : AbstractEnemy(100, 15, 20) {
	this->setDodge(50);
	setHalflingSprite(this);
}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void Halfling::getHitBy(Player *p) {
	Character::getHitBy(static_cast<Character*>(p));
}

/**
 *	Dispatch function as part of the Visitor pattern.
 */
void Halfling::strike(Player *p) {
	p->getHitBy(this);
}
