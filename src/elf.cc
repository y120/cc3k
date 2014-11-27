#include "elf.h"
#include "player.h"
#include "drow.h"

Elf::Elf() : AbstractEnemy(100, 20, 30) {}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void Elf::getHitBy(Player* p) {
	Character::getHitBy(static_cast<Character*>(p));
}

/**
 *	Dispatch function as part of the Visitor pattern.
 *
 *	Elven racial ability: strike all Players twice except for Drows.
 */
void Elf::strike(Player *p) {
	p->getHitBy(this);
	if (!dynamic_cast<Drow*>(p)) {
		p->getHitBy(this);
	}
}

std::string Elf::render() {
	return "E";
}
