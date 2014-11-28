#include "chamber.h"
#include "game.h"
#include "player.h"
#include "tile.h"
#include "tileType.h"
#include <vector>

/**
 *	Constructor: set id (if any).
 */
Chamber::Chamber(int id) : id(id) {}

/**
 *	Memory management on the Tiles is tied to the Chamber. The destructor will
 *	delete all associated Tiles.
 */
Chamber::~Chamber() {
	for (std::map<std::pair<int, int>, Tile*>::iterator it = this->tiles.begin();
		it != this->tiles.end(); ++it) {
		delete it->second;
	}
	this->tiles.clear();
}

/**
 *	Creates and adds a Tile to this Chamber.
 */
void Chamber::addTile(int r, int c, TileType tt, Renderable *re) {
	std::pair<int, int> p = std::make_pair(r, c);
	// Only add the Tile if it's not already registered. This should always be
	// the case anyway, but it doesn't hurt to check...
	if (this->tiles.count(p) == 0) {
		this->tiles[p] = new Tile(r, c, tt, re);
	}
}

/**
 *	Registers a Tile as being part of this Chamber.
 */
void Chamber::addTile(Tile *t) {
	std::pair<int, int> p = std::make_pair(t->getR(), t->getC());
	// Only add the Tile if it's not already registered. This should always be
	// the case anyway, but it doesn't hurt to check...
	if (this->tiles.count(p) == 0) {
		this->tiles[p] = t;
	}
}

/**
 *	Gets the Tile from the specified address, or NULL if not in this Chamber.
 */
Tile *Chamber::getTile(int r, int c) const {
	std::pair<int, int> p = std::make_pair(r, c);
	if (this->tiles.count(p)) {
		return this->tiles.at(p);
	} else {
		return NULL;
	}
}

/**
 *	Gets a random unoccupied, or NULL if none exists.
 */
Tile *Chamber::getUnoccupiedTile() const {
	// Presize the unoccupied vector to be the total number of Tiles to avoid
	// reallocation.
	std::vector<Tile*> unoccupied;
	unoccupied.reserve(this->tiles.size());

	// Filter the map for unoccupied floor tiles.
	for (std::map<std::pair<int, int>, Tile*>::const_iterator it = this->tiles.begin();
		it != this->tiles.end(); ++it) {
		if (!it->second->isOccupied() && it->second->is(TileType::FloorTile)) {
			unoccupied.push_back(it->second);
		}
	}

	// If we have no unoccupied Tiles, return NULL.
	if (unoccupied.size() == 0) {
		return NULL;
	} else {
		// Otherwise, select a random one.
		return unoccupied[Game::getInstance()->rand(unoccupied.size())];
	}
}

// Getter and setter for ID.
int Chamber::getId() const {
	return this->id;
}
void Chamber::setId(int id) {
	this->id = id;
}

/**
 *	Renders all tiles of the chamber
 */
void Chamber::render() {
	for (std::map<std::pair<int, int>, Tile*>::iterator mIt = tiles.begin();
		 mIt != tiles.end(); mIt++) {
		mIt->second->render();
	}
}