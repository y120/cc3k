#include "bdPotion.h"

#include "fbModifyDefEffect.h"
#include "game.h"

BDPotion::BDPotion() {
	this->effect = new FBModifyDefEffect(NULL, Game::getInstance()->getFloorNumber(),
		Game::getInstance()->getPotionStrength());
}

std::string BDPotion::getNameInternal() const {
	return "Boost Defense Potion";
}
