#include "fbModifyAtkEffect.h"
#include "game.h"

/**
 *	Constructor: pass base and floor through, then set modifier.
 */
FBModifyAtkEffect::FBModifyAtkEffect(Player *base, int floor, int modifier)
	: FloorBoundEffect(base, floor), modifier(modifier) {}

int FBModifyAtkEffect::getAtk() const {
	return base->getAtk() + modifier;
}

FBModifyAtkEffect* FBModifyAtkEffect::clone() {
	return new FBModifyAtkEffect(NULL, Game::getInstance()->getFloorNumber(), this->modifier);
};
