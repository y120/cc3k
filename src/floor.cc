#include "floor.h"

#include "game.h"
#include "player.h"
#include "chamber.h"
#include "tile.h"
#include "tileType.h"
#include "abstractItem.h"
#include "abstractPotion.h"
#include "rhPotion.h"
#include "baPotion.h"
#include "bdPotion.h"
#include "phPotion.h"
#include "waPotion.h"
#include "wdPotion.h"
#include "goldPile.h"
#include "dragonHoard.h"
#include "abstractEnemy.h"
#include "human.h"
#include "dwarf.h"
#include "halfling.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"

/**
 *	Constructor. Initialise passages and # of goldPiles / potions. The chambers,
 *	enemies, and items vectors will initialise automatically to empty, but we
 *	will reserve space for the vectors.
 */
Floor::Floor() : goldPiles(0), potions(0), passages(new Chamber()) {
	this->chambers.reserve(Game::getInstance()->getMaxChambers());
	this->enemies.reserve(Game::getInstance()->getMaxEnemies());
	this->items.reserve(Game::getInstance()->getMaxPotions() + Game::getInstance()->getMaxGoldPiles());
}

/**
 *	Destructor. Delete all chambers, enemies, and items, as well as passages.
 */
Floor::~Floor() {
	for (std::vector<Chamber*>::iterator i = this->chambers.begin(); i != this->chambers.end(); ++i) {
		delete *i;
	}
	for (std::vector<AbstractEnemy*>::iterator i = this->enemies.begin(); i != this->enemies.end(); ++i) {
		delete *i;
	}
	for (std::vector<AbstractItem*>::iterator i = this->items.begin(); i != this->items.end(); ++i) {
		delete *i;
	}
	delete this->passages;
}

/**
 *	Generates the exit (staircase). This cannot be in the same Chamber as the
 *	PC.
 *
 *	Note that the exit is not actually stored anywhere; it's just marked as such
 *	within the Tile class.
 */
void Floor::generateExit() {
	// To generate the exit, we first choose the Chamber. To do this, we just
	// randomly choose chambers until we get one that is NOT the one the PC is
	// in. We do this because PC position is generated before exit generation.
	// We also ensure that the selected Chamber actually has an unoccupied tile.
	Chamber *chamber;
	Chamber *chamberPC = this->getChamber(Game::getInstance()->getPlayer()->getTile());
	Tile *tile;
	do {
		chamber = this->getRandomChamber();
	} while (chamber == chamberPC || !(tile = chamber->getUnoccupiedTile()));
	tile->setTileType(TileType::ExitTile);
}

/**
 *	Adds a chamber to the list of chambers, setting the ID appropriately.
 */
void Floor::addChamber(Chamber *chamber) {
	this->chambers.push_back(chamber);
	chamber->setId(this->chambers.size());
}

/**
 *	Gets a random Chamber.
 */
Chamber *Floor::getRandomChamber() const {
	return this->chambers[Game::getInstance()->rand(this->chambers.size())];
}

/**
 *	Gets a specific Chamber by ID.
 */
Chamber *Floor::getChamber(int id) const {
	return this->chambers.at(id - 1);
}

/**
 *	Registers a Passage tile.
 */
void Floor::addPassage(Tile *t) {
	this->passages->addTile(t);
}

/**
 *	Returns a fake Chamber holding the passages.
 */
Chamber *Floor::getPassages() const {
	return this->passages;
}

/**
 *	Registers an Enemy to this floor.
 */
void Floor::addEnemy(AbstractEnemy *enemy) {
	this->enemies.push_back(enemy);
}

/**
 *	Generates and registers an Enemy to this floor.
 */
void Floor::generateEnemy() {
	// We limit generation to the max, as specified by the Game.
	if ((int)this->enemies.size() >= Game::getInstance()->getMaxEnemies()) {
		return;
	}

	// To spawn an enemy, we first select the Chamber and Tile. Then, we choose
	// the Enemy type, and finally we register it.

	Tile *tile = this->getRandomUnoccupiedTile();

	/* Enemy probability distribution:
	 * Human: 2/9
	 * Dwarf: 3/18
	 * Halfling: 5/18
	 * Elf: 1/9
	 * Orc: 1/9
	 * Merchant: 1/9
	 */
	AbstractEnemy *enemy;
	switch (Game::getInstance()->rand(18)) {
		case 0: case 1: case 2: case 3: // 2/9 = 4/18
			enemy = new Human();
			break;
		case 4: case 5: case 6: // 3/18
			enemy = new Dwarf();
			break;
		case 7: case 8: case 9: case 10: case 11: // 5/18
			enemy = new Halfling();
			break;
		case 12: case 13: // 1/9 = 2/18
			enemy = new Elf();
			break;
		case 14: case 15: // 1/9 = 2/18
			enemy = new Orc();
			break;
		case 16: case 17: // 1/9 = 2/18
			enemy = new Merchant();
			break;
	}

	// Now, having decided the enemy, set its position and register it.
	enemy->moveTo(tile);
	this->addEnemy(enemy);
}

/**
 *	Adds an item to the item list.
 */
void Floor::addItem(AbstractItem *item) {
	// If it's a goldPile, increment that count.
	if (dynamic_cast<GoldPile*>(item)) {
		this->goldPiles++;
	} else if (dynamic_cast<AbstractPotion*>(item)) {
		this->potions++;
	}
	this->items.push_back(item);
}

/**
 *	Creates and adds a random Potion.
 */
void Floor::generatePotion() {
	// First, check if we're allowed to add this potion.
	if (this->potions >= Game::getInstance()->getMaxPotions()) {
		return;
	}

	// As before, select the Tile first, then place the Potion.
	Tile *tile = this->getRandomUnoccupiedTile();

	// Each Potion has a 1/6 chance of being selected.
	AbstractPotion *potion;
	switch (Game::getInstance()->rand(6)) {
		case 0:
			potion = new RHPotion();
			break;
		case 1:
			potion = new BAPotion();
			break;
		case 2:
			potion = new BDPotion();
			break;
		case 3:
			potion = new PHPotion();
			break;
		case 4:
			potion = new WAPotion();
			break;
		case 5:
			potion = new WDPotion();
			break;
	}

	// Unlike for Enemy generation, in Item generation, we just set the Tile
	// contents directly.
	tile->setContents(potion);
	this->addItem(potion);
}

/**
 *	Creates and adds a random GoldPile.
 *
 *	Note there are some special generation semantics here.
 */
void Floor::generateGoldPile() {
	// Again, first check if we're allowed to add the GoldPile.
	if (this->goldPiles >= Game::getInstance()->getMaxGoldPiles()) {
		return;
	}

	// Then, again, pick a Tile and then what kind of GoldPile.
	Tile *tile = this->getRandomUnoccupiedTile();

	// 5/8 normal, 1/8 dragon, 1/4 small.
	GoldPile *goldPile;
	switch (Game::getInstance()->rand(8)) {
		case 0: case 1: // 1/4 = 2/8
			goldPile = new GoldPile(GoldPile::SmallPile);
			break;
		case 2: case 3: case 4: case 5: case 6: // 5/8
			goldPile = new GoldPile(GoldPile::NormalPile);
			break;
		case 7: // 1/8
			// When generating a Dragon Hoard, we must also create and assign
			// a dragon to one of the surrounding blocks.
			// If there is no surrounding block, we regenerate the tile until
			// we get one.
			Tile *dragonTile = NULL;
			do {
				// Check that there exists some unoccupied Tile surrounding this.
				// If not, generate Tiles until we get one.
				std::vector<Tile*> unoccupied;
				for (int dr = -1; dr <= 1; dr++) {
					for (int dc = -1; dc <= 1; dc++) {
						if (!(dr == 0 && dc == 0)) {
							Tile *t = this->getTile(tile->getR() + dr, tile->getC() + dc);
							if (t == NULL) {
								continue;
							}

							if (t->is(TileType::FloorTile) && !t->isOccupied()) {
								unoccupied.push_back(t);
							}
						}
					}
				}

				if (unoccupied.size()) {
					dragonTile = unoccupied[Game::getInstance()->rand(unoccupied.size())];
				} else {
					tile = this->getRandomUnoccupiedTile();
				}
			} while (dragonTile == NULL);

			// Now create the dragon!
			Dragon *dragon = new Dragon(tile);
			// Then, create the Hoard.
			goldPile = new DragonHoard(dragon);
			break;
	}

	// Finally, set the Tile and register the GoldPile.
	tile->setContents(goldPile);
	this->addItem(goldPile);
}

/**
 *	Gets a Tile, given row and column.
 *	If the Tile can't be found in a Chamber or a Passage, returns NULL.
 */
Tile *Floor::getTile(int r, int c) const {
	Tile *tile = this->passages->getTile(r, c);
	for (int i = 0; !tile && i < (int)this->chambers.size(); i++) {
		tile = this->chambers[i]->getTile(r, c);
	}
	return tile;
}

/**
 *	Gets the Chamber that owns a tile, or NULL if none. Does not search
 *	passages.
 */
Chamber *Floor::getChamber(int r, int c) const {
	for (int i = 0; i < (int)this->chambers.size(); i++) {
		if (this->chambers[i]->getTile(r, c)) {
			return this->chambers[i];
		}
	}
	return NULL;
}

/**
 *	As above, but with a Tile instead of a pair of ints.
 */
Chamber *Floor::getChamber(Tile *tile) const {
	return tile == NULL ? NULL : this->getChamber(tile->getR(), tile->getC());
}

/**
 *	Gets a random unoccupied tile from a random chamber. The selected tile has
 *	an equal chance of being selected from each chamber.
 *
 *	Technically it's not guaranteed to terminate (it's possible all Tiles in
 *	all Chambers are occupied), but in practice, this is not going to happen.
 */
Tile *Floor::getRandomUnoccupiedTile() const {
	Tile *tile;
	do {
		tile = this->getRandomChamber()->getUnoccupiedTile();
	} while (tile == NULL);
	return tile;
}
