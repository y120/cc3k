#include "rhPotion.h"
#include "game.h"
#include "player.h"
#include "display.h"
#include <sstream>

void RHPotion::apply() {
	int dhp = 2 * Game::getInstance()->getPotionStrength();
	int hp = Game::getInstance()->getPlayer()->getHP();
	Game::getInstance()->getPlayer()->addHP(dhp);
	dhp = Game::getInstance()->getPlayer()->getHP() - hp;
	AbstractPotion::apply();

	std::ostringstream oss;
	oss << Game::getInstance()->getPlayer()->getName() << " heals for " << dhp << " HP!";
	Display::getInstance()->addMessage(oss.str());
}

std::string RHPotion::getNameInternal() const {
	return "Restore Health Potion";
}
