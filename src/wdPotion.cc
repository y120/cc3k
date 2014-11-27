#include "wdPotion.h"

#include "fbModifyDefEffect.h"
#include "game.h"

WDPotion::WDPotion() {
	this->effect = new FBModifyDefEffect(NULL, Game::getInstance()->getFloorNumber(),
		-Game::getInstance()->getPotionStrength());
}

std::string WDPotion::getNameInternal() const {
	return "Wound Defense Potion";
}
