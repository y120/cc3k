#include "chamber.h"
#include "game.h"
#include "player.h"
#include "baseEnemies.h"
#include "basePotions.h"
#include "goldPile.h"
#include "dragonHoard.h"
#include "tile.h"
#include "tileType.h"
#include <vector>
#include <iostream>							// for cerr

/**
 *	Constructor: set id (if any).
 */
Chamber::Chamber(int id) : id(id), floor(NULL) {}

/**
 *	Constructs a chamber from a loaded string vector position (r,c)
 */
Chamber::Chamber(Floor *fl, std::vector<std::string> &store, int r, int c)
	: id(-1), floor(fl), tiles()
{
	//std::cerr << "Chamber: constructor " << r << ' ' << c << std::endl;
	//std::cerr << "store size:" << store.size() << "x" << store[0].length() << std::endl;
	floodFill(store, r, c);
}

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
Tile *Chamber::addTile(int r, int c, TileType tt, Renderable *re) {
	std::pair<int, int> p = std::make_pair(r, c);
	// Only add the Tile if it's not already registered. This should always be
	// the case anyway, but it doesn't hurt to check...
	if (this->tiles.count(p) == 0) {
		this->tiles[p] = new Tile(r, c, tt, re);
		this->tiles[p]->setChamber(this);
	}
	return this->tiles[p];
}

/**
 *	Registers a Tile as being part of this Chamber.
 */
Tile *Chamber::addTile(Tile *t) {
	std::pair<int, int> p = std::make_pair(t->getR(), t->getC());
	// Only add the Tile if it's not already registered. This should always be
	// the case anyway, but it doesn't hurt to check...
	if (this->tiles.count(p) == 0) {
		this->tiles[p] = t;
		this->tiles[p]->setChamber(this);
	}
	return this->tiles[p];
}

/**
 *	Gets the Tile from the specified address, or NULL if not in this Chamber.
 */
Tile *Chamber::getTile(int r, int c) const {
	//std::cerr << "Chamber - gettingTile " << r << ' ' << c << "\n";
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

// Getter and setter for parent Floor
Floor *Chamber::getFloor() const {
	return floor;
}
void Chamber::setFloor(Floor *fl) {
	floor = fl;
}

/**
 *	Fills the given Chamber ptr with stuff from the string vector
 *
 *	NOTE: * represents a processed dragonHoard.
 */
Tile *Chamber::floodFill(std::vector<std::string> &store, int r, int c) {
	if (store[r][c] == ' ' || store[r][c] == '*') {
		// if we've already visited it, just return the tile reference
		return getTile(r, c);
	}

	//std::cerr << "Chamber: floodFilling " << r << ' ' << c << " '" << store[r][c]  << "'\n";
	TileType tt = TileType::NoTile;
	Renderable *thing = NULL;
	if (store[r][c] == '.') {
		tt = TileType::FloorTile;
	} else if (store[r][c] == '-') {
		tt = TileType::WallTileH;
	} else if (store[r][c] == '|') {
		tt = TileType::WallTileV;
	} else if (store[r][c] == '+') {
		tt = TileType::DoorTile;
	} else if (store[r][c] == '#') {		// Should never happen
		tt = TileType::PassageTile;
	} else if (store[r][c] == '\\' || store[r][c] == '/') {
		tt = TileType::ExitTile;
	} else {
		tt = TileType::FloorTile;
		switch (store[r][c]) {
			case '@':
				thing = Game::getInstance()->getPlayer();
				this->getFloor()->setPlayerPos(r, c);
				break;
			case 'H':
				thing = this->getFloor()->addEnemy(new Human());
				break;
			case 'W':
				thing = this->getFloor()->addEnemy(new Dwarf());
				break;
			case 'E':
				thing = this->getFloor()->addEnemy(new Elf());
				break;
			case 'O':
				thing = this->getFloor()->addEnemy(new Orc());
				break;
			case 'M':
				thing = this->getFloor()->addEnemy(new Merchant());
				break;
			case 'D': {
				Tile *hoardTile = NULL;
std::cerr << "Dragon at " << r << " " << c << "!\n";
				for (int dr = -1; dr <= 1; dr++) {
					for (int dc = -1; dc <= 1; dc++) {
						if (!(dr == 0 && dc == 0)) {
							if (store[r + dr][c + dc] == '9' || store[r + dr][c + dc] == '*') {
								hoardTile = floodFill(store, r + dr, c + dc);
								store[r + dr][c + dc] = ' ';
std::cerr << "Dpos: " << r << " " << c << "; hoard: " << r + dr << " " << c + dc << '\n';
							}
						}
					}
				}
				thing = this->getFloor()->addEnemy(new Dragon(hoardTile));
				if (hoardTile) {
					DragonHoard *dh = dynamic_cast<DragonHoard*>(hoardTile->getContents());
					if (dh) {
						dh->setDragon(static_cast<Dragon*>(thing));
					}
				}
				break;
			}
			case 'L':
				thing = this->getFloor()->addEnemy(new Halfling());
				break;
			case 'P':
				std::cerr << "Random Potion in map file not implemented\n";
				break;
			case 'G':
				std::cerr << "Random Goldpile in map file not implemented\n";
				break;
			case '0':
				thing = this->getFloor()->addItem(new RHPotion());
				break;
			case '1':
				thing = this->getFloor()->addItem(new BAPotion());
				break;
			case '2':
				thing = this->getFloor()->addItem(new BDPotion());
				break;
			case '3':
				thing = this->getFloor()->addItem(new PHPotion());
				break;
			case '4':
				thing = this->getFloor()->addItem(new WAPotion());
				break;
			case '5':
				thing = this->getFloor()->addItem(new WDPotion());
				break;
			case '6':
				thing = this->getFloor()->addItem(new GoldPile(GoldPile::NormalPile));
				break;
			case '7':
				thing = this->getFloor()->addItem(new GoldPile(GoldPile::SmallPile));
				break;
			case '8':
				thing = this->getFloor()->addItem(new GoldPile(GoldPile::MerchantHoard));
				break;
			case '9':
std::cerr << "Hoard at " << r << " " << c << "!\n";
				thing = this->getFloor()->addItem(new DragonHoard());
				break;
		}
	}
	Tile *tilePtr = this->addTile(r, c, tt, thing);

	// Recursively apply to all neighbours
	if (store[r][c] == '|' || store[r][c] == '-' || store[r][c] == '+') {
		// don't recurse if it's currently a wall or a door
		return tilePtr;
	}
	store[r][c] = store[r][c] == '9' ? '*' : ' ';

	for (int dr = -1; dr <= 1; dr++) {
		for (int dc = -1; dc <= 1; dc++) {
			if (!(dr == 0 && dc == 0)) {
				int nr = r + dr, nc = c + dc;
				if (nr < 0 || nc < 0 || nr >= (int)store.size() || 
					nc >= (int)store[nr].length()) {
					continue;
				}
				if (store[nr][nc] != ' ' && 
					store[nr][nc] != '#' &&
					store[nr][nc] != '9') {
					// We only want to go to a goldpile from a dragon tile
					floodFill(store, nr, nc);
				}
			}
		}
	}
	return tilePtr;
}

/**
 *	Renders all tiles of the chamber
 */
void Chamber::render() {
	for (std::map<std::pair<int, int>, Tile*>::iterator mIt = tiles.begin();
		 mIt != tiles.end(); mIt++) {
		//std::cerr << "Chamber: render tile " << std::endl;
		mIt->second->render();
	}
}
