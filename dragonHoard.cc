#include "dragonHoard.h"
#include "dragon.h"

DragonHoard::DragonHoard(Dragon *dragon) : GoldPile(GoldPile::DragonHoard),
	dragon(dragon) {}

bool DragonHoard::canPickUp() const {
	return !dragon || dragon->isDead();
}
