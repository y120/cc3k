#include "orc.h"
#include "player.h"

namespace {
	void setOrcSprite(Renderable *obj) {
		obj->setName("O");
		obj->setSprite("O");
	}
}

// Orc racial ability (deal 50% more dmg to goblins) is implemented in Goblin.

Orc::Orc() : AbstractEnemy(180, 30, 25) {
	setOrcSprite(this);
}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void Orc::getHitBy(Player *p) {
	Character::getHitBy(static_cast<Character*>(p));
}

/**
 *	Dispatch function as part of the Visitor pattern.
 */
void Orc::strike(Player *p) {
	p->getHitBy(this);
}