#include "fbModifyDefEffect.h"

/**
 *	Constructor: pass base and floor through, then set modifier.
 */
FBModifyDefEffect::FBModifyDefEffect(Player *base, int floor, int modifier)
	: FloorBoundEffect(base, floor), modifier(modifier) {}

int FBModifyDefEffect::getDef() const {
	return base->getDef() + modifier;
}

FBModifyDefEffect* FBModifyDefEffect::clone() {
	return new FBModifyDefEffect(NULL, this->floor, this->modifier);
};
