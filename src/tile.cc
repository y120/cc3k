#include "tile.h"
#include "abstractItem.h"
#include "utilities.h"
#include "game.h"
#include "floor.h"
#include "chamber.h"
#include "player.h"

Tile::Tile(int r, int c, TileType tt, Renderable *contents)
	: Renderable(r, c), chamber(NULL), tt(tt), contents(contents) {}

// Note: we do not delete the contents on destruction, since this will be
// handled elsewhere.

/**
 *	True if a particular tile can be passed by the Player.
 */
bool Tile::isPassableByPlayer() const {
	// True for door tile, passage tile, and stairs.
	if (this->is(TileType::DoorTile) || this->is(TileType::PassageTile) || this->is(TileType::ExitTile)) {
		return true;
	}
	if (this->is(TileType::FloorTile)) {
		// True for unoccupied floor tiles
		if (!this->isOccupied()) {
			return true;
		}
		// True for tiles occupied by items that can be picked up.
		AbstractItem *item = dynamic_cast<AbstractItem*>(this->contents);
		return item && item->canPickUp();
	}
	// False otherwise.
	return false;
}

/**
 *	True if a particular tile can be passed by an Enemy.
 */
bool Tile::isPassableByEnemy() const {
	return this->is(TileType::FloorTile) && !this->isOccupied();
}

/**
 *	True if a particular tile is occupied.
 */
bool Tile::isOccupied() const {
	return this->contents != NULL;
}

/**
 *	True if a particular tile is a specific TileType.
 */
bool Tile::is(TileType tt) const {
	return this->tt == tt;
}

TileType Tile::getTileType() const {
	return this->tt;
}

void Tile::setTileType(TileType tt) {
	this->tt = tt;
}

Renderable* Tile::getContents() const {
	return this->contents;
}

void Tile::setContents(Renderable *contents) {
	this->contents = contents;
}

int Tile::getDistance(Tile *t) const {
	return Utilities::distance(this->r, this->c, t->getR(), t->getC());
}

int Tile::getTaxicabDistance(Tile *t) const {
	return Utilities::taxicabDistance(this->r, this->c, t->getR(), t->getC());
}

const std::vector<Tile*>& Tile::getNeighbours() const {
	static bool calculated = false;
	static std::vector<Tile*> neighbours;
	if (!calculated) {
		for (int dr = -1; dr <= 1; dr++) {
			for (int dc = -1; dc <= 1; dc++) {
				Tile *t = Game::getInstance()->getFloor()->getTile(this->getR() + dr, this->getC() + dc);
				if (t) {
					neighbours.push_back(t);
				}
			}
		}
		calculated = true;
	}
	return neighbours;
}

std::vector<Tile*> Tile::getUnoccupiedNeighbours() const {
	std::vector<Tile*> unoccupied;
	for (int dr = -1; dr <= 1; dr++) {
		for (int dc = -1; dc <= 1; dc++) {
			Tile *t = Game::getInstance()->getFloor()->getTile(this->getR() + dr, this->getC() + dc);
			if (t && t->is(TileType::FloorTile) && !t->isOccupied()) {
				unoccupied.push_back(t);
			}
		}
	}
	return unoccupied;
}

Chamber *Tile::getChamber() const {
	return chamber;
}

void Tile::setChamber(Chamber *ch) {
	chamber = ch;
}

std::map<TileType, Renderable> &Tile::getTileset() {
	static std::map<TileType, Renderable> tileset;
	tileset[TileType::NoTile].setSprite("?");
	tileset[TileType::FloorTile].setSprite(".");
	tileset[TileType::WallTileH].setSprite("-");
	tileset[TileType::WallTileV].setSprite("|");
	tileset[TileType::DoorTile].setSprite("+");
	tileset[TileType::PassageTile].setSprite("#");
	tileset[TileType::ExitTile].setSprite("\\");
	tileset[TileType::NoTile].setColour(ColourType::DGREY);
	tileset[TileType::FloorTile].setColour(ColourType::BLUE);
	tileset[TileType::WallTileH].setColour(ColourType::BLUE);
	tileset[TileType::WallTileV].setColour(ColourType::BLUE);
	tileset[TileType::DoorTile].setColour(ColourType::MAGENTA);
	tileset[TileType::PassageTile].setColour(ColourType::DMAGENTA);
	tileset[TileType::ExitTile].setColour(ColourType::GREEN);
	return tileset;
}

void Tile::render() {
	// If tile is empty, render the tile itself
	// If graphics are implemented, remove the if statement as the
	// tile ought to be rendered anyway
	if (Game::getInstance()->hasDLC(DLC::FogOfWar) && chamber->getId() !=
		Game::getInstance()->getPlayer()->getTile()->getChamber()->getId() &&
		this->getTileType() != TileType::DoorTile) {
		getTileset()[TileType::NoTile].moveSprite(this->getR(), this->getC());
		getTileset()[TileType::NoTile].render();
		return;
	}
	if (contents == NULL) {
		getTileset()[getTileType()].moveSprite(this->getR(), this->getC());
		getTileset()[getTileType()].render();
	} else {
		contents->moveSprite(this->getR(), this->getC());
		contents->render();
	}
}
