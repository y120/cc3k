#include "dwarf.h"
#include "player.h"

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
 *	Dispatch function as part of the Visitor pattern.
 */
void Dwarf::strike(Player *p) {
	p->getHitBy(this);
}
