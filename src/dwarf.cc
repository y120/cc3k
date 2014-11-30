#include "dwarf.h"
#include "player.h"
#include "vampire.h"

namespace {
	void setDwarfSprite(Renderable *obj) {
		obj->setName("W");
		obj->setSprite("W");
	}
}

Dwarf::Dwarf() : AbstractEnemy(100, 20, 30) {
	setDwarfSprite(this);
}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void Dwarf::getHitBy(Player* p) {
	Character::getHitBy(static_cast<Character*>(p));
}

/**
 *	Vampires are special: since Vampires are allergic to Dwarves, we negate the
 *	Vampire's 5 health gain and replace with a 5 health loss in the onHit.
 */
void Dwarf::getHitBy(Vampire *v) {
	// First, process the hit as usual.
	this->getHitBy(static_cast<Player*>(v));

	// Then, if we were hit, drain 10 HP to change the +5 to a -5.
	if (this->wasHit()) {
		v->addHP(-10);
	}
}

/**
 *	Dispatch function as part of the Visitor pattern.
 */
void Dwarf::strike(Player *p) {
	p->getHitBy(this);
}
