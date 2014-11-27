#include "waPotion.h"

#include "fbModifyAtkEffect.h"
#include "game.h"

WAPotion::WAPotion() {
	this->effect = new FBModifyAtkEffect(NULL, Game::getInstance()->getFloorNumber(),
		-Game::getInstance()->getPotionStrength());
}

std::string WAPotion::getNameInternal() const {
	return "Wound Attack Potion";
}
