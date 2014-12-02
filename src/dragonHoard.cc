#include "dragonHoard.h"
#include "dragon.h"
#include <iostream>

DragonHoard::DragonHoard()
	: GoldPile(GoldPile::DragonHoard), dragon(NULL)
{}

DragonHoard::DragonHoard(Dragon *dragon) : GoldPile(GoldPile::DragonHoard),
	dragon(dragon) {}

void DragonHoard::setDragon(Dragon *dg) {
	dragon = dg;
}

bool DragonHoard::canPickUp() const {
	return !dragon || dragon->isDead();
}
